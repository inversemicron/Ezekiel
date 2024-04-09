#ifndef EZK_WINDOW_INCLUDED // include guard
#define EZK_WINDOW_INCLUDED

// Determine window system to use
#if defined(_WIN32) || defined(_WIN64)
	#define EZK_WIN32 // as in win32api
#elif defined(__ANDROID__)
	#define EZK_ANDROID
#elif defined(__linux__) || defined(__unix__) // android has already been checked for
	#define EZK_X11 
#else
	#error "Your operating system is not support"
#endif

// Includes
#if defined(EZK_WIN32)
	#include "Windows.h"
#elif defined(EZK_X11)
	#include <X11/Xlib.h>
#endif

// Declarations

void ezk_init_inst();

typedef enum ezk_event_type_major {
	EZK_EVTYPE_KEY_DOWN,
	EZK_EVTYPE_KEY_UP,
	EZK_EVTYPE_BUTTON_DOWN,
	EZK_EVTYPE_BUTTON_UP,
	EZK_EVTYPE_BUTTON_MOTION,
	EZK_EVTYPE_MOUSE_ENTER,
	EZK_EVTYPE_MOUSE_LEAVE,
	EZK_EVTYPE_FOCUS_GAIN,
	EZK_EVTYPE_FOCUS_LOSS,
	EZK_EVTYPE_KEYMAP_CHANGE, // for changing languages
	EZK_EVTYPE_EXPOSE, // These three might need merging into one to support windows :P
	EZK_EVTYPE_GRAPHICS_EXPOSE,
	EZK_EVTYPE_NO_EXPOSE,
	// For requesting changes
	EZK_EVTYPE_CIRCULATE_REQUEST, // Change stacking order of window
	EZK_EVTYPE_CONFIGURE_REQUEST, // Change size or position of window
	EZK_EVTYPE_MAP_REQUEST, // Make a new window
	EZK_EVTYPE_RESIZE_REQUEST, // Resize window
	// For notifying when changes happen
	EZK_EVTYPE_CIRCULATE_NOTIFY,
	EZK_EVTYPE_CONFIGURE_NOTIFY,
	EZK_EVTYPE_CREATE_NOTIFY,
	EZK_EVTYPE_DESTROY_NOTIFY,
	EZK_EVTYPE_GRAVITY_NOTIFY, // To do with parent windows, might not be needed
	EZK_EVTYPE_MAP_NOTIFY,
	EZK_EVTYPE_MAPPING_NOTIFY,
	EZK_EVTYPE_REPARENT_NOTIFY,
	EZK_EVTYPE_UNMAP_NOTIFY,
	EZK_EVTYPE_VISIBILITY_NOTIFY,
	EZK_EVTYPE_COLORMAP_NOTIFY,
	EZK_EVTYPE_CLIENT_MESSAGE,
	EZK_EVTYPE_PROPERTY_NOTIFY,
	EZK_EVTYPE_SELECTION_CLEAR,
	EZK_EVTYPE_SELECTION_NOTIFY,
	EZK_EVTYPE_SELECTION_REQUEST
} ezk_event_type; // README::: make sure you know what all of these do!

typedef struct ezk_event {
	ezk_event_type type;
} ezk_event;

// X11 
#ifdef EZK_X11
typedef struct ezk_x11_inst {
	Display* display;
	Window window;
	Screen* screen;

	XSetWindowAttributes attribs;
} ezk_x11_inst;
#endif

typedef struct ezk_inst {
	int width;
	int height;
	int fullscreen;
	ezk_event event;
#ifdef EZK_X11
	ezk_x11_inst x11_inst;
#endif
} ezk_inst;

static ezk_inst ezk;

// Implementation
#ifdef EZK_IMPL
#ifndef EZK_API_IMPL
	#define EZK_API_IMPL
#endif

#endif // EZK_IMPL

#endif // EZK_WINDOW_INCLUDED
