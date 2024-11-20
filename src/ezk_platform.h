#ifndef EZK_PLAT_INCL
#define EZK_PLAT_INCL

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__))
  #define EZK_LINUX
#elif defined(__APPLE__) && defined(__MACH__) || defined(macintosh) || defined(Macintosh)
  #define EZK_APPLE
#elif defined(_WIN64) || defined(_WIN32)
  #define EZK_WINDOWS
#else
 #error "EZK::PREPROCESS::FATAL::UNSUPPORTED_PLATFORM"
#endif 

#endif // EZK_PLAT_INCL