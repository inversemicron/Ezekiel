#ifndef EZK_WIN_INCL
#define EZK_WIN_INCL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(EZK_WINDOWS)
  #include "./ezk_window/win32.h"
#elif defined(EZK_APPLE)
  #include "./ezk_window/cocoa.h"
#elif defined(EZK_LINUX)
  #include "./ezk_window/x11.h"
#endif

// Typedefs
typedef struct {
  int id;
  int wx,wy;
  int px,py;
  char* name;
  int fs_state;
} ezk_window;

// Statics
static ezk_window** windows;
static int win_count = 0;

static int* free_ids;
static int free_id_count = 0;

// Functions, static and API

static void realloc_ids(int n) {
  if(!windows) {
    windows = malloc(n * sizeof(ezk_window*));
  } else {
    windows = realloc(windows, n * sizeof(ezk_window*));
  }
}

static void realloc_free_ids(int n) {
  if(!windows) {
    free_ids = malloc(n * sizeof(int));
  } else {
    free_ids = realloc(free_ids, n * sizeof(int));
  }
}

static int alloc_window_id(ezk_window* window) {
  int id = 0;
  if (free_id_count) {
    id = free_ids[--free_id_count]; // Last free id
    realloc_free_ids(free_id_count); // Truncate the list, removing the id we just used
  } else {
    realloc_ids(win_count + 1);
    id = win_count++;
    printf("Win Count: %d\n", win_count);
  }
  windows[id] = window;
  return id;
}

EZKAPI int ezk_create_window() {
  ezk_window* win = malloc(sizeof(ezk_window));
  if (!win) {return -1;}
  memset(win, 0, sizeof(ezk_window)); // Clear the structure
  alloc_window_id(win);
}

EZKAPI void ezk_free_windows() {
  if (free_ids) free(free_ids);
  if(windows) {
    for(int i = 0; i < win_count; i++) {
      if(windows[i]) {
        free(windows[i]);
      }
    }
      free(windows);
  }
}

#endif // EZK_WIN_INCL