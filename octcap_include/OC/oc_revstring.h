/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_revstring.h
 * @brief automatic generation of revision strings
 * 
 * when included, this file adds some static strings to the resulting binary
 * object file.  It replaces the numerous duplication of some attempts to
 * include so-called "what-strings" in various places of the opencall code.
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_revstring.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_REVSTRING_H
#define OC_REVSTRING_H

#include <OC/oc_config.h>

/**
 * @def PUBLIC_STRING
 *
 * this macro results in placing a static const char* string that can be read
 * both in the generated binary file & in any core dump using the ususal
 * version marking commands:
 *
 * @li RCS's "ident", provided on both UNIX & Linux,
 * @li SCCS's "what, provided on UNIX only.
 *
 * @param var name of the static const char* variable
 * @param string actual information
 * @param head RCS-like header "Option", "Name", ...etc.
 * 
 * @see PRIVATE_STRING
 */

#define PUBLIC_STRING(var, head, string) \
static const char ATTRIBUTE_UNUSED * var = "$" head ": @(#)" string " $"

/**
 * @def PRIVATE_STRING
 *
 * this macro results in placing a static const char* string that can be read
 * both in the generated binary file & in any core dump using a non-standard
 * version marking command:
 *
 * string <file> | grep '@(@)'
 *
 * @param var name of the static const char* variable
 * @param string actual information
 *
 * @see PUBLIC_STRING
 */

#define PRIVATE_STRING(var, string) \
static const char ATTRIBUTE_UNUSED * var = "@(@)" string

/**
 * @func CM_WHATSTRING
 *
 * if not defined by the build system, the CM_WHATSTRING macro defaults to a
 * null-terminated string of 30 'X' characters.  the build/packaging system is
 * free to replace this value by any relevant need to embed build/packaging
 * information into binary deliveries.
 * 
 * @param none
 */

#ifndef CM_WHATSTRING
#define CM_WHATSTRING \
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#endif /* CM_WHATSTRING */

PUBLIC_STRING (_cm_what, "WHAT", CM_WHATSTRING);

/**
 * Additional strings, stating the Operating System name & version the object
 * was compiled for.
 */

#ifndef MACHINE
#define MACHINE "<UNKNOWN MACHINE>"
#endif
#ifndef SYSNAME
#define SYSNAME "<UNKNOWN SYSNAME>"
#endif
#ifndef SYSVERSION
#define SYSVERSION 999999
#endif

PRIVATE_STRING (_cm_os,
		"Generated on Machine: " MACHINE ", OS Name: " SYSNAME
		", OS Revision: " __OC_STR__ (SYSVERSION));

#endif /* OC_REVSTRING_H */
