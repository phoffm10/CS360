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
  int *ptrs[32];
  int *free_ptrs[16];
  int dc[32];

  free_ptrs[13] = my_malloc(8918);
  free_ptrs[10] = my_malloc(8910);
  free_ptrs[4] = my_malloc(8656);
  ptrs[5] = my_malloc(12658); dc[5] = 12672;
  ptrs[13] = my_malloc(12483); dc[13] = 12496;
  ptrs[15] = my_malloc(12909); dc[15] = 12920;
  free_ptrs[1] = my_malloc(9021);
  free_ptrs[8] = my_malloc(8380);
  free_ptrs[7] = my_malloc(8599);
  free_ptrs[14] = my_malloc(8942);
  ptrs[10] = my_malloc(12160); dc[10] = 12168;
  ptrs[19] = my_malloc(12467); dc[19] = 12480;
  ptrs[21] = my_malloc(12792); dc[21] = 12800;
  ptrs[30] = my_malloc(12774); dc[30] = 12784;
  ptrs[2] = my_malloc(12689); dc[2] = 12704;
  free_ptrs[5] = my_malloc(8760);
  ptrs[24] = my_malloc(12450); dc[24] = 12464;
  ptrs[16] = my_malloc(12159); dc[16] = 12168;
  free_ptrs[6] = my_malloc(8807);
  free_ptrs[0] = my_malloc(8749);
  free_ptrs[9] = my_malloc(8835);
  ptrs[3] = my_malloc(12813); dc[3] = 12824;
  ptrs[7] = my_malloc(12317); dc[7] = 12328;
  free_ptrs[3] = my_malloc(8254);
  free_ptrs[2] = my_malloc(8366);
  ptrs[17] = my_malloc(12611); dc[17] = 12624;
  free_ptrs[11] = my_malloc(8705);
  free_ptrs[15] = my_malloc(8993);
  ptrs[1] = my_malloc(12384); dc[1] = 12392;
  free_ptrs[12] = my_malloc(8720);
  ptrs[4] = my_malloc(12827); dc[4] = 12840;
  ptrs[9] = my_malloc(12260); dc[9] = 12272;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[4]);
  ptrs[28] = my_malloc(12315); dc[28] = 12328;
  ptrs[0] = my_malloc(12415); dc[0] = 12424;
  ptrs[27] = my_malloc(12529); dc[27] = 12544;
  my_free(free_ptrs[8]);
  ptrs[23] = my_malloc(12073); dc[23] = 12088;
  my_free(free_ptrs[1]);
  my_free(free_ptrs[7]);
  ptrs[31] = my_malloc(12177); dc[31] = 12192;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[14]);
  ptrs[26] = my_malloc(12681); dc[26] = 12696;
  my_free(free_ptrs[11]);
  ptrs[29] = my_malloc(12818); dc[29] = 12832;
  ptrs[12] = my_malloc(12868); dc[12] = 12880;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[5]);
  ptrs[11] = my_malloc(12636); dc[11] = 12648;
  ptrs[6] = my_malloc(12635); dc[6] = 12648;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[6]);
  ptrs[20] = my_malloc(12779); dc[20] = 12792;
  my_free(free_ptrs[9]);
  ptrs[25] = my_malloc(12744); dc[25] = 12752;
  ptrs[14] = my_malloc(12984); dc[14] = 12992;
  ptrs[8] = my_malloc(12888); dc[8] = 12896;
  my_free(free_ptrs[3]);
  ptrs[18] = my_malloc(12212); dc[18] = 12224;
  my_free(free_ptrs[15]);
  ptrs[22] = my_malloc(12029); dc[22] = 12040;

  double_check_memory(ptrs, dc, 32, 16, 541696);
  printf("Correct\n");
  return 0;
}
