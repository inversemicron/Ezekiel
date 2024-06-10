#define EZK_IMPL
#define EZK_WIN
#define EZK_GL
#include "../ezk_window.h"

int main() {
	int window = ezk_create_window();

  ezk_show_window(window);
  ezk_main_loop(window);
}
