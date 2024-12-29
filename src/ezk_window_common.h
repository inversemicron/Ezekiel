#ifndef EZK_WIN_COMMON_INCL
#define EZK_WIN_COMMON_INCL

#include <stdint.h>

#include "ezk_keycodes.h"
#include "ezk_primitives.h"

typedef ezk_u16 ezk_win_id;

typedef enum {
  EZK_WIN_BGTYPE_NONE,
  EZK_WIN_BGTYPE_COLOR,
  EZK_WIN_BGTYPE_COPYFROMPARENT,
  EZK_WIN_BGTYPE_IMAGE
} ezk_win_bg_type; 

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
  EZK_EVENT_CLIENTMESSAGE, // linux thing, might change
  EZK_EVENT_EXIT,
  EZK_EVENT_UNKNOWN
} ezk_event_type;

typedef enum {
  EZK_BUTTON_1 =  1,
  EZK_BUTTON_2 =  2,
  EZK_BUTTON_3 =  4,
  EZK_BUTTON_4 =  8,
  EZK_BUTTON_5 = 16
} ezk_button;


typedef struct {
  ezk_v2_i dims;
  ezk_v2_i pos;
  ezk_bool fullscreen;
  char* name;

  ezk_win_bg_type bg_type;
  uint32_t bg_color;
  char* bg_image;

  ezk_win_bg_type border_type;
  uint32_t border_color;
  char* border_image;
  ezk_u16 border_width;

  EZK_CALLBACK(exit_cb, void);
} ezk_win_desc;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
} ezk_event_any; // note changing this struct requires changing all other event structures

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_key key; // without modifiers
  ezk_key key_mod; // with modifiers
  ezk_mod_key mods;
} ezk_event_key;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_button button;
  ezk_v2_i mouse;
} ezk_event_button;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_v2_i mouse_pos;
} ezk_event_crossing; // mouse entering/leaving window

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_v2_i mouse_pos;
} ezk_event_mousemove;

typedef struct {
  ezk_event_type type;
  ezk_win_id win_id;
  ezk_time time;
  ezk_v2_i pos; // window position
  ezk_v2_i dims; // window size
} ezk_event_dimension;

typedef ezk_event_any ezk_event_focus;

typedef union {
  ezk_event_type type;
  ezk_event_any any;
  ezk_event_key key;
  ezk_event_button button;
  ezk_event_crossing crossing;
  ezk_event_mousemove mousemove;
  ezk_event_dimension dimension;
  ezk_event_focus focus;
} ezk_event;

typedef struct {
  ezk_v2_i pos;
  ezk_button buttons;
} ezk_mouse;

typedef struct {
  ezk_win_id id;
  ezk_v2_i dims;
  ezk_v2_i pos;
  char* name;
  ezk_u8 fs_state;

  ezk_event* ev_queue;
  ezk_u32 ev_count;
  
  ezk_mouse mouse;
  ezk_bool keyboard[EZK_KEY_COUNT]; // shows if each key is down
  } ezk_window;

#endif
