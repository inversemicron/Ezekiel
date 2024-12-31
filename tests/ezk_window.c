#include "../src/ezekiel.h"

void on_create(ezk_win_id id) {
  printf("New window id: %d\n", id);
}

void on_event(ezk_win_id id, ezk_event ev) {

}

void on_quit(ezk_win_id id) {
  printf("AAAA it hurts\n");
}

ezk_win_desc desc = {
  .dims = (ezk_v2_i){900,600},
  .pos = (ezk_v2_i){0,0},
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
  .event_cb = on_event,
  .quit_cb = on_quit
};

int main(int argc, char** argv) {
  int id1 = ezk_create_window(desc);
  int id2 = ezk_create_window(desc);
  while(!(ezk_window_quitted(id1) && ezk_window_quitted(id2))) {
    ezk_update_windows();
  }
  return 0;
}