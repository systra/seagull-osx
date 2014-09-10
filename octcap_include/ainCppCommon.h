/** -*- mode : c++ -*-
 * @file oc_inttypes.h
 * @brief basic definitions of types and manifest constants for C++ objects
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_iostream.H>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _AINCPPCOMMON_H
#define _AINCPPCOMMON_H

#ifdef __cplusplus

#include <OC/oc_config.h>
#include <OC/oc_types.h>
#include <OC/oc_stream.H>

#define HPAIN_HPAINAPI	OC_API

#ifdef HAVE_NAMESPACES
namespace
#else  // !HAVE_NAMESPACES
class HPAIN_HPAINAPI
#endif
HPAIN
{
#ifndef HAVE_NAMESPACES
public:
#endif
	//--------------------------------------------------------------------------
	// Common C++ AIN types for HPAIN APIs
	//--------------------------------------------------------------------------

	typedef int16_t		Int16;
	typedef int32_t		Int32;
	typedef uint8_t		Uint8;
	typedef uint16_t	Uint16;
	typedef uint32_t	Uint32;
	typedef uint8_t		Byte;
	typedef struct iovec 	IoVec;

	enum Boolean { bFalse=0, bTrue=1 };

	//--------------------------------------------------------------------------
	// Status base class
	//--------------------------------------------------------------------------
	
	// Note the implicit 
	// int/enum casts cunningly hidden in the StatusValue typedef
	class StatusBase 
	{
	public:
		typedef int StatusValue;
#ifdef _WIN32
#  ifdef NO_ERROR
#     if ((NO_ERROR) != 0L) && ((NO_ERROR) != 0)
#       error NO_ERROR must be set to 0
#     else
#       undef NO_ERROR
#     endif
#  endif
#endif /* _WIN32 */
		enum Status {NO_ERROR=0};
	
		// get enum value (used by derived classes too)
		StatusValue getStatus() const
			{return theStatus;}

		// is this status a temporary setback (ie an error and not
		// fatal)?  If the derived status object only has fatal errors
		// it can just use this version
		virtual Boolean isRecoverable()
			{return bFalse; }

		// is this status an error? (note: Derived classes should
		// redefine this)
		virtual Boolean isOk() const
			{return (theStatus==NO_ERROR) ? bTrue : bFalse;}

                // allow to reset the status value
		virtual void reset()
			{theStatus=NO_ERROR;}
	
		// o/p of localised user readable error string
		friend ostream& operator<< (ostream& os, StatusBase)
			{ os << "No error\n"; return os; }

	protected:
		// only derived classes can make it
		StatusBase(StatusValue s): theStatus(s)
			{ }

		// Default ctor (to allow passing in to calls)
		StatusBase(): theStatus(NO_ERROR)
			{}

		// all base classes should have virtual dtors
		virtual ~StatusBase()
			{}

		// only derived classes can explicitly set the value This is
		// virtual as apis will set the status in passed derived
		// objects by using it. To create special behaviour (eg
		// stacks), it is possible to inherit from the api's status
		// object and make this fn perform the specific behaviour
		// required.
		virtual void setStatus(StatusValue s)
			{ theStatus=s; }

	private:
		// derived classes must use the ctor to set this,and the
		// accessor to get it.
		StatusValue theStatus;
	};

	//--------------------------------------------------------------------------
	// Schedulable base class
	//--------------------------------------------------------------------------

	class  Schedulable 
	{
	public:
		Schedulable()
			{};

		virtual ~Schedulable()
			{};

		typedef int Work;
		enum {UNLIMITED=-2,URGENT=-1,NONE=0};

		// schedular i/f 
#ifdef _WIN32
		virtual int preWaitForMultipleObjects( DWORD * numHdl,
						       DWORD,
						       HANDLE *, 
						       struct timeval *&)
			{ return *numHdl; };

		virtual Work handler( DWORD ,
				      HANDLE *,
				      DWORD)
			{ return NONE; }
#else  // !_WIN32
		virtual int selectMask( int maxFd,
					fd_set *,
					fd_set *,
					fd_set *,
					struct timeval *& )
			{ return maxFd; }

		virtual Work handler( int ,
				      fd_set *,
				      fd_set *,
				      fd_set * )
			{ return NONE; }
#endif /* !_WIN32 */

		virtual Work doWork( Work P_work ) = 0;
		
	private:
		// No copy ctor
		Schedulable(const Schedulable&);
		const Schedulable& operator=(const Schedulable&);
	};

};

#endif /* __cplusplus */
#endif /* _AINCPPCOMMON_H */






