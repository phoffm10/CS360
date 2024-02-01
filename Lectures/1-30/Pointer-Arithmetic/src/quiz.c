#include <stdio.h>

int main()
{
  int i, array[10];
  int *ip, *a1;
  int **ipp;

  ip = &i;
  ipp = &ip;
  a1 = &(array[1]);

  for (i = 0; i < 10; i++) array[i] = i;

  i = 11;

  printf("ip: 0x%lx, &ip: 0x%lx, array: 0x%lx\n", (unsigned long) ip, (unsigned long) &ip, (unsigned long) array);
  printf("\n");
  

  printf("&i: 0x%lx\n", (unsigned long) &i);
  printf("ipp: 0x%lx, *ipp: 0x%lx, **ipp: 0x%lx\n", (unsigned long) ipp, (unsigned long) *ipp, (unsigned long) **ipp);
  printf("\n");
  printf("a1: 0x%lx, *a1: 0x%lx\n", (unsigned long) a1, (unsigned long) *a1);

  a1 += 4;
  *a1 = 500;
  
  for (i = 0; i < 10; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}
  
