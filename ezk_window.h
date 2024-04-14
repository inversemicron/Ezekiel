// This is a WORK IN PROGRESS, and should not be used to any capacity professionally. Also currently its is a carbon copy of SOKOL so use that instead.
#ifndef EZK_WINDOW_INCLUDED // include guard
#define EZK_WINDOW_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Determine window system to use
#if defined(_WIN32) || defined(_WIN64)
	#define EZK_WIN32 // as in win32api
#elif defined(__ANDROID__)
	#define EZK_ANDROID
#elif defined(__linux__) || defined(__unix__) // android has already been checked for
	#define EZK_X11 
#else
	#error "Your operating system is not supported"
#endif

// Includes
#if defined(EZK_WIN32)
	#include "Windows.h"
#elif defined(EZK_X11)
	#include <X11/Xlib.h>
#endif

// Backends

#if defined(EZK_X11) // TODO: Add in support for GLES
	#ifdef EZK_GL
		#define EZK_GLX
		#include <GL/gl.h>
		#include <GL/glx.h>
	#else
		#error "No supported linux backend selected."
	#endif
#endif 

// Macros

#ifndef EZK_ASSERT
	#include <assert.h> 
	#define EZK_ASSERT(x) assert(x)  
#endif

#define EZK_DEF_WINDOW_HEIGHT 600
#define EZK_DEF_WINDOW_WIDTH 800

#ifndef _EZK_PRIVATE
	#define _EZK_PRIVATE static
#endif
#ifndef EZK_API_DECL 
	#define EZK_API_DECL extern
#endif
#ifndef EZK_API_IMPL
	#define EZK_API_IMPL 
#endif

// Declarations

typedef enum {
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
	// For windows requesting changes
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
} ezkwin_event_type; 

typedef struct {
	ezkwin_event_type type;
	int keycode;
} ezkwin_event;

// X11 
#ifdef EZK_X11
typedef struct {
	Display* display;
	Window window;
	Screen* screen;
	int screenId;
	Window root;

	Colormap colormap;
} ezkwin_x11_inst;

#ifdef EZK_GLX
typedef struct {
	int vMajor;
	int vMinor;

	GLXContext ctx;
} ezkwin_glx_inst;
#endif // EZK_GLX
#endif

typedef struct _ezkwin {
	int width;
	int height;
	int fullscreen;
	ezkwin_event event;

	bool quit;
#ifdef EZK_X11
	ezkwin_x11_inst x11;
	#ifdef EZK_GLX
		ezkwin_glx_inst glx;
	#endif
#endif
} ezk_window_instance;

static ezk_window_instance _ezkwin; // TODO: change to allow multiple instances

EZK_API_DECL void ezkwin_run();

#ifdef EZK_X11

#ifdef EZK_GLX
	_EZK_PRIVATE void ezkwin_glx_init() {
		glXQueryVersion(_ezkwin.x11.display, &_ezkwin.glx.vMajor, &_ezkwin.glx.vMinor);
		if (_ezkwin.glx.vMajor <= 1 && _ezkwin.glx.vMinor <= 2) {
			printf("GLX 1.2 or earlier is not supported\n");
			abort();
		}
	}
	
	_EZK_PRIVATE void ezkwin_glx_choose_fbconfig() {

	}

	_EZK_PRIVATE void ezkwin_glx_choose_visual() {

	}
#endif

_EZK_PRIVATE void ezkwin_x11_create_window() {
	_ezkwin.x11.window = XCreateSimpleWindow( // yeah this needs work
		_ezkwin.x11.display, 
		RootWindow(_ezkwin.x11.display, _ezkwin.x11.screenId), 
		0, 0, 
		_ezkwin.width, _ezkwin.height,
		2,
		BlackPixel(_ezkwin.x11.display, _ezkwin.x11.screenId),
		WhitePixel(_ezkwin.x11.display, _ezkwin.x11.screenId));
}

_EZK_PRIVATE void ezkwin_x11_show_window() {
	XMapWindow(_ezkwin.x11.display, _ezkwin.x11.window);	
}

_EZK_PRIVATE void ezkwin_x11_run() { 	
	XEvent ev; // temporary

	_ezkwin.x11.display = XOpenDisplay(NULL); // TODO: Add in support for various displays
	if(!_ezkwin.x11.display) {
		printf("Failed to open X11 display.\n");
	}

	_ezkwin.x11.screen = DefaultScreenOfDisplay(_ezkwin.x11.display); // TODO: add in support for multiple screens
	_ezkwin.x11.screenId = DefaultScreen(_ezkwin.x11.display);
	
#ifdef EZK_GLX
	ezkwin_glx_init();
	ezkwin_glx_choose_fbconfig();
	ezkwin_glx_choose_visual();	
#endif

	ezkwin_x11_create_window();
	
	ezkwin_x11_show_window();

	while (true) {
		if(XPending(_ezkwin.x11.display) > 0) {
			XNextEvent(_ezkwin.x11.display, &ev);
		}
	}
}



#endif // EZK_X11

_EZK_PRIVATE void ezkwin_init_inst() { 
	_ezkwin.width = _ezkwin.width ? _ezkwin.width : EZK_DEF_WINDOW_WIDTH;
	_ezkwin.height = _ezkwin.height ? _ezkwin.height : EZK_DEF_WINDOW_HEIGHT;
}

// Implementation
#ifdef EZK_IMPL

EZK_API_IMPL void ezkwin_run() {
	ezkwin_init_inst();
#ifdef EZK_X11
	ezkwin_x11_run();
#endif
}

#endif // EZK_IMPDL

#endif // EZK_WINDOW_INCLUDED
