/**
 * @file oc_strstr.h
 * @brief provide ANSI function "strstr", when missing
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_strstr.h>
 * @endverbatim
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_STRRSTR_H
#define OC_STRRSTR_H

#include <OC/oc_config.h>

#ifdef __GLIBC__

#ifdef __cplusplus
extern "C" {
#endif

extern char *oc_strrstr( const char *mainstr, 
			 const char *substr );

#ifdef __cplusplus
}
#endif

#else  /* !__GLIBC__ */

#include <string.h>

#define oc_strrstr	strstr

#endif /* !__GLIBC__ */

#endif /* OC_STRRSTR_H */
