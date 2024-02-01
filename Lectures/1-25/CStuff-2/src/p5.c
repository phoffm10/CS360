/* Adding typecast statements to make the 
   warnings from src/p3.c go away. */

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

  printf("ip = 0x%lx.  jp = 0x%lx\n", 
         (long unsigned int) ip,   /* Here they are. */
         (long unsigned int) jp);
  return 0;
}
