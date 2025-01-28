#ifndef EZK_INCL
#define EZK_INCL

#if defined(EZK_DLL_BUILD)
  #define EZKAPI __declspec(dllexport)
#elif defined(EZK_USE_DLL)
  #define EZKAPI __declspec(dllimport)
  #define EZK_INCLUDES
#elif defined(EZK_SO_BUILD)
  #define EZKAPI __attribute__((visibility("default")))
#else
  #define EZK_INCLUDES
#endif

#if !defined(EZK_INCLUDES) // we are compiling the library in place or to a library file
  #include "../src/ezk_window.h"
#else // we are using symbols and loading from a library file
  #define EZKAPI
  #include "ezk_window.h"
#endif // EZKAPI

static const int make_iso_compilers_happy;
#endif // EZK_INCL