/**
 * @file oc_sysdl.h
 * @brief system wrapper to dynamic loading API
 * 
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_sysdl.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_SYSDL_H
#define OC_SYSDL_H 

/* configure system headers */
#include <OC/oc_config.h>

#if defined(__hpux)

#include <dl.h>

#define oc_shl_findsym	shl_findsym
#define oc_shl_load	shl_load
#define oc_shl_unload	shl_unload

#elif defined(__linux)

/* ANSI C headers */
#include <errno.h>
#include <stdio.h>
#include <malloc.h>

/* Opencall system wrappers */
#include <OC/oc_dlfcn.h>
#include <OC/oc_limits.h>

/*
 * #define's borrowed from dl.h on HPUX.  Not all of these will be interpreted
 * or used by the shl code on Linux.  These are here just to satisfy deps for
 * apps written on HPUX. Most of these will be either ignored or overridden by
 * defaults.
 */

#define BIND_IMMEDIATE  0x0
#define BIND_DEFERRED   0x1
#define BIND_REFERENCE  0x2

#define BIND_FIRST      0x4
#define BIND_NONFATAL   0x8
#define BIND_NOSTART    0x10
#define BIND_VERBOSE    0x20
#define BIND_RESTRICTED 0x40

#define TYPE_UNDEFINED  0
#define TYPE_PROCEDURE  3
#define TYPE_DATA       2
#define TYPE_STORAGE    7
#define TYPE_TSTORAGE   16

#define IMPORT_SYMBOLS  0x1
#define EXPORT_SYMBOLS  0x2

#define NO_VALUES       0x4
#define GLOBAL_VALUES   0x8

#define INITIALIZERS    0x10

/* 
 * the shl_xxx API is not available on Linux & is deprecated on HP-UX.  Both
 * OS'es prefer the dl_xxx API.  However, the following wrapps shl_xxx over
 * dl_xxx for backwards-compatibility reason.
 * 
 * @note the shl_xxx API includes library-static data, so it is not
 * thread-safe.
 */

struct shlinfo {
	void *handle;
	char slname[MAXLEN_FILENAME+MAXLEN_FILEPATH]; /* Fix for GREhp41768 */
	};

typedef struct shlinfo *shl_t;

struct shl_symbol {
        char           *name;
        short           type;
        void           *value;
        shl_t           handle;
};

struct shl_descriptor {
	shl_t handle;
	char filename[512];
	int len;

};

#ifdef __cplusplus
extern "C" {
#endif

extern shl_t oc_shl_load ( char *path, int flags, long address);

extern int oc_shl_get ( int index, struct shl_descriptor **desc);

extern int oc_shl_getsymbols ( shl_t handle, short type, int flags, void *(*memory) ( void ), struct shl_symbol **symbols);

extern int oc_shl_findsym ( shl_t *handle, const char *sym, short type, void *value);

extern int oc_shl_unload ( shl_t handle);

extern struct shl_descriptor slret;

#ifdef __cplusplus
}
#endif

#endif /* __os */

#endif /* OC_SYSDL_H */
