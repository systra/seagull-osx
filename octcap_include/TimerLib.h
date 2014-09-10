/**
 * @file TimerLib.h
 * @brief hp Opencall timer services
 * 
 * External & Public hp Opencall TimerLib Interface declaration.
 * 
 * Use it using:
 *
 * @verbatim
 * #include <TimerLib.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _TIMERLIB_H
#define _TIMERLIB_H

#ifndef TIMERXX_UseGHT
#define TIMERXX_UseGHT 3
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Opencall system wrappers */
#include <OC/oc_config.h>
#include <OC/oc_sys_select.h>
#include <OC/oc_types.h>

/* Opencall headers */
#include <ainCommon.h>

/* Set hp Opencall TimerLib configuration depending on the current OS.  Given
 * values below may be over-ridden at TimerLib generation time.
 */

/* clock sources */
#if defined(__hpux)
#define	HAVE_CLK_CPU_COUNTER	1	/* both hppa & ia64 */
#define	HAVE_CLK_GETHRTIME	1	/* not, unless PATCH */
#define HAVE_CLK_HRTIME		0	/* Linux only */
#elif defined(__linux)
#if defined(__ia64)
#define	HAVE_CLK_CPU_COUNTER	1	/* ia64 AR_ITC used */
#else  /* __ia64 */
#define	HAVE_CLK_CPU_COUNTER	0	/* ia32's tsc not used */
#endif /* __ia64 */
#define	HAVE_CLK_GETHRTIME	0	/* HP-UX only */
#define HAVE_CLK_HRTIME		0	/* not, unless PATCH */
#else
#define	HAVE_CLK_CPU_COUNTER	0
#define	HAVE_CLK_GETHRTIME	0
#define HAVE_CLK_HRTIME		0
#endif

/* UNIX ALARM signal API */
#if !(defined(__linux) && defined(_REENTRANT))
#define HAVE_OCTIME_SIGALRM	1
#else  /* __linux && _REENTRANT */
#define HAVE_OCTIME_SIGALRM	0
#endif

	/**
	 * @defgroup octime-API
	 * @brief new TimerLib API, optimized for thread-safe applications
	 * @{
	 *
	 * This TimerLib API is fully thread-safe & optimized for
	 * multi-threaded usage.
	 */

	/**
	 * @enum octime_timer_repetition
	 * @brief timer will repeat popping forever or not
	 * @see OCTIME_set_timer
	 * @see OCTIME_set_timer_t
	 * @see octime_timer_repetition_t
	 */
	enum octime_timer_repetition {
		TIMER_ONCE	= 1,
		TIMER_REPEAT	= 2
	};

	/**
	 * @typedef octime_timer_repetition
	 * @brief timer will repeat popping forever or not
	 * @see octime_timer_repetition
	 */
	typedef enum octime_timer_repetition	octime_timer_repetition_t;

	/**
	 * @enum octime_timer_origin
	 * @brief timer run from the UNIX Epoch or from current date
	 * @see OCTIME_set_timer
	 * @see OCTIME_set_timer_t
	 * @see octime_timer_origin_t
	 */
	enum octime_timer_origin {
		TIMER_ABSOLUTE	= 0,
		TIMER_RELATIVE	= 1
	};

	/**
	 * @typedef octime_timer_origin
	 * @brief timer run from the UNIX Epoch or from current date
	 * @see octime_timer_origin
	 */
	typedef enum octime_timer_origin	octime_timer_origin_t;

	/**
	 * @enum octime_clk
	 * @brief possible clock sources
	 * 
	 * @see octime_clk_t
	 * @see OCTIME_init_module
	 * @see OCTIME_set_clock_source
	 * @see OCTIME_get_clock_source
	 * 
	 * @note Not all the clock sources are available on all the architecture /
	 * operating system couple.
	 */
	enum octime_clk {
		TIMER_CLK_SYS		= 0,
		TIMER_CLK_HRTIME	= 1,
		TIMER_CLK_CPU_COUNTER	= 2,
		TIMER_CLK_GETHRTIME	= 3
	};

	/**
	 * @typedef octime_clk_t
	 * @brief possible clock sources
	 * @see octime_clk
	 */
	typedef enum octime_clk octime_clk_t;

	/**
	 * @enum octime_errors
	 * @brief values taken by octime_errno
	 * @see octime_errors_t
	 */
	enum octime_errors {
		TIMER_ENOERR		= 0,
		TIMER_EINVAL		= 1,
		TIMER_EUNSUPPCLK	= 2,
		TIMER_ENOMEM		= 3,
		TIMER_ECLKINIT		= 4,
		TIMER_EBUSY		= 5
	};

	/**
	 * @typedef octime_errors_t
	 * @brief values taken by octime_errno
	 * @see octime_errors
	 */
	typedef enum octime_errors octime_errors_t;

	/**
	 * boolean flags to set in the OCTIME_init_module flags parameter
	 */
