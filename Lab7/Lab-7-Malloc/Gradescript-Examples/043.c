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
  int *ptrs[28];
  int *free_ptrs[28];
  int dc[28];

  free_ptrs[19] = my_malloc(92);
  free_ptrs[22] = my_malloc(92);
  ptrs[19] = my_malloc(141); dc[19] = 152;
  ptrs[23] = my_malloc(145); dc[23] = 160;
  ptrs[14] = my_malloc(135); dc[14] = 144;
  ptrs[2] = my_malloc(129); dc[2] = 144;
  free_ptrs[16] = my_malloc(76);
  free_ptrs[12] = my_malloc(88);
  ptrs[8] = my_malloc(144); dc[8] = 152;
  ptrs[16] = my_malloc(149); dc[16] = 160;
  free_ptrs[13] = my_malloc(86);
  free_ptrs[27] = my_malloc(86);
  ptrs[12] = my_malloc(116); dc[12] = 128;
  free_ptrs[0] = my_malloc(74);
  free_ptrs[23] = my_malloc(84);
  ptrs[0] = my_malloc(116); dc[0] = 128;
  ptrs[7] = my_malloc(140); dc[7] = 152;
  ptrs[26] = my_malloc(131); dc[26] = 144;
  free_ptrs[18] = my_malloc(83);
  free_ptrs[14] = my_malloc(82);
  ptrs[5] = my_malloc(142); dc[5] = 152;
  ptrs[9] = my_malloc(138); dc[9] = 152;
  free_ptrs[4] = my_malloc(84);
  free_ptrs[17] = my_malloc(73);
  free_ptrs[1] = my_malloc(79);
  free_ptrs[5] = my_malloc(89);
  ptrs[22] = my_malloc(144); dc[22] = 152;
  free_ptrs[7] = my_malloc(89);
  free_ptrs[15] = my_malloc(91);
  free_ptrs[20] = my_malloc(74);
  free_ptrs[10] = my_malloc(81);
  free_ptrs[24] = my_malloc(92);
  free_ptrs[2] = my_malloc(73);
  free_ptrs[26] = my_malloc(85);
  free_ptrs[9] = my_malloc(91);
  ptrs[18] = my_malloc(129); dc[18] = 144;
  ptrs[20] = my_malloc(144); dc[20] = 152;
  free_ptrs[3] = my_malloc(95);
  ptrs[4] = my_malloc(146); dc[4] = 160;
  free_ptrs[6] = my_malloc(92);
  free_ptrs[25] = my_malloc(85);
  free_ptrs[8] = my_malloc(78);
  free_ptrs[21] = my_malloc(83);
  free_ptrs[11] = my_malloc(75);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[15]);
  ptrs[15] = my_malloc(119); dc[15] = 128;
  my_free(free_ptrs[20]);
  my_free(free_ptrs[11]);
  ptrs[27] = my_malloc(127); dc[27] = 136;
  my_free(free_ptrs[25]);
  ptrs[3] = my_malloc(133); dc[3] = 144;
  ptrs[21] = my_malloc(145); dc[21] = 160;
  my_free(free_ptrs[10]);
  ptrs[1] = my_malloc(117); dc[1] = 128;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[3]);
  ptrs[25] = my_malloc(125); dc[25] = 136;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[0]);
  ptrs[13] = my_malloc(124); dc[13] = 136;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[27]);
  ptrs[24] = my_malloc(128); dc[24] = 136;
  ptrs[10] = my_malloc(142); dc[10] = 152;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[26]);
  ptrs[17] = my_malloc(118); dc[17] = 128;
  my_free(free_ptrs[16]);
  ptrs[11] = my_malloc(120); dc[11] = 128;
  my_free(free_ptrs[22]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[23]);
  ptrs[6] = my_malloc(134); dc[6] = 144;
  my_free(free_ptrs[6]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 10, 8192);
  printf("Correct\n");
  return 0;
}
