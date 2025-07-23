#include "X11/Xlib.h"

#include "./ezk_window.h"

#include <sys/time.h>

typedef struct {
    ezk_win_id id;  

    Display* display;
    Window parent;

    Window handle;
    XSetWindowAttributes wa;
    ezk_u32 ev_mask;

    Atom NET_WM_STATE;
    Atom NET_WM_STATE_FS;

    Atom WM_PROTOCOLS;
    Atom WM_DELETE_WINDOW;
} ezk_x11_window;

static ezk_x11_window** int_windows;
static ezk_win_id int_windows_count;

static void realloc_windows(ezk_win_id len) {
    if(int_windows) {
        int_windows = realloc(int_windows, len * sizeof(ezk_x11_window*));
    } else {
        int_windows = malloc(len * sizeof(ezk_x11_window*));
    }
    int_windows_count = len;
}

static void init_atoms(ezk_x11_window* win) {
    win->NET_WM_STATE = XInternAtom(win->display, "_NET_WM_STATE", False);
    win->NET_WM_STATE_FS = XInternAtom(win->display, "_NET_WM_STATE_FULLSCREEN", False);

    win->WM_PROTOCOLS = XInternAtom(win->display, "WM_PROTOCOLS", False);
    win->WM_DELETE_WINDOW = XInternAtom(win->display, "WM_DELETE_WINDOW", False);
}

static void show_window(ezk_x11_window* win) {
    XMapWindow(win->display, win->handle);
    XRaiseWindow(win->display, win->handle);
    XFlush(win->display);

    // Wait for the window to be visible (realized)
    XEvent ev;
    do {
        XNextEvent(win->display, &ev);
    } while (ev.type != MapNotify || ev.xmap.window != win->handle);
}

static ezk_event translate_event(ezk_x11_window* win, XEvent ev) {
    ezk_event translated;

    Atom message_type; // for client events

    switch (ev.type) {
        case KeyPress:
            translated.type = EZK_EVENT_KEYDOWN;
            translated.key.key = ezk_key_x11_to_ezk(ev.xkey.keycode);
            break;
        case KeyRelease:
            translated.type = EZK_EVENT_KEYUP;
            translated.key.key = ezk_key_x11_to_ezk(ev.xkey.keycode); 
            break;
        case ButtonPress:
            translated.type = EZK_EVENT_BUTTONDOWN;
            translated.button.button = ev.xbutton.button;
            break;
        case ButtonRelease:
            translated.type = EZK_EVENT_BUTTONUP;
            translated.button.button = ev.xbutton.button; 
            break;
        case MotionNotify:
            translated.type = EZK_EVENT_MOUSEMOVE;
            translated.mousemove.mouse_pos = (ezk_v2_i){ev.xmotion.x, ev.xmotion.y}; 
            break;
        case EnterNotify:
            translated.type = EZK_EVENT_MOUSEENTER;
            translated.crossing.mouse_pos = (ezk_v2_i){ev.xcrossing.x, ev.xcrossing.y};
            break;
        case LeaveNotify:
            translated.type = EZK_EVENT_MOUSEEXIT;
            translated.crossing.mouse_pos = (ezk_v2_i){ev.xcrossing.x, ev.xcrossing.y};
            break;
        case ConfigureNotify: // can't be resized as that has already been checked for
            translated.type = EZK_EVENT_DIMCHANGE;
            translated.dimension.pos = (ezk_v2_i){ev.xconfigure.x, ev.xconfigure.y};
            translated.dimension.dims = (ezk_v2_i){ev.xconfigure.width, ev.xconfigure.height};
            break;
        case FocusIn:
            translated.type = EZK_EVENT_FOCUSIN;
            break;
        case FocusOut:
            translated.type = EZK_EVENT_FOCUSOUT;
            break;
        case ClientMessage:
            message_type = ev.xclient.message_type;
            if (message_type == win->WM_PROTOCOLS){
                if(ev.xclient.data.l[0] == (ezk_i64)win->WM_DELETE_WINDOW) {
                    translated.type = EZK_EVENT_EXIT;
                } 
            }
            break;
        case DestroyNotify:
            translated.type = EZK_EVENT_EXIT;
            break;
        default:
            // this includes MappingNotify and Selection Events. Might be worth looking into.
            translated.type = EZK_EVENT_UNKNOWN;
    }
    return translated;
}

