#include <stdio.h>

#include "../ezk_platform.h"

int main() {
#ifdef EZK_UNIX
	printf("Hello from linux!\n");
#endif
}
