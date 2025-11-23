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
static ezk_window **windows;
static ezk_win_id win_count = 0;

static ezk_win_id *free_ids;
static ezk_win_id free_id_count = 0;

// Functions, static and API

static void realloc_ids(ezk_u16 n) {
  if (!windows) {
    windows = malloc(n * sizeof(ezk_window *));
  } else {
    windows = realloc(windows, n * sizeof(ezk_window *));
  }
}

static void realloc_free_ids(ezk_u16 n) {
  if (!free_ids) {
    free_ids = malloc(n * sizeof(ezk_win_id));
  } else {
    free_ids = realloc(free_ids, n * sizeof(ezk_win_id));
  }
}

static ezk_win_id alloc_window_id(ezk_window *win) {
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


void free_window(ezk_window* win) {
  realloc_free_ids(free_id_count + 1);
  free_ids[free_id_count] = win->id;

  windows[win->id] = 0; // this means we can skip over deleted windows
  // don't reduce win_count as it describes the length of the windows buffer

  free(win);

  free_id_count++;
}

static void close_window(ezk_window *win) {
  ezk_internal_close_window(win->id);
  win->closed = true;
  if(win->exit_cb) {
    win->exit_cb(win->id);
  }
  free_window(win);
}

EZKAPI ezk_win_id ezk_window_create(ezk_win_desc desc) {
  ezk_window *win = malloc(sizeof(ezk_window));
  if (!win) { return -1; }
  memset(win, 0, sizeof(ezk_window)); // Clear the structure

  win->id = alloc_window_id(win); // Get our ID

  win->pos = desc.pos;
  win->dims = desc.dims;
  win->name = desc.name;
  win->closed = false;
  win->create_cb = desc.create_cb;
  win->event_cb = desc.event_cb;
  win->update_cb = desc.update_cb;
  win->exit_cb = desc.exit_cb;

  win->fs_state = 0;
  ezk_bflag8_set(&win->fs_state, EZK_WINDOW_FS, desc.fullscreen);
  ezk_bflag8_set(&win->fs_state, EZK_WINDOW_BORDERLESS, desc.borderless);
  ezk_bflag8_set(&win->fs_state, EZK_WINDOW_EXCLUSIVE, desc.exclusive);
  ezk_bflag8_set(&win->fs_state, EZK_WINDOW_MENU, desc.menu);
  
  ezk_internal_create_window(win->id, desc);

  ezk_internal_update_fs_state(win->id, win->fs_state);

  if (win->create_cb)
    win->create_cb(win->id);
  return win->id;
}

EZKAPI void ezk_window_request_close(ezk_win_id id) {
  ezk_window *win = windows[id];
  win->close_requested = true;
  if (win->event_cb) // manually send a close request event
    win->event_cb(id, (ezk_event){EZK_EVENT_CLOSE_REQUESTED});
}

EZKAPI void ezk_window_cancel_close(ezk_win_id id) {
  windows[id]->close_requested = false; // can be run during close_requested_cb
}

EZKAPI void ezk_window_update(ezk_win_id id) {
  ezk_window *win = windows[id];
  if (win->closed) return; // if window has closed, just dont update it

  ezk_u32 eq_size;
  ezk_event *ev_queue = ezk_internal_update_evqueue(win->id, &eq_size);

  for(ezk_u32 i = 0; i < eq_size; i++) { // loop through each event and process it
    ezk_event ev = ev_queue[i];
    switch (ev.type) {
      case EZK_EVENT_KEYDOWN:
        win->keyboard[ev.key.key] = true;
        break;
      case EZK_EVENT_KEYUP:
        win->keyboard[ev.key.key] = false;
        break;
      case EZK_EVENT_DIMCHANGE:
        win->pos = ev.dimension.pos;
        win->dims = ev.dimension.dims;
        break;
      case EZK_EVENT_MOUSEMOVE:
        win->mouse.pos = ev.mousemove.mouse_pos;
        break;
      case EZK_EVENT_CLOSE_REQUESTED:
	      win->close_requested = true;
      default:
        break;
    }

    if (win->event_cb)
      win->event_cb(id, ev);

  }

  free(ev_queue);
 
  if (win->close_requested) { // if a close had been requested and ezk_window_cancel_close 
			      // has not been called
    close_window(win);
  }
  
  if (win->update_cb) { win->update_cb(id); }
}

EZKAPI void ezk_window_update_all() {
  for (ezk_win_id i = 0; i < win_count; i++) {
    if (!windows[i]) { // if the window was deleted
      continue; // skip it
    }
    ezk_window_update(i);
  }
}

EZKAPI ezk_bool ezk_window_closed(ezk_win_id id) {
  return windows[id] == 0 || windows[id]->closed; // short-circuiting prevents segfault
}

EZKAPI ezk_bflag8 ezk_window_get_fs_state(ezk_win_id id) {
  return windows[id]->fs_state;
} 

EZKAPI ezk_bool ezk_window_get_fs(ezk_win_id id) {
  return ezk_bflag8_get(windows[id]->fs_state, EZK_WINDOW_FS);
}

EZKAPI ezk_bool ezk_window_get_borderless(ezk_win_id id) {
  return ezk_bflag8_get(windows[id]->fs_state, EZK_WINDOW_BORDERLESS);
}

EZKAPI ezk_v2i ezk_window_get_dims(ezk_win_id id) {
  return windows[id]->dims;
}

EZKAPI ezk_v2i ezk_window_get_pos(ezk_win_id id) {
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
  ezk_bflag8_set(&windows[id]->fs_state, EZK_WINDOW_FS, fs);
  ezk_internal_update_fs_state(id, windows[id]->fs_state);
}

EZKAPI void ezk_window_flip_fs(ezk_win_id id) {
  ezk_bflag8_flip(&windows[id]->fs_state, EZK_WINDOW_FS);
  ezk_internal_update_fs_state(id, windows[id]->fs_state);
}

EZKAPI void ezk_window_set_borderless(ezk_win_id id, ezk_bool borderless) {
  ezk_bflag8_set(&windows[id]->fs_state, EZK_WINDOW_BORDERLESS, borderless);
  ezk_internal_update_fs_state(id, windows[id]->fs_state);
}

EZKAPI void ezk_window_set_dims(ezk_win_id id, ezk_v2i dims, ezk_bool inc) {
  if (inc) {
    windows[id]->dims.x += dims.x;
    windows[id]->dims.y += dims.y;
  } else {
    windows[id]->dims = dims;
  }
  ezk_internal_set_dims(id, windows[id]->dims);
}

EZKAPI void ezk_window_set_pos(ezk_win_id id, ezk_v2i pos, ezk_bool inc) {
  if (inc) {
    windows[id]->pos.x += pos.x;
    windows[id]->pos.y += pos.y;
  } else {
    windows[id]->pos = pos;
  }
  ezk_internal_set_pos(id, windows[id]->pos);
}

EZKAPI void ezk_window_set_name(ezk_win_id id, ezk_string name) {
  ezk_window *win = windows[id];
  if (win->name) {
    free(win->name);
  }
  win->name = name;
  ezk_internal_set_name(id, name);
}
