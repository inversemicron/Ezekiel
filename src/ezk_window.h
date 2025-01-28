#ifndef EZK_WIN_INCL
#define EZK_WIN_INCL

#include "./ezk_platform.h"
#include "./ezk_window_common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Platform-specific headers

#if defined(EZK_WINDOWS)
  #include "./ezk_window/win32.h"
#elif defined(EZK_APPLE)
  #include "./ezk_window/cocoa.h"
#elif defined(EZK_LINUX)
  #include "./ezk_window/x11.h"
#endif

#include "./ezk_window_common.h"

// Externs (from platform-specific headers)
// This section isn't necessary as header already exist but serves to document
// platform-specific functions. 
extern void ezk_internal_create_window(ezk_window* win, ezk_win_desc desc);
extern ezk_u32 ezk_internal_get_event_count(ezk_win_id id);
extern ezk_event ezk_internal_get_next_event(ezk_win_id id);

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

static void realloc_evqueue(ezk_window* win) {
  if(win->ev_queue) {
    win->ev_queue = realloc(win->ev_queue, win->ev_count * sizeof(ezk_event));
  } else {
    win->ev_queue = malloc(win->ev_count * sizeof(ezk_event));
  }
}

static void update_evqueue(ezk_window* win) {
  ezk_u32 start_index = win->ev_count; // where we put new events 
  ezk_u32 event_count = ezk_internal_get_event_count(win->id);

  win->ev_count += event_count;
  realloc_evqueue(win);
  for(ezk_u32 i = 0; i < event_count; i++) {
    win->ev_queue[start_index + i] = ezk_internal_get_next_event(win->id);
    if(win->ev_queue[start_index + 1].type == EZK_EVENT_EXIT) {
      free(win->ev_queue);
    }
  }
} 

void quit_window(ezk_window* win) {
  ezk_internal_delete_window(win->id);
  if(win->ev_queue) {
    free(win->ev_queue);
  }
  win->quitted = true;
  win->quit_cb(win->id);
}

EZKAPI ezk_win_id ezk_create_window(ezk_win_desc desc) {
  ezk_window* win = malloc(sizeof(ezk_window));
  if (!win) {return -1;}
  //memset(win, 0, sizeof(ezk_window)); // Clear the structure
  win->id = alloc_window_id(win); // Get our ID

  win->pos = desc.pos;
  win->dims = desc.dims;
  win->name = desc.name;
  win->create_cb = desc.create_cb;
  win->event_cb = desc.event_cb;
  win->quit_cb = desc.quit_cb;

  ezk_internal_create_window(win, desc);

  win->create_cb(win->id);

  return win->id;
}

EZKAPI void ezk_free_window(ezk_win_id id) {
  ezk_window* win = windows[id];

  realloc_free_ids(free_id_count + 1);
  free_ids[free_id_count] = win->id;

  windows[win->id] = 0; // this means we can skip over deleted windows
  // don't reduce win count as it describes the length of the windows buffer

  free(win);

  free_id_count++;
}

EZKAPI void ezk_delete_window(ezk_win_id id) {
  ezk_window* win = windows[id];
  quit_window(win);
  ezk_free_window(id);
}

EZKAPI void ezk_delete_windows() {
  if (free_ids) free(free_ids);
  if(windows) {
    for(ezk_win_id i = 0; i < win_count; i++) {
      if(windows[i]) {
        ezk_delete_window(i);
      }
    }
    free(windows);
  }
}

EZKAPI void ezk_key_down(ezk_window* win, ezk_key key) {
  win->keyboard[key] = true;
}

EZKAPI void ezk_key_up(ezk_window* win, ezk_key key) {
  win->keyboard[key] = false;
}

EZKAPI void ezk_update_window(ezk_win_id id) {
  ezk_window* win = windows[id];
  if(win->quitted) return; // if window has quitted, just dont update it
  update_evqueue(win);
  for(ezk_u32 i = 0;i < win->ev_count;i++) { // loop through each event and process it
    ezk_event ev = win->ev_queue[i];
    switch (ev.type) {
      case EZK_EVENT_KEYDOWN:
        ezk_key_down(win,ev.key.key);
        break;
      case EZK_EVENT_KEYUP:
        ezk_key_up(win,ev.key.key);
        break;
      case EZK_EVENT_EXIT:
        quit_window(win);
        break;
      default:
        break;
    }
    if(win->event_cb) 
      win->event_cb(id, ev);
    if(win->quitted) break; // stops processing events after quit
  }
  if(!win->quitted) { // if it hasnt quitted, clear the event queue, as every event has been processed
    free(win->ev_queue);
    win->ev_queue = 0;
    win->ev_count = 0;
  }
}

EZKAPI void ezk_update_windows() {
  for(int i = 0; i < win_count; i++) {
    if(!windows[i]) { // if the window was deleted
      break; // skip it
    }
    ezk_update_window(i);
  }
}

EZKAPI ezk_bool ezk_window_quitted(ezk_win_id id) {
  return windows[id]->quitted;
}

#endif // EZK_WIN_INCL