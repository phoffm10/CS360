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
  int *ptrs[45];
  int *free_ptrs[18];
  int dc[45];

  ptrs[17] = my_malloc(138); dc[17] = 152;
  ptrs[3] = my_malloc(151); dc[3] = 160;
  free_ptrs[4] = my_malloc(113);
  free_ptrs[1] = my_malloc(113);
  ptrs[5] = my_malloc(120); dc[5] = 128;
  ptrs[2] = my_malloc(118); dc[2] = 128;
  ptrs[16] = my_malloc(123); dc[16] = 136;
  ptrs[12] = my_malloc(151); dc[12] = 160;
  ptrs[1] = my_malloc(151); dc[1] = 160;
  ptrs[6] = my_malloc(127); dc[6] = 136;
  ptrs[4] = my_malloc(131); dc[4] = 144;
  ptrs[13] = my_malloc(119); dc[13] = 128;
  free_ptrs[0] = my_malloc(115);
  free_ptrs[16] = my_malloc(131);
  free_ptrs[10] = my_malloc(150);
  free_ptrs[7] = my_malloc(144);
  free_ptrs[15] = my_malloc(150);
  free_ptrs[8] = my_malloc(139);
  ptrs[9] = my_malloc(128); dc[9] = 136;
  free_ptrs[12] = my_malloc(146);
  ptrs[15] = my_malloc(139); dc[15] = 152;
  ptrs[14] = my_malloc(116); dc[14] = 128;
  free_ptrs[14] = my_malloc(133);
  free_ptrs[17] = my_malloc(114);
  free_ptrs[2] = my_malloc(136);
  free_ptrs[6] = my_malloc(117);
  ptrs[8] = my_malloc(150); dc[8] = 160;
  free_ptrs[13] = my_malloc(120);
  ptrs[10] = my_malloc(149); dc[10] = 160;
  ptrs[0] = my_malloc(129); dc[0] = 144;
  free_ptrs[5] = my_malloc(136);
  ptrs[11] = my_malloc(135); dc[11] = 144;
  ptrs[7] = my_malloc(118); dc[7] = 128;
  free_ptrs[3] = my_malloc(146);
  free_ptrs[9] = my_malloc(120);
  free_ptrs[11] = my_malloc(138);

  my_free(free_ptrs[2]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[15]);

  ptrs[35] = my_malloc(85); dc[35] = 96;
  ptrs[21] = my_malloc(93); dc[21] = 104;
  ptrs[20] = my_malloc(77); dc[20] = 88;
  ptrs[30] = my_malloc(95); dc[30] = 104;
  ptrs[43] = my_malloc(89); dc[43] = 104;
  ptrs[33] = my_malloc(93); dc[33] = 104;
  ptrs[36] = my_malloc(83); dc[36] = 96;
  ptrs[22] = my_malloc(73); dc[22] = 88;
  ptrs[18] = my_malloc(83); dc[18] = 96;
  ptrs[26] = my_malloc(81); dc[26] = 96;
  ptrs[41] = my_malloc(75); dc[41] = 88;
  ptrs[23] = my_malloc(73); dc[23] = 88;
  ptrs[34] = my_malloc(95); dc[34] = 104;
  ptrs[44] = my_malloc(76); dc[44] = 88;
  ptrs[24] = my_malloc(86); dc[24] = 96;
  ptrs[32] = my_malloc(92); dc[32] = 104;
  ptrs[37] = my_malloc(80); dc[37] = 88;
  ptrs[38] = my_malloc(73); dc[38] = 88;
  ptrs[31] = my_malloc(85); dc[31] = 96;
  ptrs[29] = my_malloc(89); dc[29] = 104;
  ptrs[28] = my_malloc(92); dc[28] = 104;
  ptrs[25] = my_malloc(76); dc[25] = 88;
  ptrs[27] = my_malloc(94); dc[27] = 104;
  ptrs[42] = my_malloc(90); dc[42] = 104;
  ptrs[39] = my_malloc(73); dc[39] = 88;
  ptrs[19] = my_malloc(85); dc[19] = 96;
  ptrs[40] = my_malloc(80); dc[40] = 88;

  double_check_memory(ptrs, dc, 45, 19);
  printf("Correct\n");
  return 0;
}
