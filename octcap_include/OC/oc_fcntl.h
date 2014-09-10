/**
 * @file oc_fcntl.h
 * @brief wrapper POSIX Standard: 6.5 File Control Operations
 * 
 * Use it using:
 * 
 * @verbatim
 * #include <OC/oc_fcntl.h>
 * @endverbatim
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */


#ifndef OC_FCNTL_H
#define OC_FCNTL_H

#include <OC/oc_config.h>

#ifdef __linux

/*
 * necessary to bring the equivalent of fcntl.h on HP-UX
 */

#include <sys/types.h>
#include <unistd.h>

#endif /* __linux */

#include <fcntl.h>

#endif /* OC_FCNTL_H */

