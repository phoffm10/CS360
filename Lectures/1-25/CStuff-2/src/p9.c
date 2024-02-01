/* This is the same as src/p8.c, but we've changed i to a long. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long unsigned int LUI;

int main()
{
  char s[4];
  long i;
  char *s2;

  strcpy(s, "Jim"); 
  i = (long) s;
  printf("Before incrementing i.\n");
  printf("i = %ld (0x%lx)\n", i, i);
  printf("s = %ld (0x%lx)\n", (LUI) s, (LUI) s);

  i++;
  s2 = (char *) i;
  printf("\n");
  printf("After incrementing i.\n");
  printf("s = 0x%lx.  s2 = 0x%lx, i = 0x%lx\n", (LUI) s, (LUI) s2, i);
  printf("s[0] = %c, s[1] = %c, *s2 = %c\n", s[0], s[1], *s2);
  return 0;
}
