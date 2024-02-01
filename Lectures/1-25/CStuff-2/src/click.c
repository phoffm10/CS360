#include <stdio.h>
#include <stdlib.h>

int main()
{
  unsigned int p[2];
  unsigned int x;
  unsigned char *cp;
  unsigned char c;

  p[0] = 0x28f4a13e;
  p[1] = 0xbc70695d;
  cp = (unsigned char *) p;

  c = cp[0];                          printf("0x%02x\n", c);
  c = cp[6];                          printf("0x%02x\n", c);
  c = (p[0] >> 8);                    printf("0x%02x\n", c);
  x = ((p[0] >> 16) | (p[1] << 16));  printf("0x%08x\n", x);
  return 0;
}
