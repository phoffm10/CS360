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
  int *ptrs[29];
  int *free_ptrs[29];
  int dc[29];

  free_ptrs[0] = my_malloc(95);
  free_ptrs[5] = my_malloc(94);
  free_ptrs[10] = my_malloc(88);
  free_ptrs[6] = my_malloc(90);
  ptrs[9] = my_malloc(141); dc[9] = 152;
  free_ptrs[20] = my_malloc(90);
  free_ptrs[21] = my_malloc(78);
  ptrs[23] = my_malloc(124); dc[23] = 136;
  free_ptrs[22] = my_malloc(93);
  free_ptrs[26] = my_malloc(86);
  free_ptrs[27] = my_malloc(85);
  ptrs[10] = my_malloc(127); dc[10] = 136;
  free_ptrs[13] = my_malloc(73);
  free_ptrs[16] = my_malloc(77);
  free_ptrs[1] = my_malloc(81);
  free_ptrs[19] = my_malloc(73);
  free_ptrs[7] = my_malloc(94);
  free_ptrs[18] = my_malloc(93);
  ptrs[28] = my_malloc(140); dc[28] = 152;
  free_ptrs[17] = my_malloc(82);
  ptrs[16] = my_malloc(140); dc[16] = 152;
  free_ptrs[15] = my_malloc(94);
  ptrs[12] = my_malloc(118); dc[12] = 128;
  ptrs[5] = my_malloc(139); dc[5] = 152;
  free_ptrs[2] = my_malloc(80);
  free_ptrs[8] = my_malloc(77);
  free_ptrs[23] = my_malloc(81);
  ptrs[17] = my_malloc(136); dc[17] = 144;
  ptrs[21] = my_malloc(132); dc[21] = 144;
  free_ptrs[3] = my_malloc(82);
  free_ptrs[4] = my_malloc(84);
  ptrs[13] = my_malloc(117); dc[13] = 128;
  free_ptrs[9] = my_malloc(77);
  free_ptrs[24] = my_malloc(83);
  free_ptrs[28] = my_malloc(74);
  free_ptrs[12] = my_malloc(76);
  free_ptrs[25] = my_malloc(79);
  free_ptrs[11] = my_malloc(74);
  ptrs[15] = my_malloc(133); dc[15] = 144;
  ptrs[24] = my_malloc(115); dc[24] = 128;
  free_ptrs[14] = my_malloc(86);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[19]);
  ptrs[19] = my_malloc(147); dc[19] = 160;
  ptrs[2] = my_malloc(132); dc[2] = 144;
  my_free(free_ptrs[3]);
  ptrs[1] = my_malloc(136); dc[1] = 144;
  ptrs[8] = my_malloc(113); dc[8] = 128;
  my_free(free_ptrs[25]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[11]);
  ptrs[26] = my_malloc(129); dc[26] = 144;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[9]);
  ptrs[22] = my_malloc(116); dc[22] = 128;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[26]);
  ptrs[11] = my_malloc(124); dc[11] = 136;
  ptrs[6] = my_malloc(151); dc[6] = 160;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[22]);
  ptrs[27] = my_malloc(151); dc[27] = 160;
  ptrs[20] = my_malloc(138); dc[20] = 152;
  my_free(free_ptrs[20]);
  ptrs[25] = my_malloc(133); dc[25] = 144;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[17]);
  ptrs[0] = my_malloc(143); dc[0] = 152;
  ptrs[14] = my_malloc(136); dc[14] = 144;
  ptrs[7] = my_malloc(123); dc[7] = 136;
  ptrs[4] = my_malloc(147); dc[4] = 160;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[28]);
  ptrs[18] = my_malloc(148); dc[18] = 160;
  ptrs[3] = my_malloc(138); dc[3] = 152;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[13]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 11, 8192);
  printf("Correct\n");
  return 0;
}
