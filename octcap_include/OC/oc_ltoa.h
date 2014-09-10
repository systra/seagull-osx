/**
 * @file HP-AIN/OC/oc_ltoa.h
 * @brief "long" to ASCII (char*) conversion
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_ltoa.h>
 * @endverbatim
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_LTOA_H
#define OC_LTOA_H

#ifdef __linux

#ifdef __cplusplus
extern "C" {
#endif

extern char *	oc_ltoa( long n );
extern int	oc_ltoa_r( long n, char *buffer, int buflen );

#ifdef __cplusplus
}
#endif

#elif defined(__hpux)

#include <stdlib.h>

#define oc_ltoa		ltoa

#endif /* __os */

#endif /* OC_LTOA_H */
