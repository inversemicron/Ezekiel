// This is a WORK IN PROGRESS, and should not be used to any capacity professionally. Also currently its is a carbon copy of SOKOL so use that instead.

// wiggle - WGL, windows GL
// eagle - EGL


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
	#define EZK_WIN32 // as in _ezk_curwin32api
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

typedef enum {
  EZK_BACKEND_GL,
  EZK_BACKEND_VULKAN,
  EZK_BACKEND_D3D,
  EZK_BACKEND_NONE
} ezk_backend_type;

// Macros

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

#define ezk_zero_var(v) memset(&v, 0, sizeof(v))
#define ezk_zero_ptr(p) memset(p, 0, sizeof(*p))

// Declarations

#ifdef EZK_WIN

// Events
typedef enum {
  EZK_EVTYPE_NONE, // there so that type does not default to keypress
  EZK_EVTYPE_KEYPRESS,
  EZK_EVTYPE_KEYRELEASE,
  EZK_EVTYPE_BUTTONPRESS,
  EZK_EVTYPE_BUTTONRELEASE,
  EZK_EVTYPE_MOTIONNOTIFY,
  EZK_EVTYPE_ENTERNOTIFY,
  EZK_EVTYPE_LEAVENOTIFY,
  EZK_EVTYPE_FOCUSIN,
  EZK_EVTYPE_FOCUSOUT,
  EZK_EVTYPE_EXPOSE,
  EZK_EVTYPE_GRAPHICSEXPOSE,
  EZK_EVTYPE_NOEXPOSE,
  EZK_EVTYPE_VISIBILITYNOTIFY,
  EZK_EVTYPE_CREATENOTIFY,
  EZK_EVTYPE_DESTROYNOTIFY,
  EZK_EVTYPE_UNMAPNOTIFY,
  EZK_EVTYPE_MAPNOTIFY,
  EZK_EVTYPE_MAPREQUEST,
  EZK_EVTYPE_REPARENTNOTIFY,
  EZK_EVTYPE_CONFIGURENOTIFY,
  EZK_EVTYPE_CONFIGUREREQUEST,
  EZK_EVTYPE_GRAVITYNOTIFY,
  EZK_EVTYPE_RESIZEREQUEST, 
  EZK_EVTYPE_CIRCULATENOTIFY,
  EZK_EVTYPE_CIRCULATEREQUEST,
  EZK_EVTYPE_PROPERTYNOTIFY,
  EZK_EVTYPE_SELECTIONCLEAR,
  EZK_EVTYPE_SELECTIONNOTIFY,
  EZK_EVTYPE_CLIENTMESSAGE,
  EZK_EVTYPE_MAPPINGNOTIFY,
  EZK_EVTYPE_KEYMAPNOTIFY,
  EZK_EVTYPE_GENERIC
} ezk_event_type; // based off of x11 docs, subject to change

typedef enum {
   EZK_WINTYPE_X11,
   EZK_WINTYPE_WIN32,
   EZK_WINTYPE_COCOA
} ezk_win_type;

typedef struct {
	ezk_event_type type;
	int keycode;
  Time time;
  int mx, my;
} ezk_event;
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
  } ezk_gl_fbconfig;

#ifdef EZK_GLX
typedef struct {
	int vMajor;
	int vMinor;

	GLXContext ctx;
} ezk_glx_inst;
#endif // EZK_GLX
#endif

#ifdef EZK_X11
typedef struct {
	Display* display;
	Window window;
	Screen* screen;
	int screen_id;
	Window root;

  ezk_gl_fbconfig fbc;
  XVisualInfo* visual;

  XSetWindowAttributes win_attribs; // TODO: centralise window attributes into ezk_window_attribs
	Colormap colormap;
} ezk_x11_inst;
#endif

typedef struct {
	int width;
	int height;
	int fullscreen;
	ezk_event event;

	bool quit;

  ezk_win_type platform;
#ifdef EZK_X11
	ezk_x11_inst x11;
	#ifdef EZK_GLX
		ezk_glx_inst glx;
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

static ezk_window_instance* _ezk_curwin;
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
    glXGetFBConfigAttrib(_ezk_curwin->x11.display, c, a, &value);
    return value;
  }  

	_EZK_PRIVATE void ezk_glx_init() {
		glXQueryVersion(_ezk_curwin->x11.display, &_ezk_curwin->glx.vMajor, &_ezk_curwin->glx.vMinor);
		if (_ezk_curwin->glx.vMajor <= 1 && _ezk_curwin->glx.vMinor <= 2) {
			printf("GLX 1.2 or earlier is not supported\n");
			abort();
		}
	}
	
  _EZK_PRIVATE ezk_gl_fbconfig ezk_glx_choose_fbconfig() {
      GLXFBConfig* nativeConfigs;
      ezk_gl_fbconfig* usableConfigs;
      int nativeConfigCount = 0;
      int usableConfigCount = 0;
      
      nativeConfigs = glXGetFBConfigs(_ezk_curwin->x11.display, _ezk_curwin->x11.screen_id, &nativeConfigCount);
      
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

    *v = glXGetVisualFromFBConfig(_ezk_curwin->x11.display, fbc->handle);
	}