ezk_time get_time() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (ezk_time) {tv.tv_sec, tv.tv_usec}; 
}

void ezk_internal_set_fullscreen(ezk_win_id id, ezk_bool fs) {
    ezk_x11_window* win = int_windows[id];
    XEvent e;

    memset(&e, 0, sizeof(XEvent));

    e.type = ClientMessage;
    e.xclient.window = win->handle;
    e.xclient.format = 32;
    e.xclient.message_type = win->NET_WM_STATE;
    e.xclient.data.l[0] = (ezk_u64)fs;
    e.xclient.data.l[1] = win->NET_WM_STATE_FS;
    e.xclient.data.l[2] = 0;
    e.xclient.data.l[3] = 1;
    e.xclient.data.l[4] = 0;

    XSendEvent(win->display, win->parent,
            false,
            SubstructureNotifyMask | SubstructureRedirectMask,
            &e);
       
    XFlush(win->display);
}

void ezk_internal_set_dims(ezk_win_id id, ezk_v2_i dims) {
    ezk_x11_window* win = int_windows[id];
    XResizeWindow(win->display, win->handle, dims.x, dims.y);
}

void ezk_internal_set_pos(ezk_win_id id, ezk_v2_i pos) {
    ezk_x11_window* win = int_windows[id];
    XMoveWindow(win->display, win->handle, pos.x, pos.y - 37); // ???
}

void ezk_internal_set_name(ezk_win_id id, ezk_string name) {
    ezk_x11_window* win = int_windows[id];
    XStoreName(win->display, win->handle, name);
}

void ezk_internal_create_window(ezk_window* window, ezk_win_desc desc) {
    if(window->id >= int_windows_count) { // this is using the same ids as are used in ezk_window.
        realloc_windows(window->id + 1);
    }

    int_windows[window->id] = malloc(sizeof(ezk_x11_window));

    ezk_x11_window* win = int_windows[window->id];

    win->id = window->id;
    win->display = XOpenDisplay(NULL);

    if(win->display == 0) {
	fprintf(stderr, "Failed to open X11 display.\n");
	exit(1);   
    }

    win->parent = DefaultRootWindow(win->display);

    init_atoms(win);

    win->ev_mask = CWBorderPixel | CWColormap | CWEventMask;

    win->wa.colormap = CopyFromParent;
    win->wa.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask |
                    PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                    ExposureMask | FocusChangeMask | VisibilityChangeMask |
                    EnterWindowMask | LeaveWindowMask | PropertyChangeMask;
    win->wa.background_pixmap = CopyFromParent;

    win->handle = XCreateWindow(win->display, win->parent, 
                                desc.pos.x, desc.pos.y, 
                                desc.dims.x , desc.dims.y, 
                                0,
                                CopyFromParent, 
                                CopyFromParent, CopyFromParent, 
                                win->ev_mask, &(win->wa));
    
    ezk_internal_set_name(win->id, desc.name);

    Atom protocols[] = {
        win->WM_DELETE_WINDOW
    };

    XSetWMProtocols(win->display, win->handle, protocols, 1);

    show_window(win);

    if(desc.fullscreen) {
        ezk_internal_set_fullscreen(win->id, true);
    }
}

void ezk_internal_delete_window(ezk_win_id id) {
    ezk_x11_window* win = int_windows[id];
    XUnmapWindow(win->display, win->handle);
    XDestroyWindow(win->display, win->handle);

    XFlush(win->display);
}

ezk_u32 ezk_internal_get_event_count(ezk_win_id id) {
    ezk_x11_window* win = int_windows[id];    
    return XEventsQueued(win->display, QueuedAfterFlush);    
}

ezk_event ezk_internal_get_next_event(ezk_win_id id) {
    ezk_x11_window* win = int_windows[id];
    XEvent event;
    XNextEvent(win->display, &event);

    ezk_event ezk_ev = translate_event(win, event);
    ezk_ev.any.win_id = id;
    ezk_ev.any.time = get_time();
    return ezk_ev;
}
