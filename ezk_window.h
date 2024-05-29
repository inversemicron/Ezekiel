// This is a WORK IN PROGRESS, and should not be used to any capacity professionally. Also currently its is a carbon copy of SOKOL so use that instead.
#ifndef EZK_WINDOW_INCLUDED // include guard
#define EZK_WINDOW_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>

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

// this is going to end up being a macro monster, sorry NASA :(
#ifndef EZK_DEF_WIN_HEIGHT
#define EZK_DEF_WIN_HEIGHT 600
#endif
#ifndef EZK_DEF_WIN_WIDTH 
#define EZK_DEF_WIN_WIDTH 800
#endif

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

#ifdef EZK_WIN

// Events
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
#ifdef EZK_GL 
  
#endif
// X11 

#ifdef EZK_GL 
  typedef struct {
    int id;
    uint8_t red_bits,
            green_bits,
            blue_bits,
            alpha_bits,
            depth_bits,
            stencil_bits,
            samples;
    bool doublebuffer;

    GLXFBConfig handle;
  } ezk_gl_fbconfig  ;

#ifdef EZK_GLX
typedef struct {
	int vMajor;
	int vMinor;

	GLXContext ctx;
} ezkwin_glx_inst;
#endif // EZK_GLX
#endif

#ifdef EZK_X11
typedef struct {
	Display* display;
	Window window;
	Screen* screen;
	int screenId;
	Window root;

  ezk_gl_fbconfig fbc;
  XVisualInfo* visual;

  XSetWindowAttributes win_attribs; // TODO: centralise window attributes into ezk_window_attribs
	Colormap colormap;
} ezkwin_x11_inst;
#endif

