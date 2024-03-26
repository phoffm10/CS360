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
    if (nbytes == 0 || l < low) low = l;
    if (nbytes == 0 || h > high) high = h;
    nbytes += *ip;
  }
    
  nfl = 0;
  for (l = free_list_begin(); l != NULL; l = free_list_next(l)) {
    ip = (int *) l;
    h = l + *ip;
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
  int *ptrs[25];
  int *free_ptrs[10];
  int dc[25];

  ptrs[3] = my_malloc(119); dc[3] = 128;
  free_ptrs[4] = my_malloc(139);
  ptrs[8] = my_malloc(146); dc[8] = 160;
  ptrs[2] = my_malloc(128); dc[2] = 136;
  free_ptrs[0] = my_malloc(116);
  ptrs[6] = my_malloc(131); dc[6] = 144;
  free_ptrs[3] = my_malloc(123);
  ptrs[1] = my_malloc(149); dc[1] = 160;
  free_ptrs[7] = my_malloc(138);
  free_ptrs[8] = my_malloc(135);
  free_ptrs[5] = my_malloc(126);
  free_ptrs[6] = my_malloc(140);
  free_ptrs[9] = my_malloc(148);
  ptrs[5] = my_malloc(125); dc[5] = 136;
  ptrs[4] = my_malloc(126); dc[4] = 136;
  ptrs[9] = my_malloc(120); dc[9] = 128;
  free_ptrs[2] = my_malloc(123);
  free_ptrs[1] = my_malloc(134);
  ptrs[0] = my_malloc(146); dc[0] = 160;
  ptrs[7] = my_malloc(115); dc[7] = 128;

  my_free(free_ptrs[4]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[9]);

  ptrs[20] = my_malloc(83); dc[20] = 96;
  ptrs[12] = my_malloc(88); dc[12] = 96;
  ptrs[17] = my_malloc(79); dc[17] = 88;
  ptrs[19] = my_malloc(73); dc[19] = 88;
  ptrs[24] = my_malloc(78); dc[24] = 88;
  ptrs[11] = my_malloc(93); dc[11] = 104;
  ptrs[15] = my_malloc(87); dc[15] = 96;
  ptrs[13] = my_malloc(77); dc[13] = 88;
  ptrs[14] = my_malloc(81); dc[14] = 96;
  ptrs[21] = my_malloc(89); dc[21] = 104;
  ptrs[16] = my_malloc(87); dc[16] = 96;
  ptrs[22] = my_malloc(89); dc[22] = 104;
  ptrs[10] = my_malloc(92); dc[10] = 104;
  ptrs[23] = my_malloc(74); dc[23] = 88;
  ptrs[18] = my_malloc(88); dc[18] = 96;

  double_check_memory(ptrs, dc, 25, 11);
  printf("Correct\n");
  return 0;
}
