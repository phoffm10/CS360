#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

void double_check_memory(int **ptrs, int *dc, int nptrs, int fl_size)
{
  void *low, *l;
  void *high, *h;
  int *ip, i;
  int nbytes;
  int nfl;

  nbytes = 0;

  for (i = 0; i < nptrs; i++) {
    l = (void *) ptrs[i];
    l -= 8;
    ip = (int *) l;

    if (*ip != dc[i]) {
      printf("Error: pointer number %d the wrong size (%d instead of %d)\n", i, *ip, dc[i]);
      exit(1);
    }
    h = l + *ip;
    /* printf("P: 0x%lx 0x%lx %d\n", l, h, *ip); */
    if (nbytes == 0 || l < low) low = l;
    if (nbytes == 0 || h > high) high = h;
    nbytes += *ip;
  }
    
  nfl = 0;
  for (l = free_list_begin(); l != NULL; l = free_list_next(l)) {
    ip = (int *) l;
    h = l + *ip;
    /* printf("F: 0x%lx 0x%lx %d\n", l, h, *ip); */
    if (nbytes == 0 || l < low) low = l;
    if (nbytes == 0 || h > high) high = h;
    nbytes += *ip;
    nfl++;
  }

  if (nbytes != 8192) {
    printf("Error: Total bytes allocated and on the free list = %d, not 8192\n", nbytes);
    exit(0);
  }
    
  if (high - low != 8192) {
    printf("Error: Highest address (0x%lx) minus lowest (0x%lx) does not equal 8192\n", (unsigned long) high, (unsigned long) low);
    exit(0);
  }

  if (nfl != fl_size && fl_size != -1) {
    printf("Error: %d nodes on the free list -- should be %d\n", nfl, fl_size);
    exit(0);
  }
}

int main()
{
  int *ptrs[9];
  int *free_ptrs[9];
  int dc[9];
  int i;

  for (i = 0; i < 8; i++) dc[i] = 1024;

  for (i = 0; i < 4; i++) {
    ptrs[i] = my_malloc(1010);
    free_ptrs[i] = my_malloc(1009);
  }
  for (i = 0; i < 4; i++) {
    my_free(free_ptrs[i]);
    ptrs[i+4] = my_malloc(1010);
  }

  double_check_memory(ptrs, dc, 8, 0);
  printf("Correct\n");
  return 0;
}
