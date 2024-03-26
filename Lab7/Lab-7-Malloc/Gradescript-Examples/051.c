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

  ptrs[26] = my_malloc(117); dc[26] = 128;
  ptrs[22] = my_malloc(139); dc[22] = 152;
  ptrs[8] = my_malloc(148); dc[8] = 160;
  ptrs[24] = my_malloc(131); dc[24] = 144;
  free_ptrs[3] = my_malloc(94);
  ptrs[2] = my_malloc(136); dc[2] = 144;
  free_ptrs[5] = my_malloc(80);
  ptrs[19] = my_malloc(124); dc[19] = 136;
  ptrs[28] = my_malloc(151); dc[28] = 160;
  free_ptrs[1] = my_malloc(80);
  free_ptrs[17] = my_malloc(89);
  ptrs[21] = my_malloc(120); dc[21] = 128;
  free_ptrs[21] = my_malloc(86);
  free_ptrs[10] = my_malloc(92);
  free_ptrs[7] = my_malloc(74);
  free_ptrs[14] = my_malloc(86);
  free_ptrs[6] = my_malloc(90);
  free_ptrs[2] = my_malloc(73);
  free_ptrs[4] = my_malloc(84);
  free_ptrs[13] = my_malloc(75);
  ptrs[23] = my_malloc(132); dc[23] = 144;
  free_ptrs[0] = my_malloc(73);
  ptrs[20] = my_malloc(131); dc[20] = 144;
  free_ptrs[24] = my_malloc(80);
  free_ptrs[19] = my_malloc(87);
  free_ptrs[11] = my_malloc(81);
  ptrs[5] = my_malloc(148); dc[5] = 160;
  free_ptrs[22] = my_malloc(93);
  free_ptrs[27] = my_malloc(95);
  ptrs[15] = my_malloc(148); dc[15] = 160;
  free_ptrs[15] = my_malloc(89);
  free_ptrs[26] = my_malloc(91);
  free_ptrs[28] = my_malloc(91);
  ptrs[3] = my_malloc(144); dc[3] = 152;
  free_ptrs[12] = my_malloc(87);
  free_ptrs[25] = my_malloc(87);
  ptrs[12] = my_malloc(121); dc[12] = 136;
  free_ptrs[9] = my_malloc(75);
  ptrs[16] = my_malloc(121); dc[16] = 136;
  free_ptrs[18] = my_malloc(93);
  free_ptrs[16] = my_malloc(84);
  free_ptrs[23] = my_malloc(76);
  free_ptrs[8] = my_malloc(82);
  ptrs[4] = my_malloc(136); dc[4] = 144;
  ptrs[10] = my_malloc(141); dc[10] = 152;
  free_ptrs[20] = my_malloc(80);
  ptrs[1] = my_malloc(126); dc[1] = 136;
  my_free(free_ptrs[8]);
  ptrs[6] = my_malloc(128); dc[6] = 136;
  ptrs[18] = my_malloc(127); dc[18] = 136;
  ptrs[11] = my_malloc(140); dc[11] = 152;
  my_free(free_ptrs[17]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[11]);
  ptrs[0] = my_malloc(132); dc[0] = 144;
  ptrs[7] = my_malloc(144); dc[7] = 152;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[26]);
  ptrs[14] = my_malloc(138); dc[14] = 152;
  my_free(free_ptrs[25]);
  ptrs[17] = my_malloc(116); dc[17] = 128;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[6]);
  ptrs[9] = my_malloc(132); dc[9] = 144;
  ptrs[13] = my_malloc(139); dc[13] = 152;
  my_free(free_ptrs[18]);
  ptrs[25] = my_malloc(151); dc[25] = 160;
  ptrs[27] = my_malloc(146); dc[27] = 160;
  my_free(free_ptrs[9]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 13, 8192);
  printf("Correct\n");
  return 0;
}
