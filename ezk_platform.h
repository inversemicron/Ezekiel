#ifndef EZK_PLATFORM_INCLUDED
#define EZK_PLATFORM_INCLUDED

// TODO: MORE OSes for completion's sake

// Determining main OS

#if defined(__linux__) && !defined(__ANDROID__)
	#define EZK_LINUX
#endif 

#if defined(_WIN16) || defined(_WIN32) || defined (_WIN64)
	#define EZK_WINDOWS // if it is 16 bits, it is literally win 3.1 or earlier (not good) - check the ARCHITECTURE
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__bsdi__) || defined(__DragonFly__)
	#define EZK_BSD
#endif

#if defined(__APPLE__) && defined(__MACH__)
	#define EZK_OSX
#endif

#if defined(EZK_BSD) || defined(EZK_LINUX)
#define EZK_UNIX // Unix like systems
#endif

// Determining architecture
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(_M_ARM64)
	#define EZK_ARCH 64
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__) || defined(_M_ARM)
	#define EZK_ARCH 32
#else
	#define EZK_ARCH 0xffffffffffffffff // infinite bits - there is probably a better way to do this
#endif

// Determine window system
#if defined(EZK_UNIX)
	#define EZK_X11
#elif defined(EZK_WINDOWS) && EZK_ARCH >= 32 // as stated earlier, 16 bit windows is not desirable (Win 3.1 or earlier)
	#define EZK_WIN32API
#elif defined (EZK_OSX)
	#define EZK_COCOA
#endif

#endif // EZK_PLATFORM_INCLUDED

