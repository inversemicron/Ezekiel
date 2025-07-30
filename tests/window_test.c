#include "../include/ezekiel.h"

#include <stdio.h>

void on_create(ezk_win_id id) {
  printf("New window id: %d\n", id);
}

void on_event(ezk_win_id id, ezk_event ev) {
  switch (ev.type) {
    case EZK_EVENT_KEYDOWN:
      switch (ev.key.key) {
        case EZK_KEY_ONE:
          ezk_window_flip_fs(id);
          break;
        case EZK_KEY_ARROWUP:
          ezk_window_set_pos(id, (ezk_v2i) {0, -10}, true);
          break;
        case EZK_KEY_ARROWDOWN:
          ezk_window_set_pos(id, (ezk_v2i) {0, 10}, true);
          break;
        case EZK_KEY_ARROWLEFT:
          ezk_window_set_pos(id, (ezk_v2i) {-10, 0}, true);
          break;
        case EZK_KEY_ARROWRIGHT:
          ezk_window_set_pos(id, (ezk_v2i) {10, 0}, true);
          break;
        case EZK_KEY_x:
          ezk_window_request_close(id);
          break;
      }
      break;
    case EZK_EVENT_CLOSE_REQUESTED:
      printf("Quit requested for window id: %d\n", id);
      if(ezk_window_is_key_down(id, EZK_KEY_z)) {
      	ezk_window_cancel_close(id);
      }
  }
}

void on_quit(ezk_win_id id) {
  printf("Window id %i exited\n", id);
}

ezk_win_desc desc = {
    .dims.x = 900,
    .dims.y = 600,
    .pos.x = 0,
    .pos.y = 0,
    .fullscreen = false,
    .name = "ezk_window test",

    .bg_type = EZK_WIN_BGTYPE_COPYFROMPARENT,
    .bg_color = 0,
    .bg_image = 0,

    .create_cb = on_create,
    .event_cb = on_event,
    .update_cb = 0,
    .exit_cb = 0
};

int main() {
  int id = ezk_window_create(desc);
  while (!ezk_window_closed(id)) {
    ezk_window_update_all();
  }

  return 0;
}
