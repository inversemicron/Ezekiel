#include "../include/ezekiel.h"

#include <stdio.h>

void on_create(ezk_win_id id) {
  printf("New window id: %d\n", id);
}

void on_event(ezk_win_id id, ezk_event ev) {
  id = ev.any.win_id;
  ev.any.win_id = id;
}

void on_quit(ezk_win_id id) {
  printf("Killing window id: %d\n", id);
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

  .border_type = EZK_WIN_BGTYPE_COPYFROMPARENT,
  .border_color = 0,
  .border_image = 0,
  .border_width = 10,

  .create_cb = on_create,
  //.event_cb = on_event,
  .quit_cb = on_quit
};

int main() {
  int id1 = ezk_create_window(desc);
  while(!ezk_window_quitted(id1)) {
    ezk_update_windows();
  }

  return 0;
}