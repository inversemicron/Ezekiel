#include "../ezk_window.h"
#include <xcb/xcb.h>

typedef struct {
  ezk_win_id id;

  xcb_connection_t *display;
  xcb_screen_t *screen;
  xcb_window_t parent;

  xcb_window_t handle;
  
  ezk_u32 ev_mask;

  ezk_v2i current_dims; // used for GC right now, may not be needed later

  ezk_bool borderless; // get this from updating state flags cause it doesn't have an atom.

  xcb_atom_t NET_WM_STATE;
  xcb_atom_t NET_WM_STATE_FS;
  xcb_atom_t NET_WM_STATE_MAX_H;
  xcb_atom_t NET_WM_STATE_MAX_V;
  xcb_atom_t NET_WM_STATE_HIDDEN;
  xcb_atom_t NET_WM_STATE_ABOVE;

  xcb_atom_t WM_PROTOCOLS;
  xcb_atom_t WM_DELETE_WINDOW;

  xcb_atom_t NET_WM_NAME;
  xcb_atom_t UTF8_STRING;

  xcb_gcontext_t gc;
} ezk_x11_window;

static ezk_x11_window **int_windows;
static ezk_win_id int_windows_count;

static void realloc_windows(ezk_win_id len) {
  if (int_windows) {
    int_windows = realloc(int_windows, len * sizeof(ezk_x11_window *));
  } else {
    int_windows = malloc(len * sizeof(ezk_x11_window *));
  }
  int_windows_count = len;
}

static ezk_time get_time() { // temporary
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (ezk_time) {tv.tv_sec, tv.tv_usec};
}

// add error checking to this!!
static xcb_atom_t get_atom(ezk_x11_window *win, ezk_string name) {
  xcb_intern_atom_cookie_t c = xcb_intern_atom(win->display, 0, strlen(name), name);
  xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(win->display, c, NULL);
  xcb_atom_t atom = r->atom;
  free(r);
  return atom;
}

static void init_atoms(ezk_x11_window *win) {
  win->NET_WM_STATE = get_atom(win,"_NET_WM_STATE");
  win->NET_WM_STATE_FS = get_atom(win,"_NET_WM_STATE_FULLSCREEN");
  win->NET_WM_STATE_MAX_H = get_atom(win,"_NET_WM_STATE_MAXIMIZED_HORZ");
  win->NET_WM_STATE_MAX_V = get_atom(win,"_NET_WM_STATE_MAXIMIZED_VERT");
  win->NET_WM_STATE_HIDDEN = get_atom(win,"_NET_WM_STATE_HIDDEN");
  win->NET_WM_STATE_ABOVE = get_atom(win,"_NET_WM_STATE_ABOVE"); 
  
  win->WM_PROTOCOLS = get_atom(win,"WM_PROTOCOLS");
  win->WM_DELETE_WINDOW = get_atom(win,"WM_DELETE_WINDOW");

  win->NET_WM_NAME = get_atom(win,"_NET_WM_NAME");

  win->UTF8_STRING = get_atom(win,"UTF8_STRING");
}

static inline ezk_u8 get_xcb_evtype(xcb_generic_event_t *ev) { return ev->response_type & ~0x80; }

static void show_window(ezk_x11_window *win) {
  xcb_map_window(win->display, win->handle);
  xcb_flush(win->display);
}

