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
  int *ptrs[40];
  int *free_ptrs[16];
  int dc[40];

  ptrs[13] = my_malloc(116); dc[13] = 128;
  free_ptrs[5] = my_malloc(131);
  ptrs[9] = my_malloc(127); dc[9] = 136;
  ptrs[15] = my_malloc(122); dc[15] = 136;
  free_ptrs[0] = my_malloc(123);
  ptrs[6] = my_malloc(117); dc[6] = 128;
  ptrs[12] = my_malloc(121); dc[12] = 136;
  ptrs[0] = my_malloc(127); dc[0] = 136;
  ptrs[2] = my_malloc(120); dc[2] = 128;
  ptrs[7] = my_malloc(135); dc[7] = 144;
  ptrs[1] = my_malloc(118); dc[1] = 128;
  ptrs[3] = my_malloc(131); dc[3] = 144;
  free_ptrs[3] = my_malloc(132);
  ptrs[5] = my_malloc(131); dc[5] = 144;
  ptrs[8] = my_malloc(137); dc[8] = 152;
  free_ptrs[7] = my_malloc(113);
  ptrs[4] = my_malloc(113); dc[4] = 128;
  free_ptrs[2] = my_malloc(121);
  free_ptrs[15] = my_malloc(149);
  free_ptrs[14] = my_malloc(121);
  free_ptrs[12] = my_malloc(128);
  free_ptrs[10] = my_malloc(125);
  free_ptrs[11] = my_malloc(123);
  free_ptrs[13] = my_malloc(126);
  free_ptrs[6] = my_malloc(113);
  ptrs[10] = my_malloc(119); dc[10] = 128;
  free_ptrs[8] = my_malloc(151);
  free_ptrs[4] = my_malloc(124);
  free_ptrs[1] = my_malloc(143);
  free_ptrs[9] = my_malloc(150);
  ptrs[14] = my_malloc(121); dc[14] = 136;
  ptrs[11] = my_malloc(132); dc[11] = 144;

  my_free(free_ptrs[2]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[14]);

  ptrs[21] = my_malloc(78); dc[21] = 88;
  ptrs[31] = my_malloc(73); dc[31] = 88;
  ptrs[22] = my_malloc(88); dc[22] = 96;
  ptrs[24] = my_malloc(87); dc[24] = 96;
  ptrs[26] = my_malloc(79); dc[26] = 88;
  ptrs[39] = my_malloc(81); dc[39] = 96;
  ptrs[37] = my_malloc(82); dc[37] = 96;
  ptrs[30] = my_malloc(84); dc[30] = 96;
  ptrs[25] = my_malloc(81); dc[25] = 96;
  ptrs[32] = my_malloc(76); dc[32] = 88;
  ptrs[29] = my_malloc(90); dc[29] = 104;
  ptrs[20] = my_malloc(74); dc[20] = 88;
  ptrs[28] = my_malloc(75); dc[28] = 88;
  ptrs[23] = my_malloc(85); dc[23] = 96;
  ptrs[17] = my_malloc(93); dc[17] = 104;
  ptrs[36] = my_malloc(75); dc[36] = 88;
  ptrs[34] = my_malloc(89); dc[34] = 104;
  ptrs[18] = my_malloc(92); dc[18] = 104;
  ptrs[16] = my_malloc(83); dc[16] = 96;
  ptrs[19] = my_malloc(77); dc[19] = 88;
  ptrs[33] = my_malloc(93); dc[33] = 104;
  ptrs[27] = my_malloc(91); dc[27] = 104;
  ptrs[38] = my_malloc(86); dc[38] = 96;
  ptrs[35] = my_malloc(80); dc[35] = 88;

  double_check_memory(ptrs, dc, 40, 17);
  printf("Correct\n");
  return 0;
}
