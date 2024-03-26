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
  int *ptrs[30];
  int *free_ptrs[12];
  int dc[30];

  free_ptrs[0] = my_malloc(146);
  ptrs[11] = my_malloc(126); dc[11] = 136;
  ptrs[10] = my_malloc(150); dc[10] = 160;
  free_ptrs[1] = my_malloc(132);
  free_ptrs[5] = my_malloc(129);
  free_ptrs[7] = my_malloc(130);
  free_ptrs[6] = my_malloc(117);
  ptrs[5] = my_malloc(142); dc[5] = 152;
  ptrs[4] = my_malloc(130); dc[4] = 144;
  ptrs[2] = my_malloc(150); dc[2] = 160;
  ptrs[3] = my_malloc(140); dc[3] = 152;
  free_ptrs[9] = my_malloc(121);
  ptrs[0] = my_malloc(141); dc[0] = 152;
  ptrs[7] = my_malloc(114); dc[7] = 128;
  ptrs[1] = my_malloc(131); dc[1] = 144;
  free_ptrs[10] = my_malloc(118);
  free_ptrs[11] = my_malloc(138);
  ptrs[6] = my_malloc(144); dc[6] = 152;
  ptrs[8] = my_malloc(135); dc[8] = 144;
  free_ptrs[8] = my_malloc(121);
  free_ptrs[3] = my_malloc(149);
  free_ptrs[2] = my_malloc(113);
  ptrs[9] = my_malloc(123); dc[9] = 136;
  free_ptrs[4] = my_malloc(151);

  my_free(free_ptrs[11]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[0]);

  ptrs[13] = my_malloc(73); dc[13] = 88;
  ptrs[21] = my_malloc(92); dc[21] = 104;
  ptrs[12] = my_malloc(92); dc[12] = 104;
  ptrs[29] = my_malloc(83); dc[29] = 96;
  ptrs[23] = my_malloc(82); dc[23] = 96;
  ptrs[17] = my_malloc(94); dc[17] = 104;
  ptrs[16] = my_malloc(94); dc[16] = 104;
  ptrs[15] = my_malloc(92); dc[15] = 104;
  ptrs[22] = my_malloc(88); dc[22] = 96;
  ptrs[18] = my_malloc(77); dc[18] = 88;
  ptrs[19] = my_malloc(77); dc[19] = 88;
  ptrs[27] = my_malloc(92); dc[27] = 104;
  ptrs[25] = my_malloc(93); dc[25] = 104;
  ptrs[26] = my_malloc(90); dc[26] = 104;
  ptrs[24] = my_malloc(78); dc[24] = 88;
  ptrs[28] = my_malloc(88); dc[28] = 96;
  ptrs[20] = my_malloc(93); dc[20] = 104;
  ptrs[14] = my_malloc(84); dc[14] = 96;

  double_check_memory(ptrs, dc, 30, 13);
  printf("Correct\n");
  return 0;
}