static ezk_bflag8 get_state_flags(ezk_x11_window *win) {
  ezk_u8 format;
  xcb_atom_t type_atom;
  ezk_u32 n;
  void *data = NULL;
  xcb_atom_t *atoms = NULL;
  ezk_bflag8 flags = 0;
 
  xcb_get_property_cookie_t cookie = xcb_get_property(win->display, 0, 
      win->handle, win->NET_WM_STATE, XCB_GET_PROPERTY_TYPE_ANY, 0, 1024);

  // !! error checking !!
  xcb_get_property_reply_t* reply = xcb_get_property_reply(win->display, cookie, NULL);
  if (!reply) {
    return false;
  }

  type_atom = reply->type;
  format = reply->format;
  n = xcb_get_property_value_length(reply) / 4; // div 4 cause 32-bits per value
  data = xcb_get_property_value(reply);

  if(type_atom == XCB_ATOM_ATOM && format == 32) {
    atoms = (xcb_atom_t*)data;
    for (ezk_u64 i = 0; i < n; i++) {
      xcb_atom_t atom = atoms[i];
      if (atom == win->NET_WM_STATE_FS) {
        ezk_bflag8_set(&flags,EZK_WINDOW_FS, true);
      } else if (!win->borderless &&
          (atom == win->NET_WM_STATE_MAX_V || atom == win->NET_WM_STATE_MAX_H)) {
        // gonna assume just one of these means we are maximised
        ezk_bflag8_set(&flags,EZK_WINDOW_FS,true);
      } else if (atom == win->NET_WM_STATE_HIDDEN) {
        ezk_bflag8_set(&flags,EZK_WINDOW_MINIMISE,true);
      } else if (atom == win->NET_WM_STATE_ABOVE) {
        ezk_bflag8_set(&flags,EZK_WINDOW_ONTOP,true);
      }
    }
  }

  // manually set borderless, as it doesn't directy correspond to a flag
  ezk_bflag8_set(&flags, EZK_WINDOW_BORDERLESS, win->borderless);

  free(reply);
  
  return flags;
}

static ezk_event translate_event(ezk_x11_window *win, xcb_generic_event_t *ge) {
  ezk_event translated;

  switch (get_xcb_evtype(ge)) {
    case XCB_KEY_PRESS:
      translated.type = EZK_EVENT_KEYDOWN;
      xcb_key_press_event_t *kpe = (xcb_key_press_event_t*)ge;
      translated.key.key = ezk_key_x11_to_ezk(kpe->detail);
      break;
    case XCB_KEY_RELEASE:
      translated.type = EZK_EVENT_KEYUP;
      xcb_key_release_event_t *kre = (xcb_key_release_event_t*)ge;
      translated.key.key = ezk_key_x11_to_ezk(kre->detail);
      break;
    case XCB_BUTTON_PRESS:
      translated.type = EZK_EVENT_BUTTONDOWN;
      xcb_button_press_event_t *bpe = (xcb_button_press_event_t*)ge;
      translated.button.button = bpe->detail;
      break;
    case XCB_BUTTON_RELEASE:
      translated.type = EZK_EVENT_BUTTONUP;
      xcb_button_release_event_t *bre = (xcb_button_release_event_t*)ge;
      translated.button.button = bre->detail;
      break;
    case XCB_MOTION_NOTIFY:
      translated.type = EZK_EVENT_MOUSEMOVE;
      xcb_motion_notify_event_t *mne = (xcb_motion_notify_event_t*)ge;
      translated.mousemove.mouse_pos = (ezk_v2i) {mne->event_x,mne->event_y};
      break;
    case XCB_ENTER_NOTIFY:
      translated.type = EZK_EVENT_MOUSEENTER;
      xcb_enter_notify_event_t *ene = (xcb_enter_notify_event_t*)ge;
      translated.crossing.mouse_pos = (ezk_v2i) {ene->event_x,ene->event_y};
      break;
    case XCB_LEAVE_NOTIFY:
      translated.type = EZK_EVENT_MOUSEEXIT;
      xcb_leave_notify_event_t *lne = (xcb_leave_notify_event_t*)ge;
      translated.crossing.mouse_pos = (ezk_v2i) {lne->event_x,lne->event_y};
      break;
    case XCB_CONFIGURE_NOTIFY: 
      translated.type = EZK_EVENT_DIMCHANGE;
      xcb_configure_notify_event_t *cne = (xcb_configure_notify_event_t*)ge;
      translated.dimension.pos = (ezk_v2i) {cne->x,cne->y};
      translated.dimension.dims = (ezk_v2i) {cne->width,cne->height};
      
      win->current_dims = translated.dimension.dims;
      break;
    case XCB_FOCUS_IN:
      translated.type = EZK_EVENT_FOCUSIN;
      break;
    case XCB_FOCUS_OUT:
      translated.type = EZK_EVENT_FOCUSOUT;
      break;
    case XCB_EXPOSE:
      translated.type = EZK_EVENT_UNKNOWN;
      xcb_rectangle_t rect = {0,0,win->current_dims.x,win->current_dims.y};
      
      xcb_poly_fill_rectangle(win->display,win->handle,win->gc,1,&rect);
      break;
    case XCB_PROPERTY_NOTIFY:
      xcb_property_notify_event_t *pne = (xcb_property_notify_event_t*)ge;
      if (pne->atom == win->NET_WM_STATE) {
        translated.type = EZK_EVENT_FLAGCHANGE;
        translated.flagchange.flags = get_state_flags(win);
        break;
      }
      translated.type = EZK_EVENT_UNKNOWN;
      break;
    case XCB_CLIENT_MESSAGE:
      xcb_client_message_event_t *cme = (xcb_client_message_event_t *)ge;
      if (cme->type == win->WM_PROTOCOLS) {
        if (cme->data.data32[0] == (ezk_i64) win->WM_DELETE_WINDOW) {
          translated.type = EZK_EVENT_CLOSEREQUESTED;
          break;
        }
      } 
      translated.type = EZK_EVENT_UNKNOWN;
      break;
    default:
      // this includes MappingNotify and Selection Events. Might be worth looking into.
      translated.type = EZK_EVENT_UNKNOWN;
  }
  return translated;
}

