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
  int *ptrs[35];
  int *free_ptrs[14];
  int dc[35];

  free_ptrs[6] = my_malloc(140);
  ptrs[6] = my_malloc(146); dc[6] = 160;
  free_ptrs[2] = my_malloc(151);
  ptrs[12] = my_malloc(119); dc[12] = 128;
  ptrs[2] = my_malloc(133); dc[2] = 144;
  free_ptrs[9] = my_malloc(129);
  ptrs[11] = my_malloc(118); dc[11] = 128;
  ptrs[8] = my_malloc(124); dc[8] = 136;
  ptrs[1] = my_malloc(124); dc[1] = 136;
  free_ptrs[7] = my_malloc(116);
  free_ptrs[8] = my_malloc(124);
  free_ptrs[0] = my_malloc(137);
  free_ptrs[11] = my_malloc(128);
  free_ptrs[5] = my_malloc(151);
  ptrs[3] = my_malloc(150); dc[3] = 160;
  ptrs[5] = my_malloc(131); dc[5] = 144;
  free_ptrs[13] = my_malloc(137);
  free_ptrs[4] = my_malloc(127);
  ptrs[4] = my_malloc(134); dc[4] = 144;
  free_ptrs[3] = my_malloc(120);
  ptrs[0] = my_malloc(136); dc[0] = 144;
  ptrs[7] = my_malloc(113); dc[7] = 128;
  free_ptrs[1] = my_malloc(144);
  ptrs[9] = my_malloc(126); dc[9] = 136;
  ptrs[13] = my_malloc(113); dc[13] = 128;
  ptrs[10] = my_malloc(117); dc[10] = 128;
  free_ptrs[10] = my_malloc(118);
  free_ptrs[12] = my_malloc(139);

  my_free(free_ptrs[2]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[1]);

  ptrs[23] = my_malloc(78); dc[23] = 88;
  ptrs[17] = my_malloc(95); dc[17] = 104;
  ptrs[21] = my_malloc(87); dc[21] = 96;
  ptrs[30] = my_malloc(73); dc[30] = 88;
  ptrs[16] = my_malloc(94); dc[16] = 104;
  ptrs[15] = my_malloc(88); dc[15] = 96;
  ptrs[27] = my_malloc(81); dc[27] = 96;
  ptrs[34] = my_malloc(77); dc[34] = 88;
  ptrs[28] = my_malloc(83); dc[28] = 96;
  ptrs[26] = my_malloc(76); dc[26] = 88;
  ptrs[25] = my_malloc(85); dc[25] = 96;
  ptrs[31] = my_malloc(74); dc[31] = 88;
  ptrs[14] = my_malloc(76); dc[14] = 88;
  ptrs[32] = my_malloc(93); dc[32] = 104;
  ptrs[20] = my_malloc(93); dc[20] = 104;
  ptrs[33] = my_malloc(74); dc[33] = 88;
  ptrs[24] = my_malloc(90); dc[24] = 104;
  ptrs[22] = my_malloc(91); dc[22] = 104;
  ptrs[29] = my_malloc(85); dc[29] = 96;
  ptrs[18] = my_malloc(89); dc[18] = 104;
  ptrs[19] = my_malloc(93); dc[19] = 104;

  double_check_memory(ptrs, dc, 35, 15);
  printf("Correct\n");
  return 0;
}
