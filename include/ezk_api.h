#ifndef EZK_API_INCL
#define EZK_API_INCL

#if defined(EZK_DLL_BUILD)
  #define EZKAPI __declspec(dllexport)
#elif defined(EZK_USE_DLL)
  #define EZKAPI __declspec(dllimport)
#elif defined(EZK_SO_BUILD)
  #define EZKAPI __attribute__((visibility("default")))
#endif

#ifndef EZKAPI // we are compiling the library in place
  #define EZKAPI
#endif 

#endif // EZK_API_INCL