#define TIMER_F_NONE			0
#define TIMER_F_LAST			(1 << 0)

	typedef void*	octime_opaque_t;
	typedef void*	octime_module_t;
	typedef void*	octime_application_t;

	/**
	 * @var V_octime_shared_info
	 * @brief compile-time parameters settings
	 *
	 * @var si_ts_never constant struct COM_timeval containing the formal
	 * value "never", as understood by the current MsgLib.  this field is
	 * preserved for backward compatibility reasons.
	 *
	 * @var si_tv_never constant struct timeval containing the formal value
	 * "never", as understood by the current MsgLib.
	 *
	 * this structure contains constant values that were set at Opencall
	 * TimerLib compilation time.  these values are shared by every threads
	 * using the TimerLib.
	 *
	 * This structure has a single instance for a whole process.  Use the
	 * accessor macro "OCTIME_SHARED_INFO" to access the fields.
	 * 
	 * @note using this field is deprecated with the new OCTIME API.
	 */

	struct octime_shared_info {
		struct COM_timeval	si_ts_never;
		struct timeval		si_tv_never;
	};
	typedef struct octime_shared_info	octime_shared_info_t;
	const OC_API octime_shared_info_t	V_octime_shared_info;

	/* accessors */
#define OCTIME_SHARED_INFO( p )	(V_octime_shared_info.si_##p)
#define OCTIME_TV_NEVER		OCTIME_SHARED_INFO(tv_never)

	/**
	 * @typedef octime_cb_t
	 * @brief Opencall TimerLib callbacks type
	 *
	 * @param app	the application handle (octime_application_t),
	 * 		exactly as provided by the application to the
	 * 		"OCTIME_init_module" function in the "app"
	 * 		parameter,
	 * @param v	the first opaque (octime_opaque_t) parameter given
	 * 		to the Opencall TimerLib when arming the timer with
	 * 		"OCTIME_set_timer",
	 * @param p	the second opaque parameter,
	 * @param ts	the current time (struct timeval).
	 *
	 * this is the only type of function allowed to be passed as call-back
	 * functions to the Opencall TimerLib.
	 */
	typedef void		(*octime_cb_t)( octime_application_t app,
						octime_opaque_t v,
						octime_opaque_t p,
						struct timeval ts );

	/* init and destroy */
	OC_API octime_module_t	OCTIME_init_module( int n_timers, octime_application_t app, octime_clk_t clock, uint32_t flags );
	OC_API int		OCTIME_destroy_module( octime_module_t tm );

	/* configuration edition */
	OC_API octime_module_t	OCTIME_get_default_module( void );
	OC_API int		OCTIME_set_clock_source( octime_module_t tm, octime_clk_t clk );
	OC_API octime_clk_t	OCTIME_get_clock_source( octime_module_t tm );

	/* takes a pointer to a pointer to allow it to be set to NULL, for select(2) when NO timeout */
	OC_API int		OCTIME_select_time( octime_module_t tm, struct timeval **t );
	OC_API void		OCTIME_handler( octime_module_t tm );

	OC_API void*		OCTIME_set_timer( octime_module_t tm, struct timeval ts, octime_cb_t cb, void *v, void *p, int del, int rel );
	OC_API void*		OCTIME_set_timer_t( octime_module_t mh, time_t s, suseconds_t u, octime_cb_t cb, void *v, void *p, int del, int rel );
	OC_API void		OCTIME_cancel_timer( octime_module_t tm, void *tp );

	OC_API struct timeval	OCTIME_ts_now( octime_module_t tm );
	OC_API struct timeval	OCTIME_ts_now_system( octime_module_t tm );

	OC_API int		OCTIME_ts_lessthan( struct timeval t1, struct timeval t2 );
	OC_API int		OCTIME_ts_equals( struct timeval t1, struct timeval t2 );
	OC_API struct timeval	OCTIME_ts_sub( struct timeval t1, struct timeval t2 );
	OC_API struct timeval	OCTIME_ts_add( struct timeval t1, struct timeval t2 );
	/* thread-safe function wrapper to access octime_errno */
	OC_API int*		OCTIME_errno_ptr (void);
