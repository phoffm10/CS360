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
  int *ptrs[27];
  int *free_ptrs[27];
  int dc[27];

  free_ptrs[23] = my_malloc(81);
  free_ptrs[26] = my_malloc(77);
  free_ptrs[2] = my_malloc(81);
  free_ptrs[19] = my_malloc(76);
  free_ptrs[7] = my_malloc(93);
  ptrs[16] = my_malloc(149); dc[16] = 160;
  ptrs[2] = my_malloc(142); dc[2] = 152;
  free_ptrs[15] = my_malloc(86);
  free_ptrs[17] = my_malloc(93);
  ptrs[12] = my_malloc(125); dc[12] = 136;
  free_ptrs[1] = my_malloc(94);
  free_ptrs[25] = my_malloc(75);
  free_ptrs[22] = my_malloc(88);
  free_ptrs[11] = my_malloc(89);
  free_ptrs[16] = my_malloc(91);
  free_ptrs[3] = my_malloc(88);
  ptrs[11] = my_malloc(117); dc[11] = 128;
  free_ptrs[21] = my_malloc(94);
  ptrs[15] = my_malloc(130); dc[15] = 144;
  free_ptrs[6] = my_malloc(88);
  free_ptrs[5] = my_malloc(79);
  ptrs[25] = my_malloc(131); dc[25] = 144;
  free_ptrs[0] = my_malloc(87);
  ptrs[19] = my_malloc(121); dc[19] = 136;
  free_ptrs[4] = my_malloc(89);
  free_ptrs[9] = my_malloc(93);
  free_ptrs[14] = my_malloc(89);
  free_ptrs[13] = my_malloc(88);
  free_ptrs[18] = my_malloc(80);
  free_ptrs[12] = my_malloc(85);
  free_ptrs[20] = my_malloc(94);
  free_ptrs[10] = my_malloc(89);
  free_ptrs[24] = my_malloc(92);
  ptrs[5] = my_malloc(142); dc[5] = 152;
  free_ptrs[8] = my_malloc(84);
  ptrs[26] = my_malloc(117); dc[26] = 128;
  my_free(free_ptrs[14]);
  ptrs[14] = my_malloc(140); dc[14] = 152;
  my_free(free_ptrs[7]);
  ptrs[13] = my_malloc(121); dc[13] = 136;
  my_free(free_ptrs[24]);
  ptrs[18] = my_malloc(135); dc[18] = 144;
  ptrs[4] = my_malloc(128); dc[4] = 136;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[8]);
  ptrs[20] = my_malloc(132); dc[20] = 144;
  ptrs[1] = my_malloc(123); dc[1] = 136;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[22]);
  ptrs[17] = my_malloc(134); dc[17] = 144;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[13]);
  ptrs[0] = my_malloc(114); dc[0] = 128;
  ptrs[7] = my_malloc(118); dc[7] = 128;
  my_free(free_ptrs[25]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[12]);
  ptrs[23] = my_malloc(122); dc[23] = 136;
  ptrs[3] = my_malloc(124); dc[3] = 136;
  ptrs[6] = my_malloc(124); dc[6] = 136;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[18]);
  ptrs[21] = my_malloc(130); dc[21] = 144;
  ptrs[8] = my_malloc(131); dc[8] = 144;
  my_free(free_ptrs[3]);
  ptrs[10] = my_malloc(140); dc[10] = 152;
  my_free(free_ptrs[17]);
  ptrs[9] = my_malloc(137); dc[9] = 152;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[20]);
  ptrs[22] = my_malloc(116); dc[22] = 128;
  my_free(free_ptrs[0]);
  ptrs[24] = my_malloc(134); dc[24] = 144;
  my_free(free_ptrs[5]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 9, 8192);
  printf("Correct\n");
  return 0;
}
