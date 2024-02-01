/* Print out pointers of local variables */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i;
  char j[14];
  int *ip;
  char *jp;

  ip = &i;
  jp = j;

  printf("ip = 0x%lx.  jp = 0x%lx\n", (unsigned long) ip, jp);
  return 0;
}