#define octime_errno			(*OCTIME_errno_ptr())


	/**
	 * @}
	 */

	/**
	 * @defgroup timer-API
	 * @brief deprecated TimerLib API, not optimized for multi-thread
	 * @{
	 *
	 * this API is thread-safe, but suffers a performance penalty due to
	 * the per-thread data lookup at each call.  the API Rev2, including
	 * "octime_module_t" is preferred for new developments.
	 *
	 * each API Rev1 function first resolves the missing "octime_module_t"
	 * & then proceeds using the new API.
	 */

	typedef void				(*TIMER_T_CB)(void *, void *, struct COM_timeval);

	OC_API int			TIMER_init_module( int nTimers );
	OC_API int			TIMER_destroy_module( int tId );

	OC_API octime_clk_t		TIMER_get_clock_source( void );
	OC_API int			TIMER_set_clock_source( octime_clk_t clk );

	OC_API void			TIMER_select_time( struct timeval **t );
	OC_API void			TIMER_handler( int n );

	OC_API void*			TIMER_set_timer( struct COM_timeval ts, TIMER_T_CB cb, void *v, void *p, int del, int rel );
	OC_API void*			TIMER_set_timer_t( int s, int u, TIMER_T_CB cb, void *v, void *p, int del, int rel );
	OC_API void			TIMER_cancel_timer( void *tp );
	OC_API struct COM_timeval	TIMER_ts_now( void );
	OC_API struct timeval		TIMER_ts_now_Real( void );

	OC_API int			TIMER_ts_lessthan( struct COM_timeval t1, struct COM_timeval t2 );
	OC_API int			TIMER_ts_lessthan_tv( struct COM_timeval t1, struct timeval t2 );
	OC_API int			TIMER_ts_equals( struct COM_timeval t1, struct COM_timeval t2 );
	OC_API struct COM_timeval	TIMER_ts_sub( struct COM_timeval t1, struct COM_timeval t2 );
	OC_API struct COM_timeval	TIMER_ts_add( struct COM_timeval t1, struct COM_timeval t2 );

#define TIMER_ts_never	OCTIME_SHARED_INFO(ts_never)

	/**
	 * @}
	 */

	/**
	 * @defgroup sigalrm-API
	 * @brief API to handle SIGALRM as clock-source
	 * @{
	 *
	 * @warning SIGALRM API is an interface that comes from the old time
	 * where select(2) timeout was not a reliable clock source.  This
	 * SIGALRM API should really not be used: consider switching to the
	 * Rev2 API (optimized for multi-thread).
	 *
	 * Use the UNIX signal SIGALRM to set the current date within TimerLib
	 * internal structures.  This API does only work on the default
	 * per-thread TimerLib module.  It cannot be used against a
	 * user-initialized TimerLib module.
	 *
	 * The user of the TimerLib can i/f with sigalm in two ways - either WE
	 * control it, and have the signal handler, or the user controls it,
	 * and gives us the address of their timeofday variable.
	 *
	 * @warning Linux multi-threads API (LinuxThreads) is based on "light
	 * processes" (using "clone(2)"), that have separated pid_t.  this
	 * approach is not compatible with UNIX threads for signals: UNIX
	 * threads share the same pid_t, but have different pthread_t.
	 * Therefore, the SIGLARM API is disabled when this code is compiled
	 * for Linux with multi-thread support.
	 */
#if !(defined(__linux) && defined(_REENTRANT))

	typedef void		(*TIMER_T_SIGCB)( int signal
#if !defined(__ia64) && defined(__hpux)
						  ,
						  int code,
						  struct sigcontext *sigc
#endif /* !__ia64 && __hpux */
		);

	/**
	 * @func TIMER_use_sigalm
	 * @brief install a SIGALRM handler & regular SIGALRM timer pop
	 */
	OC_API void	TIMER_use_sigalm( TIMER_T_SIGCB   users_sig_cb, struct COM_timeval res );

	/**
	 * @func TIMER_set_timeofday_var
	 * @brief give pointer to the user's maintained date
	 *
	 * @param user_tv_ptr place where the user maintains the date
	 *
	 * The user is using SIGALM to get timeofday. So we point our timeofday
	 * var pointer to the user's one.  For using SIGALM, either with
	 * timerlib in control or user in control.
	 *
	 * This function does not take any "module" parameter, since the only
	 * TimerLib module SIGALM can operate on is the default per-thread
	 * TimerLib module.
	 */
	OC_API void	TIMER_set_timeofday_var( struct COM_timeval *user_tv_ptr );

	/**
	 * @}
	 */

#endif /* !(__linux && _REENTRANT) */

#ifndef OC_DONT_USE_OLD_CR16
	/**
	 * @defgroup CR16-API
	 * @brief deprecated way to set the prefered clock-source
	 * @{
	 */
	/* thread-safe function wrapper to access TIMERXX_UseCR16_ptr */
	OC_API int*	TIMER_use_cpu_counter_ptr( void );
#define TIMERXX_UseCR16		(*TIMER_use_cpu_counter_ptr())
	/**
	 * @}
	 */
#endif /* OC_DONT_USE_OLD_CR16 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _TIMERLIB_H */
