/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_macros.h
 * @brief useful macros for development
 * 
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_macros.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_MACROS_H
#define OC_MACROS_H

#include <OC/oc_config.h>

/**
 * @defgroup portability-macros
 * @brief portable helper macros
 * @{
 */

/**
 * @def oc_perror
 *
 * The ISO-C function perror() only provide support for the built-in errno
 * integer.  this wrapper allows to provide another error number source.
 * resulting string is still printed on stderr.
 *
 * @param err the error code source
 * @param msg the message to print,
 */

#include <stdio.h>
#include <errno.h>
#ifdef __linux
#include <string.h>		/* strerror */
#endif /* __linux */
#ifdef DEBUG
#include <assert.h>
#endif /* DEBUG */

#ifndef __cplusplus

#ifdef DEBUG

#define oc_perror( err, msg )                                           \
        fprintf( stderr,                                                \
                 __FILE__ ":" __LINESTR__ " [%s]: *** err=%d(%s) %s\n", \
                 __func__, err, strerror( err ), msg )

#define oc_abort( msg )                                                 \
        assert( __FILE__ ":" __LINESTR__ ": " msg == NULL )

#define oc_tdebug(...)                                                  \
        fprintf( stderr,                                                \
                 __FILE__ ":" __LINESTR__ ": " __VA_ARGS__ )

#else  /* !DEBUG */

#define oc_perror( err, msg )

#define oc_abort( msg )                                                 \
        fprintf( stderr,                                                \
                 __FILE__ ":" __LINESTR__ " [%s]: ASSERTION FAILED *** "\
		 msg "\n", __func__)

#define oc_tdebug(...)                                                  \
        do {} while (0)

#endif /* !DEBUG */

#endif /* !__cplusplus */

/**
 * @}
 */

#endif /* OC_MACROS_H */
