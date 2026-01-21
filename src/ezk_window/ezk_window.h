#ifndef EZK_WIN_COMMON_INCL
#define EZK_WIN_COMMON_INCL

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <sys/time.h>

#include "../ezk_keycodes.h"
#include "../ezk_primitives.h"
#include "../ezk_callback.h"
#include "../ezk_bflag.h"
#include "../ezk_api.h"

#include "X11/Xlib.h"
#include "X11/Xatom.h"

typedef ezk_u16 ezk_win_id;

typedef enum {
  EZK_WIN_BGTYPE_NONE,
  EZK_WIN_BGTYPE_COLOR,
  EZK_WIN_BGTYPE_COPYFROMPARENT,
  EZK_WIN_BGTYPE_IMAGE
} ezk_win_bg_type;

typedef enum {
  EZK_BUTTON_1 = 1,
  EZK_BUTTON_2 = 2,
  EZK_BUTTON_3 = 4,
  EZK_BUTTON_4 = 8,
  EZK_BUTTON_5 = 16
} ezk_button;

typedef enum {
  EZK_EVENT_KEYDOWN,
  EZK_EVENT_KEYUP,
  EZK_EVENT_BUTTONDOWN,
  EZK_EVENT_BUTTONUP,
  EZK_EVENT_MOUSEMOVE,
  EZK_EVENT_MOUSEENTER,
  EZK_EVENT_MOUSEEXIT,
  EZK_EVENT_DIMCHANGE,
  EZK_EVENT_FOCUSIN,
  EZK_EVENT_FOCUSOUT,
  EZK_EVENT_FLAGCHANGE,
  EZK_EVENT_CLOSEREQUESTED,
  EZK_EVENT_UNKNOWN
} ezk_event_type;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_u32 index; // in the event queue
} ezk_event_any; // note changing this struct requires changing all other event structures

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_u32 index;
  ezk_key key; // without modifiers
  ezk_key key_mod; // with modifiers
  ezk_mod_key mods;
} ezk_event_key;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_u32 index;
  ezk_button button;
  ezk_v2i mouse;
} ezk_event_button;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_u32 index;
  ezk_v2i mouse_pos;
} ezk_event_crossing; // mouse entering/leaving window

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_u32 index;
  ezk_v2i mouse_pos;
} ezk_event_mousemove;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_u32 index;
  ezk_v2i pos; // window position
  ezk_v2i dims; // window size
} ezk_event_dimension;

typedef ezk_event_any ezk_event_focus;
typedef ezk_event_any ezk_event_minimize;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_u32 index;
  ezk_bflag8 flags;
} ezk_event_flag_change;

typedef union {
  ezk_event_type type;
  ezk_event_any any;
  ezk_event_key key;
  ezk_event_button button;
  ezk_event_crossing crossing;
  ezk_event_mousemove mousemove;
  ezk_event_dimension dimension;
  ezk_event_focus focus;
  ezk_event_flag_change flagchange;
} ezk_event;

typedef struct {
  ezk_v2i pos;
  ezk_button buttons;
} ezk_mouse;

EZK_CALLBACK_TYPEDEF(ezk_window_non_event_cb, void, ezk_win_id);
EZK_CALLBACK_TYPEDEF(ezk_window_event_cb, void, ezk_win_id, ezk_event);

#define EZK_WINDOW_FS 0
#define EZK_WINDOW_BORDERLESS 1 // top bar
#define EZK_WINDOW_EXCLUSIVE 2 // lets the app control screen rendering
#define EZK_WINDOW_MENU 3 // dropdown menus (only on windows for now)
#define EZK_WINDOW_MINIMISE 4 // minimised/restored
#define EZK_WINDOW_ONTOP 5 // always on top

typedef struct {
  ezk_v2i dims;
  ezk_v2i pos;

  ezk_bool fullscreen;
  ezk_bool borderless;
  ezk_bool exclusive;
  ezk_bool menu;
  ezk_bool ontop;

  char *name;

  ezk_win_bg_type bg_type;
  uint32_t bg_color;
  char *bg_image;

  ezk_window_non_event_cb create_cb;
  ezk_window_event_cb event_cb;
  ezk_window_non_event_cb update_cb;
  ezk_window_non_event_cb exit_cb;
} ezk_win_desc;

typedef struct {
  ezk_win_id id;
  ezk_v2i dims;
  ezk_v2i pos;
  ezk_string name;
  ezk_bflag8 state_flags;

  ezk_event *ev_queue;
  ezk_u32 ev_count;

  ezk_mouse mouse;
  ezk_bool keyboard[EZK_KEY_COUNT]; // shows if each key is down

  ezk_bool close_requested;
  ezk_bool closed;

  ezk_window_non_event_cb create_cb;
  ezk_window_event_cb event_cb;
  ezk_window_non_event_cb update_cb;
  ezk_window_non_event_cb exit_cb;
} ezk_window;

EZKAPI ezk_win_id ezk_window_create(ezk_win_desc desc);

EZKAPI void ezk_window_request_close(ezk_win_id id);
EZKAPI void ezk_window_cancel_close(ezk_win_id id);

EZKAPI void ezk_window_update(ezk_win_id id);
EZKAPI void ezk_window_update_all();

EZKAPI ezk_bool ezk_window_get_fs(ezk_win_id id);
EZKAPI ezk_bool ezk_window_get_borderless(ezk_win_id id);
EZKAPI ezk_v2i ezk_window_get_dims(ezk_win_id id);
EZKAPI ezk_v2i ezk_window_get_pos(ezk_win_id id);
EZKAPI ezk_string ezk_window_get_name(ezk_win_id id);
EZKAPI ezk_mouse ezk_window_get_mouse(ezk_win_id id);
EZKAPI ezk_bool ezk_window_is_key_down(ezk_win_id id, ezk_key key);
EZKAPI ezk_bool ezk_window_closed(ezk_win_id id);

EZKAPI void ezk_window_set_fs(ezk_win_id id, ezk_bool fs);
EZKAPI void ezk_window_flip_fs(ezk_win_id id);
EZKAPI void ezk_window_set_borderless(ezk_win_id id, ezk_bool borderless);
EZKAPI void ezk_window_set_minimised(ezk_win_id id, ezk_bool minimised);
EZKAPI void ezk_window_flip_minimised(ezk_win_id id);
EZKAPI void ezk_window_set_dims(ezk_win_id id, ezk_v2i dims, ezk_bool inc);
EZKAPI void ezk_window_set_pos(ezk_win_id id, ezk_v2i pos, ezk_bool inc);
EZKAPI void ezk_window_set_name(ezk_win_id id, ezk_string name);

#endif
