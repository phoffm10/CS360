#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

void double_check_memory(int **ptrs, int *dc, int nptrs, int fl_size, int tbytes)
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

  if (nbytes != tbytes) {
    printf("Error: Total bytes allocated and on the free list = %d, not %d\n", nbytes, tbytes);
    exit(0);
  }
    
  if (high - low != tbytes) {
    printf("Error: Highest address (0x%lx) minus lowest (0x%lx) does not equal %d\n", (unsigned long) high, (unsigned long) low, tbytes);
    exit(0);
  }

  if (nfl != fl_size && fl_size != -1) {
    printf("Error: %d nodes on the free list -- should be %d\n", nfl, fl_size);
    exit(0);
  }
}


int main()
{
  int *ptrs[31];
  int *free_ptrs[31];
  int dc[31];

  ptrs[22] = my_malloc(122); dc[22] = 136;
  free_ptrs[11] = my_malloc(82);
  ptrs[23] = my_malloc(127); dc[23] = 136;
  free_ptrs[15] = my_malloc(85);
  ptrs[17] = my_malloc(150); dc[17] = 160;
  free_ptrs[2] = my_malloc(92);
  free_ptrs[23] = my_malloc(93);
  free_ptrs[13] = my_malloc(89);
  ptrs[14] = my_malloc(144); dc[14] = 152;
  free_ptrs[24] = my_malloc(93);
  ptrs[27] = my_malloc(145); dc[27] = 160;
  free_ptrs[19] = my_malloc(87);
  ptrs[21] = my_malloc(142); dc[21] = 152;
  free_ptrs[28] = my_malloc(82);
  free_ptrs[14] = my_malloc(73);
  ptrs[28] = my_malloc(139); dc[28] = 152;
  free_ptrs[17] = my_malloc(83);
  free_ptrs[26] = my_malloc(81);
  free_ptrs[9] = my_malloc(80);
  free_ptrs[29] = my_malloc(90);
  ptrs[4] = my_malloc(130); dc[4] = 144;
  free_ptrs[3] = my_malloc(86);
  free_ptrs[10] = my_malloc(93);
  free_ptrs[20] = my_malloc(84);
  ptrs[6] = my_malloc(124); dc[6] = 136;
  free_ptrs[6] = my_malloc(74);
  free_ptrs[27] = my_malloc(88);
  free_ptrs[0] = my_malloc(89);
  free_ptrs[4] = my_malloc(82);
  free_ptrs[8] = my_malloc(75);
  free_ptrs[25] = my_malloc(81);
  free_ptrs[21] = my_malloc(76);
  ptrs[8] = my_malloc(143); dc[8] = 152;
  ptrs[18] = my_malloc(113); dc[18] = 128;
  free_ptrs[1] = my_malloc(93);
  ptrs[13] = my_malloc(129); dc[13] = 144;
  free_ptrs[30] = my_malloc(75);
  free_ptrs[5] = my_malloc(73);
  free_ptrs[22] = my_malloc(93);
  free_ptrs[16] = my_malloc(88);
  ptrs[9] = my_malloc(134); dc[9] = 144;
  free_ptrs[7] = my_malloc(84);
  ptrs[12] = my_malloc(132); dc[12] = 144;
  ptrs[1] = my_malloc(123); dc[1] = 136;
  free_ptrs[18] = my_malloc(73);
  free_ptrs[12] = my_malloc(95);
  ptrs[5] = my_malloc(128); dc[5] = 136;
  ptrs[16] = my_malloc(151); dc[16] = 160;
  ptrs[2] = my_malloc(141); dc[2] = 152;
  my_free(free_ptrs[22]);
  ptrs[30] = my_malloc(126); dc[30] = 136;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[14]);
  ptrs[26] = my_malloc(118); dc[26] = 128;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[16]);
  ptrs[11] = my_malloc(130); dc[11] = 144;
  my_free(free_ptrs[24]);
  my_free(free_ptrs[21]);
  ptrs[25] = my_malloc(126); dc[25] = 136;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[3]);
  ptrs[29] = my_malloc(113); dc[29] = 128;
  my_free(free_ptrs[28]);
  my_free(free_ptrs[25]);
  ptrs[19] = my_malloc(149); dc[19] = 160;
  my_free(free_ptrs[5]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[13]);
  ptrs[24] = my_malloc(141); dc[24] = 152;
  my_free(free_ptrs[1]);
  ptrs[15] = my_malloc(134); dc[15] = 144;
  my_free(free_ptrs[19]);
  my_free(free_ptrs[26]);
  ptrs[0] = my_malloc(129); dc[0] = 144;
  my_free(free_ptrs[9]);
  ptrs[7] = my_malloc(144); dc[7] = 152;
  my_free(free_ptrs[11]);
  ptrs[10] = my_malloc(124); dc[10] = 136;
  my_free(free_ptrs[17]);
  ptrs[20] = my_malloc(141); dc[20] = 152;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[18]);
  ptrs[3] = my_malloc(129); dc[3] = 144;
  my_free(free_ptrs[8]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 14, 8192);
  printf("Correct\n");
  return 0;
}
