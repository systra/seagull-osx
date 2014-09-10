/**
 * @file oc_fstream.H
 * @brief wrapper over C++ <fstream>
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_fstream.H>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_FSTREAM_H
#define _OC_FSTREAM_H

#include <OC/oc_config.h>

#ifdef __hpux
# ifdef __HP_aCC
#  if defined(_HP_NAMESPACE_STD)
/*
 * ANSI C++ Standard feature
 */
#   include <fstream>
using namespace std;
#  else  // !_HP_NAMESPACE_STD
#   include <fstream.h>
#  endif // !_HP_NAMESPACE_STD
# endif  // __HP_aCC
#else
/* ANSI C++ */
# include <fstream>
#endif

#endif // _OC_FSTREAM_H
