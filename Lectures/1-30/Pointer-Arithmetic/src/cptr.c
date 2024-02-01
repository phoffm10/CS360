/* This is the same as src/iptr.c, except iarray is an array of chars instead of ints. */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long (UL);

int main()
{
  char iarray[10];
  char *ip;
  int i;

  for (i = 0; i < 10; i++) iarray[i] = 100+i;
  printf("iarray = 0x%lx\n", (UL) iarray);

  ip = iarray;

  for (i = 0; i < 10; i++) {
    printf("i=%d.  ",            i              );
    printf("iarray[i]=%d.  ",    iarray[i]      );
    printf("ip = 0x%lx.  ",      (UL) ip        );
    printf("*ip=%d.  ",          *ip            );
    printf("(ip-iarray)=%ld.\n", (UL) (ip-iarray));
    ip++;
  }

  return 0;
}