static void send_state_message(ezk_x11_window *win, xcb_atom_t atom1, xcb_atom_t atom2, ezk_u64 val) {
  xcb_client_message_event_t cme;
  memset(&cme, 0, sizeof(xcb_client_message_event_t));

  if(atom1 == win->NET_WM_STATE_FS) {
  }

  cme.response_type = XCB_CLIENT_MESSAGE;
  cme.window = win->handle;
  cme.format = 32;
  cme.type = win->NET_WM_STATE;
  
  cme.data.data32[0] = val ? 1 : 0;
  cme.data.data32[1] = atom1;
  cme.data.data32[2] = atom2;
  cme.data.data32[3] = 1;
  cme.data.data32[4] = 0;
  
  xcb_send_event(win->display,0,win->parent, // root window, not our window
      XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT,
      (const char*)&cme);
}

void ezk_internal_update_state_flags(ezk_win_id id, ezk_bflag8 state_flags) {
  ezk_x11_window *win = int_windows[id];
  
  ezk_bool borderless = ezk_bflag8_get(state_flags, EZK_WINDOW_BORDERLESS);

  win->borderless = borderless; // update borderless value

  // disable borderless if it isnt active
  send_state_message(win, win->NET_WM_STATE_FS, 0, 
      borderless && ezk_bflag8_get(state_flags, EZK_WINDOW_FS));
  
  // disable bordered if borderless is active
  send_state_message(win, win->NET_WM_STATE_MAX_H, win->NET_WM_STATE_MAX_V, 
      borderless && !ezk_bflag8_get(state_flags, EZK_WINDOW_FS));
 
  // set if window is minimized
  send_state_message(win, win->NET_WM_STATE_HIDDEN, 0,
      ezk_bflag8_get(state_flags, EZK_WINDOW_MINIMISE));

  // set if window is always on top
  send_state_message(win, win->NET_WM_STATE_ABOVE, 0,
      ezk_bflag8_get(state_flags, EZK_WINDOW_ONTOP));

  xcb_flush(win->display);
}

void ezk_internal_set_dims(ezk_win_id id, ezk_v2i dims) {
  ezk_x11_window *win = int_windows[id];
  ezk_u32 values[] = {dims.x, dims.y};

  xcb_configure_window(win->display,win->handle,
      XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,values);
}

void ezk_internal_set_pos(ezk_win_id id, ezk_v2i pos) {
  ezk_x11_window *win = int_windows[id];
  ezk_u32 values[] = {pos.x, pos.y};

  xcb_configure_window(win->display,win->handle, 
      XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,values);
}

