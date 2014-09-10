/**
 * @file oc_dlfcn.h
 * @brief Portable wrapper on user functions for run-time dynamic loading
 * 
 * Use it using:
 * 
 * @verbatim
 * #include <OC/oc_dlfcn.h>
 * @endverbatim
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_DLFCN_H
#define OC_DLFCN_H

#include <OC/oc_config.h>

#include <dlfcn.h>
#ifdef __linux
#include <OC/oc_sysdl.h>
#endif /* __linux */


#endif /* OC_DLFCN_H */