#endif // EZK_GLX
#endif // EZK_GL

#ifdef EZK_X11

_EZK_PRIVATE void ezk_x11_create_window() {
	_ezk_curwin->x11.window = XCreateWindow( 
    _ezk_curwin->x11.display, 
		_ezk_curwin->x11.root, 
		0, 0, // window position
		1600, 900, // TODO: replace with non-placeholder values
		0, // border width
	  _ezk_curwin->x11.visual->depth,
    InputOutput,
    _ezk_curwin->x11.visual->visual,
		CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
    &_ezk_curwin->x11.win_attribs);
} 

_EZK_PRIVATE void ezk_x11_show_window() {
	XMapWindow(_ezk_curwin->x11.display, _ezk_curwin->x11.window);	
}

#endif // EZK_X11

_EZK_PRIVATE int ezk_alloc_window() {
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

  ezk_window_instance** new_inst = &(_ezk.windows[id]);
  *new_inst = (ezk_window_instance*)malloc(sizeof(ezk_window_instance));


  return id;
}

#ifdef EZK_X11

#endif // EZK_WIN

// Implementation
#ifdef EZK_IMPL

#if defined(EZK_X11)
  _EZK_PRIVATE ezk_event ezk_translate_event(XEvent ev) {
    ezk_event translated;
    ezk_zero_var(translated);
    
    switch (ev.type) {
      case KeyPress:
        translated.type = EZK_EVTYPE_KEYPRESS;
KeyEvent:
        printf("X: %d Y: %d\n", ev.xkey.x, ev.xkey.y);
        break;
      case KeyRelease:
        translated.type = EZK_EVTYPE_KEYRELEASE;
        goto KeyEvent;

        break;
      case ButtonPress:
        translated.type = EZK_EVTYPE_BUTTONPRESS;

        break;
      case ButtonRelease:
        translated.type = EZK_EVTYPE_BUTTONRELEASE;

        break;
      case MotionNotify:
        translated.type = EZK_EVTYPE_MOTIONNOTIFY;

        break;
      case EnterNotify:
        translated.type = EZK_EVTYPE_ENTERNOTIFY;

        break;
      case LeaveNotify:
        translated.type = EZK_EVTYPE_LEAVENOTIFY;

        break;
      case FocusIn:
        translated.type = EZK_EVTYPE_FOCUSIN;

        break;
      case FocusOut:
        translated.type = EZK_EVTYPE_FOCUSOUT;

        break;
      case Expose:
        translated.type = EZK_EVTYPE_EXPOSE;

        break;
      case GraphicsExpose:
        translated.type = EZK_EVTYPE_GRAPHICSEXPOSE;

        break;
      case NoExpose:
        translated.type = EZK_EVTYPE_NOEXPOSE;

        break;
      case VisibilityNotify:
        translated.type = EZK_EVTYPE_VISIBILITYNOTIFY;

        break;
      case CreateNotify:
        translated.type = EZK_EVTYPE_CREATENOTIFY;

        break;
      case DestroyNotify:
        translated.type = EZK_EVTYPE_DESTROYNOTIFY;

        break;
      case UnmapNotify:
        translated.type = EZK_EVTYPE_UNMAPNOTIFY;

        break;
      case MapNotify:
        translated.type = EZK_EVTYPE_MAPNOTIFY;

        break;
      case MapRequest:
        translated.type = EZK_EVTYPE_MAPREQUEST;

        break;
      case ReparentNotify:
        translated.type = EZK_EVTYPE_REPARENTNOTIFY;

        break;
      case ConfigureNotify:
        translated.type = EZK_EVTYPE_CONFIGURENOTIFY;

        break;
      case ConfigureRequest:
        translated.type = EZK_EVTYPE_CONFIGUREREQUEST;

        break;
      case GravityNotify:
        translated.type = EZK_EVTYPE_GRAVITYNOTIFY;

        break;
      case ResizeRequest:
        translated.type = EZK_EVTYPE_RESIZEREQUEST;

        break;
      case CirculateNotify:
        translated.type = EZK_EVTYPE_CIRCULATENOTIFY;

        break;
      case CirculateRequest:
        translated.type = EZK_EVTYPE_CIRCULATEREQUEST;

        break;
      case PropertyNotify:
        translated.type = EZK_EVTYPE_PROPERTYNOTIFY;

        break;
      case SelectionClear:
        translated.type = EZK_EVTYPE_SELECTIONCLEAR;

        break;
      case SelectionNotify:
        translated.type = EZK_EVTYPE_SELECTIONNOTIFY;

        break;
      case ClientMessage:
        translated.type = EZK_EVTYPE_CLIENTMESSAGE;

        break;
      case MappingNotify:
        translated.type = EZK_EVTYPE_MAPPINGNOTIFY;

        break;
      case KeymapNotify:
        translated.type = EZK_EVTYPE_KEYMAPNOTIFY;

        break;
    }
    return translated;
  }