typedef struct {
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

#endif // EZK_WIN

typedef struct {
#ifdef EZK_WIN
  ezk_window_instance** windows;
 
#ifndef EZK_16_BIT_WIN_IDS
  uint8_t window_count;
#else
  uint16_t window_count;
#endif
  
#endif // EZK_WIN

} ezk_instance;

static ezk_window_instance* _ezkwin; // current window
static ezk_instance _ezk;

#ifdef EZK_WIN
EZK_API_DECL int ezk_init_window();
#endif

#ifdef EZK_WIN
#ifdef EZK_GL

  _EZK_PRIVATE void ezk_gl_print_fbconfig(ezk_gl_fbconfig f) {
    printf("## FRAMEBUFFER CONFIG %d\n", f.id);
    printf("## Red bits: %d\n", f.red_bits);
    printf("## Green bits: %d\n", f.blue_bits);    
    printf("## Blue bits: %d\n", f.green_bits);
    printf("## Alpha bits: %d\n", f.alpha_bits);
    printf("## Depth bits: %d\n", f.depth_bits);
    printf("## Stencil bits: %d\n", f.stencil_bits);
    printf("## Samples: %d\n", f.samples);
    printf("## Doublebuffer: %s\n", f.doublebuffer ? "Yes" : "No");
  }

  _EZK_PRIVATE double ezk_gl_eval_fbconfig(ezk_gl_fbconfig d, ezk_gl_fbconfig e) { // desired fb config, config to eval
    register int red_err = (d.red_bits - e.red_bits);
    register int green_err = (d.green_bits - e.green_bits);
    register int blue_err = (d.blue_bits - e.blue_bits);
    register int alpha_err = (d.alpha_bits - e.alpha_bits);
    register int depth_err = (d.depth_bits - e.depth_bits);
    register int stencil_err = (d.stencil_bits - e.stencil_bits);
    register int sample_err = (d.samples - e.samples);
    register int doublebuffer_err = d.doublebuffer ? (e.doublebuffer ? 0 : 100) : (e.doublebuffer ? 100 : 0);

    double return_value = sqrt(
          (red_err * red_err) +
          (green_err * green_err) +
          (blue_err * blue_err) +
          (alpha_err * alpha_err) +
          (depth_err * depth_err) +
          (stencil_err * stencil_err) +
          (sample_err * sample_err) +
          (doublebuffer_err) // already accounted for squaring doublebuffer  
        );
    return return_value;
  }

  _EZK_PRIVATE ezk_gl_fbconfig ezk_gl_select_fbconfig(ezk_gl_fbconfig desired, ezk_gl_fbconfig* usable, int count) {
      ezk_gl_fbconfig best_fbconfig;
      double lowest_score = 0xffffffff; 
      for(int i = 0; i < count; i++) {
        double score = ezk_gl_eval_fbconfig(desired, usable[i]);
        if(score < lowest_score) {
          lowest_score = score;
          best_fbconfig = usable[i];
        }
      }
      return best_fbconfig; 
  }

#ifdef EZK_GLX
  _EZK_PRIVATE int ezk_glx_attrib(GLXFBConfig c, int a) {
    int value;
    glXGetFBConfigAttrib(_ezkwin->x11.display, c, a, &value);
    return value;
  }  

	_EZK_PRIVATE void ezk_glx_init() {
		glXQueryVersion(_ezkwin->x11.display, &_ezkwin->glx.vMajor, &_ezkwin->glx.vMinor);
		if (_ezkwin->glx.vMajor <= 1 && _ezkwin->glx.vMinor <= 2) {
			printf("GLX 1.2 or earlier is not supported\n");
			abort();
		}
	}
	
  _EZK_PRIVATE ezk_gl_fbconfig ezk_glx_choose_fbconfig() {
      GLXFBConfig* nativeConfigs;
      ezk_gl_fbconfig* usableConfigs;
      int nativeConfigCount = 0;
      int usableConfigCount = 0;
      
      nativeConfigs = glXGetFBConfigs(_ezkwin->x11.display, _ezkwin->x11.screenId, &nativeConfigCount);
      
      usableConfigs = malloc(sizeof(ezk_gl_fbconfig) * nativeConfigCount);
      memset(usableConfigs, 0, sizeof(ezk_gl_fbconfig) * nativeConfigCount);
      
      for(int i = 0; i < nativeConfigCount; i++) {
        const GLXFBConfig h = nativeConfigs[i];
        ezk_gl_fbconfig* t = usableConfigs + usableConfigCount;
        usableConfigCount++;
        
        if ((ezk_glx_attrib(h, GLX_RENDER_TYPE) & GLX_RGBA_BIT) == 0) {
          continue; // TODO: support CLUTs
        }

        if ((ezk_glx_attrib(h, GLX_DRAWABLE_TYPE) & GLX_WINDOW_BIT) == 0) {
          continue; // TODO: support PBUFFERs and PIXMAPs for RTT
        }

        t->id = ezk_glx_attrib(h, GLX_FBCONFIG_ID);

        t->red_bits = ezk_glx_attrib(h, GLX_RED_SIZE);
        t->green_bits = ezk_glx_attrib(h, GLX_GREEN_SIZE);
        t->blue_bits = ezk_glx_attrib(h, GLX_BLUE_SIZE);        
        t->alpha_bits = ezk_glx_attrib(h, GLX_ALPHA_SIZE);
        t->depth_bits = ezk_glx_attrib(h, GLX_DEPTH_SIZE);
        t->stencil_bits = ezk_glx_attrib(h, GLX_STENCIL_SIZE);

        // TODO: add in support for extensions, for now just pray that ARB multisampling is enabled. (for no reason)
        t->samples = ezk_glx_attrib(h, GLX_SAMPLES);

        t->doublebuffer = ezk_glx_attrib(h, GLX_DOUBLEBUFFER);

        // TODO: add in support for stereo rendering if we want to make VR games
        // TODO: add in support for auxilliary buffers, to store more stencil values or depth bits

        t->handle = h; 
      }

      // Now this returns quite a few framebuffer configs, so now we need to select one!
      ezk_gl_fbconfig desired;

      desired.red_bits = 8;
      desired.green_bits = 8;
      desired.blue_bits = 8;
      desired.alpha_bits = 8;
      desired.depth_bits = 24;
      desired.stencil_bits = 8;
      desired.samples = 8; // TODO: allow the developer to specify a number of samples (actually everything)
      desired.doublebuffer = true;

      ezk_gl_fbconfig chosen = ezk_gl_select_fbconfig(desired, usableConfigs, usableConfigCount);
      
      free(nativeConfigs);
      free(usableConfigs);
      //ezk_gl_print_fbconfig(desired);
      //ezk_gl_print_fbconfig(chosen);
      //printf("Difference: %d\n", ezk_gl_eval_fbconfig(desired, chosen));

      return chosen; 
	}

	_EZK_PRIVATE void ezk_glx_choose_visual(ezk_gl_fbconfig *fbc, XVisualInfo **v) {
    *fbc = ezk_glx_choose_fbconfig();

    *v = glXGetVisualFromFBConfig(_ezkwin->x11.display, fbc->handle);
	}
#endif // EZK_GLX
#endif // EZK_GL

#ifdef EZK_X11

_EZK_PRIVATE void ezk_x11_create_window() {
	_ezkwin->x11.window = XCreateWindow( 
    _ezkwin->x11.display, 
		_ezkwin->x11.root, 
		0, 0, // window position
		_ezkwin->width, _ezkwin->height,
		0, // border width
	  _ezkwin->x11.visual->depth,
    InputOutput,
    _ezkwin->x11.visual->visual,
		CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
    &_ezkwin->x11.win_attribs);
} 

_EZK_PRIVATE void ezk_x11_show_window() {
	XMapWindow(_ezkwin->x11.display, _ezkwin->x11.window);	
}

_EZK_PRIVATE void ezk_x11_run() {	
	XEvent ev; // temporary

	_ezkwin->x11.display = XOpenDisplay(NULL); // TODO: Add in support for various displays
	if(!_ezkwin->x11.display) {
		printf("Failed to open X11 display.\n");
	}

	_ezkwin->x11.screen = DefaultScreenOfDisplay(_ezkwin->x11.display); // TODO: add in support for multiple screens
                                                                    // X11 tends to assign multiple monitors to 
									                                                  // one screen so this might not be necessary 
	_ezkwin->x11.screenId = DefaultScreen(_ezkwin->x11.display);
  _ezkwin->x11.root = RootWindow(_ezkwin->x11.display, _ezkwin->x11.screenId);
#ifdef EZK_GLX
	ezk_glx_init();

	ezk_glx_choose_visual(&_ezkwin->x11.fbc, &_ezkwin->x11.visual);	
#endif
  
  // Setup window attributes
	_ezkwin->x11.win_attribs.border_pixel = BlackPixel(_ezkwin->x11.display, _ezkwin->x11.screenId);
  _ezkwin->x11.win_attribs.background_pixel = WhitePixel(_ezkwin->x11.display, _ezkwin->x11.screenId);
	_ezkwin->x11.win_attribs.override_redirect = True;
	_ezkwin->x11.win_attribs.colormap = XCreateColormap(_ezkwin->x11.display, _ezkwin->x11.root, 
                                                     _ezkwin->x11.visual->visual, AllocNone);
	_ezkwin->x11.win_attribs.event_mask = ExposureMask;

	ezk_x11_create_window();
	
	ezk_x11_show_window();

  while (!_ezkwin->quit) {
    if(XPending(_ezkwin->x11.display) > 0) {
      XNextEvent(_ezkwin->x11.display, &ev);
      // Process the event here
    } else {
      struct timespec sleep_time;
      sleep_time.tv_sec = 0;
      sleep_time.tv_nsec = 1000000; // Sleep for 10 milliseconds
      nanosleep(&sleep_time, NULL); // This is to prevent busy waiting, TODO: change to allow various polling rates
    }
  }
}



#endif // EZK_X11

// Implementation
#ifdef EZK_IMPL

EZK_API_IMPL int ezk_alloc_window() {
  if (!_ezk.windows) _ezk.windows = malloc(0);

  uint16_t id = 0;
  bool found = false;
  for(;id < _ezk.window_count; id++) {
    if(!_ezk.windows[id]) { // if there is no pointer there, its free to use
      found = true;
      break;
    }
  }
  
  if (!found) {
    _ezk.windows = realloc(_ezk.windows, (_ezk.window_count + 1) * sizeof(ezk_window_instance*));
    id = _ezk.window_count++;
  }

  printf("%d\n", id);

  ezk_window_instance** new_inst = &(_ezk.windows[id]);
  *new_inst = (ezk_window_instance*)malloc(sizeof(ezk_window_instance));

  _ezkwin = *new_inst; // make it the current window
}

#endif // EZK_WIN

#endif // EZK_IMPL

#endif // EZK_WINDOW_INCLUDED
