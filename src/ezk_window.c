#include "ezk_api.h"
#include "ezk_platform.h"
#include "ezk_window/ezk_window.h"

// Platform-specific headers

#if defined(EZK_WINDOWS)
  #include "./ezk_window/win32.h"
#elif defined(EZK_APPLE)
  #include "./ezk_window/cocoa.h"
#elif defined(EZK_LINUX)
  #include "./ezk_window/x11.h"
#endif

// Statics
static ezk_window** windows;
static ezk_win_id win_count = 0;

static ezk_win_id* free_ids;
static ezk_win_id free_id_count = 0;

// Functions, static and API

static void realloc_ids(ezk_u16 n) {
  if(!windows) {
    windows = malloc(n * sizeof(ezk_window*));
  } else {
    windows = realloc(windows, n * sizeof(ezk_window*));
  }
}

static void realloc_free_ids(ezk_u16 n) {
  if(!windows) {
    free_ids = malloc(n * sizeof(ezk_win_id));
  } else {
    free_ids = realloc(free_ids, n * sizeof(ezk_win_id));
  }
}

static ezk_win_id alloc_window_id(ezk_window* win) {
  ezk_win_id id = 0;
  if (free_id_count) {
    id = free_ids[--free_id_count]; // Last free id
    realloc_free_ids(free_id_count); // Truncate the list, removing the id we just used
  } else {
    realloc_ids(win_count + 1);
    id = win_count++;
  }
  windows[id] = win;
  return id;
}

static void quit_window(ezk_window* win) {
  ezk_internal_delete_window(win->id);
  if(win->ev_queue) {
    free(win->ev_queue);
  }
  win->quitted = true;
  if (win->quit_cb)
    win->quit_cb(win->id);
}

EZKAPI ezk_win_id ezk_window_create(ezk_win_desc desc) {
  ezk_window* win = malloc(sizeof(ezk_window));
  if (!win) {return -1;}
  memset(win, 0, sizeof(ezk_window)); // Clear the structure

  win->id = alloc_window_id(win); // Get our ID

  win->pos = desc.pos;
  win->dims = desc.dims;
  win->name = desc.name;
  win->quitted = false;
  win->create_cb = desc.create_cb;
  win->event_cb = desc.event_cb;
  win->update_cb = desc.update_cb;
  win->quit_cb = desc.quit_cb;

  ezk_internal_create_window(win, desc);
  
  if(win->create_cb)
    win->create_cb(win->id);
  return win->id;
}

EZKAPI void ezk_window_free(ezk_win_id id) {
  ezk_window* win = windows[id];

  realloc_free_ids(free_id_count + 1);
  free_ids[free_id_count] = win->id;

  windows[win->id] = 0; // this means we can skip over deleted windows
  // don't reduce win count as it describes the length of the windows buffer

  free(win);

  free_id_count++;
}

EZKAPI void ezk_window_quit(ezk_win_id id) {
  windows[id]->quitted = true; // quits next update
}

// The next two functions can be used to manually press keys
EZKAPI void ezk_window_key_down(ezk_window* win, ezk_key key) {
  win->keyboard[key] = true;
}

EZKAPI void ezk_window_key_up(ezk_window* win, ezk_key key) {
  win->keyboard[key] = false;
}

EZKAPI void ezk_window_update(ezk_win_id id) {
  ezk_window* win = windows[id];
  if(win->quitted) return; // if window has quitted, just dont update it
  ezk_event* ev_queue = ezk_internal_update_evqueue(win->id); // returns null terminated list

  ezk_u32 i = 0;
  while(ev_queue[i].any.type != EZK_EVENT_NONE) { // loop through each event and process it
    ezk_event ev = ev_queue[i];
    switch (ev.type) {
      case EZK_EVENT_KEYDOWN:
        ezk_window_key_down(win,ev.key.key);
        break;
      case EZK_EVENT_KEYUP:
        ezk_window_key_up(win,ev.key.key);
        break;
      case EZK_EVENT_DIMCHANGE:
        win->pos = ev.dimension.pos;
        win->dims = ev.dimension.dims;
        break;
      case EZK_EVENT_MOUSEMOVE:
        win->mouse.pos = ev.mousemove.mouse_pos;
        break;
      case EZK_EVENT_EXIT:
        ezk_window_quit(id);
        break;
      default:
        break;
    }
    if(win->event_cb) 
      win->event_cb(id, ev);
    if(win->quitted) break; // stops processing events after quit

	i++;
  }
  free(ev_queue); // free the event queue allocated by ezk_internal_update_evqueue

  if(!win->quitted) {
	if(win->update_cb)
    	win->update_cb(id);
  } else {
    quit_window(win);
  }
}

EZKAPI void ezk_window_update_all() {
  for(ezk_win_id i = 0; i < win_count; i++) {
    if(!windows[i]) { // if the window was deleted
  	  printf("%i\n",i);
      break; // skip it
    }
    ezk_window_update(i);
  }
}

EZKAPI ezk_bool ezk_window_quitted(ezk_win_id id) {
  return windows[id]->quitted;
}

EZKAPI ezk_bool ezk_window_get_fs(ezk_win_id id) {
  return windows[id]->fs;
}

EZKAPI ezk_v2_i ezk_window_get_dims(ezk_win_id id) {
  return windows[id]->dims;
}

EZKAPI ezk_v2_i ezk_window_get_pos(ezk_win_id id) {
  return windows[id]->pos;
}

EZKAPI ezk_string ezk_window_get_name(ezk_win_id id) {
  return windows[id]->name;
}

EZKAPI ezk_mouse ezk_window_get_mouse(ezk_win_id id) {
  return windows[id]->mouse;
}

EZKAPI ezk_bool ezk_window_is_key_down(ezk_win_id id, ezk_key key) {
  return windows[id]->keyboard[key];
}

EZKAPI void ezk_window_set_fs(ezk_win_id id, ezk_bool fs) {
  windows[id]->fs = fs;
  ezk_internal_set_fullscreen(id, fs);
}

EZKAPI void ezk_window_flip_fs(ezk_win_id id) {
  windows[id]->fs ^= 1; // flip
  ezk_internal_set_fullscreen(id, windows[id]->fs);
}

EZKAPI void ezk_window_set_dims(ezk_win_id id, ezk_v2_i dims, ezk_bool inc) {
  if(inc) {
    windows[id]->dims.x += dims.x;
    windows[id]->dims.y += dims.y; 
  } else {
    windows[id]->dims = dims;
  }  
  ezk_internal_set_dims(id,windows[id]->dims);
}

EZKAPI void ezk_window_set_pos(ezk_win_id id, ezk_v2_i pos, ezk_bool inc) {
  if(inc) {
    windows[id]->pos.x += pos.x;
    windows[id]->pos.y += pos.y;
  } else {
    windows[id]->pos = pos;
  }
  ezk_internal_set_pos(id,windows[id]->pos);
}

EZKAPI void ezk_window_set_name(ezk_win_id id, ezk_string name) {
  windows[id]->name = name; // memory unsafe? prev. name is not freed
  ezk_internal_set_name(id, name);
}