#elif defined(EZK_WIN32)

#endif

EZK_API_IMPL int ezk_create_window() { // TODO: add in support for using native graphics and EGL
  int id = ezk_alloc_window();
  _ezk_curwin = _ezk.windows[id]; // make window current
  
  ezk_zero_ptr(_ezk_curwin);
#if defined(EZK_X11)
  _ezk_curwin->x11.display = XOpenDisplay(NULL); // TODO: Add in support for various displays
	if(!_ezk_curwin->x11.display) {
		printf("Failed to open X11 display.\n");
	}

  _ezk_curwin->platform = EZK_WINTYPE_X11;
	_ezk_curwin->x11.screen = DefaultScreenOfDisplay(_ezk_curwin->x11.display); 
                                                                    // TODO: add in support for multiple screens
                                                                    // X11 tends to assign multiple monitors to 
									                                                  // one screen so this might not be necessary 
	_ezk_curwin->x11.screen_id = DefaultScreen(_ezk_curwin->x11.display);
  _ezk_curwin->x11.root = RootWindow(_ezk_curwin->x11.display, _ezk_curwin->x11.screen_id);

  #ifdef EZK_GLX
	ezk_glx_init();

	ezk_glx_choose_visual(&_ezk_curwin->x11.fbc, &_ezk_curwin->x11.visual);	
#endif
  
  // Setup window attributes
  memset(&(_ezk_curwin->x11.win_attribs), 0, sizeof(XSetWindowAttributes));
	_ezk_curwin->x11.win_attribs.border_pixel = BlackPixel(_ezk_curwin->x11.display, _ezk_curwin->x11.screen_id);
  _ezk_curwin->x11.win_attribs.background_pixel = WhitePixel(_ezk_curwin->x11.display, _ezk_curwin->x11.screen_id);
	_ezk_curwin->x11.win_attribs.override_redirect = True;
	_ezk_curwin->x11.win_attribs.colormap = XCreateColormap(_ezk_curwin->x11.display, _ezk_curwin->x11.root, 
                                                     _ezk_curwin->x11.visual->visual, AllocNone);
	_ezk_curwin->x11.win_attribs.event_mask = 0xffffff; // all the events
  _ezk_curwin->x11.win_attribs.override_redirect = 0;

	ezk_x11_create_window();

#elif defined(EZK_WIN32)
  _ezk_curwin->platform = EZK_WINTYPE_WIN32;
#endif

  return id;
}

// TODO: allow loading of window from string for debugging / saving state (ezk_load_window(char* string, int len))

void ezk_show_window(int id) {
  _ezk_curwin = _ezk.windows[id];
#ifdef EZK_X11
  ezk_x11_show_window();
#endif
}

void ezk_main_loop(int id) {
  _ezk_curwin = _ezk.windows[id]; 

#ifdef EZK_X11 
  XEvent ev; // temporary
  ezk_zero_var(ev);

  ezk_event translated;
  ezk_zero_var(translated);

  while (!_ezk_curwin->quit) {
    if(XPending(_ezk_curwin->x11.display) > 0) {
      XNextEvent(_ezk_curwin->x11.display, &ev);
      translated = ezk_translate_event(ev);
    } else {
      struct timespec sleep_time;
      sleep_time.tv_sec = 0;
      sleep_time.tv_nsec = 1000000; // Sleep for 10 milliseconds
      nanosleep(&sleep_time, NULL); // This is to prevent busy waiting, TODO: change to allow various polling rates
    }
  }
#endif 
}
#endif // EZK_WIN

#endif // EZK_IMPL

#endif // EZK_WINDOW_INCLUDED
