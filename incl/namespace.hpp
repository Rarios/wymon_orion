// GG namespace

#ifndef _GGNAMESPACE_
#define _GGNAMESPACE_

//! Macro for opening the namespace "gg"
#ifndef START_GG
	#define START_GG namespace gg {
#else
	#undef START_GG
	#define START_GG namespace gg {
#endif

//! Macro for closing the namespace "gg"
#ifndef END_GG
	#define END_GG }
#else
	#undef END_GG
	#define END_GG }
#endif

//! Macro for opening namespace "python", used for all Python extending code
#ifndef START_PYHTON
	#define START_PYTHON namespace python {
#else
	#undef START_PYTHON
	#define START_PYTHON namespace python {
#endif

//! Macro for closing the namespace "python"
#ifndef END_PYTHON
	#define END_PYTHON }
#else
	#undef END_PYTHON
	#define END_PYTHON }
#endif

#endif