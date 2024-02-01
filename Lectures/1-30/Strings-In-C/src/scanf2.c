/* What happens when you try to use scanf to read into an uninitialized pointer. */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int *i;
  
  printf("i = 0x%lx\n", (unsigned long) i);
  if (scanf("%d", i) == 1) {
    printf("Just read i: %d (0x%x)\n", *i, *i);
  } else {
    printf("Scanf() failed for some reason.\n");
  }
  exit(0);
}
