#ifndef EZK_PLATFORM_INCLUDED
#define EZK_PLATFORM_INCLUDED

// TODO: MORE OSes for completion's sake

#if defined(__linux__) && !defined(__ANDROID__)
#define EZK_LINUX
#endif 

#if defined(_WIN16) || defined(_WIN32) || defined (_WIN64)
#define EZK_WINDOWS
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__bsdi__) || defined(__DragonFly__)
#define EZK_BSD
#endif

#if defined(__APPLE__) && defined(__MACH__)
#define EZK_OSX
#endif

#endif // EZK_PLATFORM_INCLUDED

