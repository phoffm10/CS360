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

  ptrs[5] = my_malloc(151); dc[5] = 160;
  free_ptrs[8] = my_malloc(119);
  free_ptrs[2] = my_malloc(143);
  ptrs[12] = my_malloc(140); dc[12] = 152;
  free_ptrs[0] = my_malloc(149);
  ptrs[1] = my_malloc(115); dc[1] = 128;
  ptrs[10] = my_malloc(138); dc[10] = 152;
  ptrs[8] = my_malloc(116); dc[8] = 128;
  ptrs[3] = my_malloc(116); dc[3] = 128;
  free_ptrs[5] = my_malloc(116);
  ptrs[0] = my_malloc(132); dc[0] = 144;
  ptrs[7] = my_malloc(118); dc[7] = 128;
  ptrs[4] = my_malloc(148); dc[4] = 160;
  free_ptrs[4] = my_malloc(129);
  ptrs[11] = my_malloc(145); dc[11] = 160;
  ptrs[6] = my_malloc(131); dc[6] = 144;
  free_ptrs[13] = my_malloc(149);
  free_ptrs[11] = my_malloc(119);
  free_ptrs[7] = my_malloc(124);
  ptrs[2] = my_malloc(141); dc[2] = 152;
  free_ptrs[3] = my_malloc(132);
  free_ptrs[12] = my_malloc(127);
  free_ptrs[9] = my_malloc(141);
  free_ptrs[10] = my_malloc(135);
  free_ptrs[6] = my_malloc(126);
  ptrs[13] = my_malloc(129); dc[13] = 144;
  free_ptrs[1] = my_malloc(114);
  ptrs[9] = my_malloc(126); dc[9] = 136;

  my_free(free_ptrs[6]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[8]);

  ptrs[31] = my_malloc(78); dc[31] = 88;
  ptrs[17] = my_malloc(90); dc[17] = 104;
  ptrs[34] = my_malloc(90); dc[34] = 104;
  ptrs[27] = my_malloc(75); dc[27] = 88;
  ptrs[18] = my_malloc(85); dc[18] = 96;
  ptrs[23] = my_malloc(90); dc[23] = 104;
  ptrs[22] = my_malloc(73); dc[22] = 88;
  ptrs[19] = my_malloc(74); dc[19] = 88;
  ptrs[33] = my_malloc(94); dc[33] = 104;
  ptrs[21] = my_malloc(92); dc[21] = 104;
  ptrs[16] = my_malloc(80); dc[16] = 88;
  ptrs[26] = my_malloc(80); dc[26] = 88;
  ptrs[29] = my_malloc(91); dc[29] = 104;
  ptrs[20] = my_malloc(81); dc[20] = 96;
  ptrs[25] = my_malloc(89); dc[25] = 104;
  ptrs[28] = my_malloc(90); dc[28] = 104;
  ptrs[24] = my_malloc(76); dc[24] = 88;
  ptrs[32] = my_malloc(89); dc[32] = 104;
  ptrs[14] = my_malloc(88); dc[14] = 96;
  ptrs[30] = my_malloc(90); dc[30] = 104;
  ptrs[15] = my_malloc(75); dc[15] = 88;

  double_check_memory(ptrs, dc, 35, 15);
  printf("Correct\n");
  return 0;
}