void ezk_internal_set_name(ezk_win_id id, ezk_string name) {
  ezk_x11_window *win = int_windows[id];

  xcb_change_property(win->display,XCB_PROP_MODE_REPLACE,win->handle,
    XCB_ATOM_WM_NAME,XCB_ATOM_STRING,8,strlen(name),name);

  xcb_change_property(win->display,XCB_PROP_MODE_REPLACE,win->handle,
    win->NET_WM_NAME,win->UTF8_STRING,8,strlen(name),name);
}

void ezk_internal_create_window(ezk_win_id id, ezk_win_desc desc) {
  if (id >= int_windows_count) {
    // each window here corresponds to a window in ezk_window.c,
    // so the buffer just allocates enough for the highest id.
    // if the same id is repeated, the window is overwritten.
    realloc_windows(id + 1);
  }

  int_windows[id] = malloc(sizeof(ezk_x11_window));

  ezk_x11_window *win = int_windows[id];

  win->id = id;

  int screen_num;
  win->display = xcb_connect(NULL, &screen_num); 

  if (xcb_connection_has_error(win->display)) {
    fprintf(stderr, "Failed to open X display.\n");
    exit(1);
  }

  const xcb_setup_t *setup = xcb_get_setup(win->display);
  xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);

  for (int i = 0; i < screen_num; i++)
    xcb_screen_next(&it);

  win->screen = it.data;
  win->parent = win->screen->root;

  init_atoms(win);

  win->ev_mask = XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_KEY_PRESS |
    XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
    XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW |
    XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY |
    XCB_EVENT_MASK_PROPERTY_CHANGE;
  
  ezk_u32 win_attr[] = {
    win->screen->black_pixel,
    win->ev_mask
  }; 

  ezk_u32 mask = XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK;

  win->handle = xcb_generate_id(win->display);
  xcb_create_window(win->display,XCB_COPY_FROM_PARENT,
      win->handle,
      win->parent,desc.pos.x, desc.pos.y,
      desc.dims.x, desc.dims.y,0,
      XCB_WINDOW_CLASS_INPUT_OUTPUT,
      XCB_COPY_FROM_PARENT,mask,win_attr);

  ezk_internal_set_name(win->id, desc.name);
  
  win->gc = xcb_generate_id(win->display);
  xcb_create_gc(win->display,win->handle,win->gc,0,NULL);

  xcb_change_property(win->display,XCB_PROP_MODE_REPLACE,win->handle,win->WM_PROTOCOLS,
      XCB_ATOM_ATOM,32,1,&win->WM_DELETE_WINDOW);

  show_window(win);
  printf("Window showing!\n");
}

void ezk_internal_close_window(ezk_win_id id) {
  ezk_x11_window *win = int_windows[id];
  xcb_unmap_window(win->display, win->handle);
  xcb_destroy_window(win->display, win->handle);

  xcb_flush(win->display);
}

static ezk_event get_next_event(ezk_x11_window *win) {
  xcb_generic_event_t *event = xcb_poll_for_event(win->display);

  if(event == NULL) return (ezk_event){EZK_EVENT_NULL};

  ezk_event translated = translate_event(win, event);
  translated.any.win_id = win->id;
  translated.any.time = get_time();

  free(event);

  return translated;
}

ezk_event *ezk_internal_update_evqueue(ezk_win_id id, ezk_u32 *eq_size) {
  ezk_x11_window *win = int_windows[id];

  ezk_u32 capacity = 8;
  ezk_event ev;

  *eq_size = 0;
  ezk_event *ev_queue = malloc(capacity * sizeof(ezk_event));
  while ((ev = get_next_event(win)).type != EZK_EVENT_NULL) { 
    if (++*eq_size >= capacity) { // ah yes, ++*, my favorite operator
      capacity = capacity * 2;
      ev_queue = realloc(ev_queue, capacity * sizeof(ezk_event));
    }
    ev_queue[*eq_size-1] = ev;
  }

  return ev_queue;
}
