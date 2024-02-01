/* Using a typedef to make the typecast statements a little less cumbersome. */

#include <stdio.h>
#include <stdlib.h>

typedef long unsigned int LU;        /* Now, I can use "(LU)" rather than "(long unsigned int). */

int main()
{
  int i;
  char j[14];
  int *ip;
  char *jp;

  ip = &i;
  jp = j;

  printf("ip = 0x%lx.  jp = 0x%lx\n", (LU) ip, (LU) jp);
  return 0;
}
