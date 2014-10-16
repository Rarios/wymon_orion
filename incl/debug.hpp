// debug.hpp

#ifndef _DEBUG_
#define _DEBUG_

#ifndef _GGNAMESPACE_
	#include "namespace.hpp"
#endif

// debug (macro) //
// The debug macro takes an expression and simply writes it again, so it can be executed. However, if "NDEBUG" is defined
// it won't write the expression, which means that the expression is still in the code, but won't be used. Perfect for
// expressions only used if system is set to console, because if it is changed to windows later on, they will disappear in
// execution.

START_GG

//#define NDEBUG // Enable for disabling debugging mode

#ifdef NDEBUG
	#define debug(x)
#else
	#define debug(x) x
#endif

END_GG

#endif