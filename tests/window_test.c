#include "../include/ezekiel.h"

#include <stdio.h>

void on_create(ezk_win_id id) {
  printf("New window id: %d\n", id);
}

void on_event(ezk_win_id id, ezk_event ev) {
  switch(ev.type) {
    case EZK_EVENT_KEYDOWN:
      switch (ev.key.key) {
        case EZK_KEY_ONE:
          ezk_window_flip_fs(id);
          break;
      case EZK_KEY_ARROWUP:
        ezk_window_set_pos(id, (ezk_v2_i){0,-10}, true);
        break;  
      case EZK_KEY_ARROWDOWN:
        ezk_window_set_pos(id, (ezk_v2_i){0,10}, true);
        break; 
      case EZK_KEY_ARROWLEFT:
        ezk_window_set_pos(id, (ezk_v2_i){-10,0}, true);
        break; 
      case EZK_KEY_ARROWRIGHT:
        ezk_window_set_pos(id, (ezk_v2_i){10,0}, true);
        break;
      case EZK_KEY_x: 
        ezk_window_quit(id);
        break;
    }
  }
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

  .create_cb = on_create,
  .event_cb = on_event,
  .quit_cb = on_quit
};

int main() {
  int id1 = ezk_window_create(desc);
  int id2 = 0;//ezk_window_create(desc);
  while(!ezk_window_quitted(id1) || !ezk_window_quitted(id2)) {
    ezk_window_update_all();
  }
  
  ezk_window_free(id1);
  ezk_window_free(id2);

  return 0;
}
