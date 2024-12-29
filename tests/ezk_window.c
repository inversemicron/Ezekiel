#include "../src/ezekiel.h"

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
  .border_width = 10
};

int main(int argc, char** argv) {
  int id1 = ezk_create_window(desc);
  for(;;) {
    ezk_update_window(id1);
  }
  int id2 = ezk_create_window(desc);
  for(;;) {
    ezk_update_window(id2);
  }
  ezk_free_windows();
  return 0;
}