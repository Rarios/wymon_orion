// Namespace definitions for WymonOrion project.

#ifndef WO_NAMESPACE
#define WO_NAMESPACE

//! WymonOrion namespace opening macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef OPEN_WO
	#undef OPEN_WO
	#define OPEN_WO namespace wo {
#else
	#define OPEN_WO namespace wo {
#endif

//! WymonOrion namespace closing macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef CLOSE_WO
	#undef CLOSE_WO
	#define CLOSE_WO }
#else
	#define CLOSE_WO }
#endif

//! WymonOrion system module namespace opening macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef OPEN_WO_SYS
	#undef OPEN_WO_SYS
	#define OPEN_WO_SYS namespace wo { namespace sys {
#else
	#define OPEN_WO_SYS namespace wo { namespace sys {
#endif

//! WymonOrion system module namespace closing macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef CLOSE_WO_SYS
	#undef CLOSE_WO_SYS
	#define CLOSE_WO_SYS } }
#else
	#define CLOSE_WO_SYS } }
#endif

//! WymonOrion window module namespace opening macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef OPEN_WO_WIN
	#undef OPEN_WO_WIN
	#define OPEN_WO_WIN namespace wo { namespace win {
#else
	#define OPEN_WO_WIN namespace wo { namespace win {
#endif

//! WymonOrion window module namespace closing macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef CLOSE_WO_WIN
	#undef CLOSE_WO_WIN
	#define CLOSE_WO_WIN } }
#else
	#define CLOSE_WO_WIN } }
#endif

//! WymonOrion graphics module namespace opening macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef OPEN_WO_GFX
	#undef OPEN_WO_GFX
	#define OPEN_WO_GFX namespace wo { namespace gfx {
#else
	#define OPEN_WO_GFX namespace wo { namespace gfx {
#endif

//! WymonOrion graphics module namespace closing macro.
/*!
* ATTENTION: Any previous definition of this macro will be overwritten.
*/
#ifdef CLOSE_WO_GFX
	#undef CLOSE_WO_GFX
	#define CLOSE_WO_GFX } }
#else
	#define CLOSE_WO_GFX } }
#endif

#endif
