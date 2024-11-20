#include "../src/ezekiel.h"

int main(int argc, char** argv) {

  for(int i = 0; i < 1000; i++) {
    printf("Win Id: %d\n", ezk_create_window());
  }
  ezk_free_windows();
  return 0;
}