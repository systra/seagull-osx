/**
 * @file oc_stdsyms.h
 * @brief provide HP-UX <sys/stdsyms.h> equivalent Linux
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_stdsyms.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_STDSYMS_H
#define OC_STDSYMS_H

#include <OC/oc_config.h>

#ifdef __linux
#include <unistd.h>
#else  /* !__linux */
#include <sys/stdsyms.h>
#endif /* __linux */

#endif /* OC_STDSYMS_H */

