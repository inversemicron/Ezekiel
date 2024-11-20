#ifndef EZK_INCL
#define EZK_INCL

#if defined(EZK_DLL_BUILD)
  #define EZKAPI __declspec(dllexport)
#elif defined(EZK_USE_DLL)
  #define EZKAPI __declspec(dllimport)
  #define EZK_INCLUDES
#elif defined(EZK_SO_BUILD)
  #define EZKAPI __attribute__((visibility("default")))
#endif

#ifndef EZKAPI
  #define EZKAPI
  #define EZK_INCLUDES
#endif 

#ifdef EZK_INCLUDES
#include "ezk_window.h"
#endif

#endif // EZK_INCL