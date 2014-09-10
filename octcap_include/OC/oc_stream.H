/**
 * @file oc_stream.H
 * @brief wrapper over ANSI C++ <*stream>
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_stream.H>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_STREAM_H
#define _OC_STREAM_H
#ifdef __cplusplus

#include <OC/oc_config.h>

#define DECLARE_STRSTREAM							\
class ostrstream : public ostringstream {					\
public:										\
	ostrstream( ) : ostringstream( ) {};					\
	ostrstream( char* cstr, int len )					\
	{ *this << string ( cstr, len ) << ends; };				\
	inline const char* str( void )						\
	{ return std::ostringstream::str().c_str(); };				\
};										\
class istrstream : public istringstream {					\
public:										\
	inline const char* str( void )						\
	{ return std::istringstream::str().c_str(); };				\
}

#if defined(__hpux) && defined(__HP_aCC)
# if defined(_HP_NAMESPACE_STD)
/*
 * ANSI C++ Standard feature
 */
#  include <fstream>
#  include <iostream>
#  include <stdio.h>
#  include <strstream>
using namespace std;
# else  // !_HP_NAMESPACE_STD
/*
 * aCC delivers the following files into </opt/aCC/include/iostream>, which
 * must be added to the INCPATH of the compilation command-line
 */
#  include <fstream.h>
#  include <iostream.h>
#  include <stream.h>
#  include <strstream.h>
# endif // !_HP_NAMESPACE_STD

#elif defined(__GNUG__)
/*
 * GCC
 */
# include <fstream>
# include <iostream>
# include <sstream>
# if (__GNUC__ >= 3 )
// GCC-3.x is mostly ANSI C++ compliant
#  include <ostream>
#  include <istream>
// backward compatibility with no warnings
#  include <string>
DECLARE_STRSTREAM;
# else // __GNUC__ < 3
// GCC-2.x
#  include <strstream.h>
# endif// __GNUC__ < 3

#elif (__cplusplus >= 199711L)
/*
 * strict ANSI C++ conformance
 */
# include <fstream>
# include <iostream>
# include <sstream>
# include <ostream>
# include <istream>
// backward compatibility with no warnings
#  include <string>
DECLARE_STRSTREAM;

#elif defined(_WIN32)

#include <windows.h>
#include <strstrea.h>

#else
# warning "*** Un-supported C++ compiler.  Use GNU C++, HP aCC or another ANSI C++ compiler"
#endif

#undef DECLARE_STRSTREAM

#endif // __cplusplus
#endif // _OC_STREAM_H
