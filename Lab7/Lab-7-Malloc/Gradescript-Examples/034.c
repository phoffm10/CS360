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
  int *ptrs[36];
  int *free_ptrs[18];
  int dc[36];

  free_ptrs[13] = my_malloc(8525);
  ptrs[20] = my_malloc(12106); dc[20] = 12120;
  ptrs[11] = my_malloc(12963); dc[11] = 12976;
  free_ptrs[14] = my_malloc(8556);
  free_ptrs[10] = my_malloc(8531);
  ptrs[18] = my_malloc(12779); dc[18] = 12792;
  ptrs[0] = my_malloc(12710); dc[0] = 12720;
  free_ptrs[8] = my_malloc(8869);
  free_ptrs[1] = my_malloc(8760);
  free_ptrs[6] = my_malloc(8299);
  ptrs[2] = my_malloc(12680); dc[2] = 12688;
  ptrs[10] = my_malloc(12551); dc[10] = 12560;
  ptrs[9] = my_malloc(12587); dc[9] = 12600;
  ptrs[16] = my_malloc(12406); dc[16] = 12416;
  ptrs[34] = my_malloc(12612); dc[34] = 12624;
  free_ptrs[3] = my_malloc(8198);
  ptrs[5] = my_malloc(12249); dc[5] = 12264;
  free_ptrs[0] = my_malloc(8433);
  ptrs[17] = my_malloc(12778); dc[17] = 12792;
  free_ptrs[15] = my_malloc(9158);
  free_ptrs[7] = my_malloc(8262);
  ptrs[30] = my_malloc(12181); dc[30] = 12192;
  ptrs[14] = my_malloc(12007); dc[14] = 12016;
  ptrs[19] = my_malloc(12394); dc[19] = 12408;
  free_ptrs[9] = my_malloc(8267);
  free_ptrs[16] = my_malloc(8984);
  ptrs[23] = my_malloc(12944); dc[23] = 12952;
  free_ptrs[17] = my_malloc(8772);
  ptrs[25] = my_malloc(12063); dc[25] = 12072;
  free_ptrs[12] = my_malloc(8412);
  ptrs[24] = my_malloc(12697); dc[24] = 12712;
  ptrs[21] = my_malloc(12791); dc[21] = 12800;
  free_ptrs[2] = my_malloc(8756);
  ptrs[1] = my_malloc(12407); dc[1] = 12416;
  free_ptrs[4] = my_malloc(8722);
  free_ptrs[5] = my_malloc(8283);
  free_ptrs[11] = my_malloc(8376);
  ptrs[27] = my_malloc(12280); dc[27] = 12288;
  my_free(free_ptrs[1]);
  ptrs[31] = my_malloc(12168); dc[31] = 12176;
  ptrs[29] = my_malloc(12985); dc[29] = 13000;
  my_free(free_ptrs[16]);
  ptrs[33] = my_malloc(12951); dc[33] = 12960;
  my_free(free_ptrs[2]);
  ptrs[22] = my_malloc(12780); dc[22] = 12792;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[11]);
  ptrs[3] = my_malloc(12548); dc[3] = 12560;
  ptrs[6] = my_malloc(12706); dc[6] = 12720;
  ptrs[12] = my_malloc(12275); dc[12] = 12288;
  ptrs[8] = my_malloc(12487); dc[8] = 12496;
  ptrs[15] = my_malloc(12644); dc[15] = 12656;
  ptrs[32] = my_malloc(12276); dc[32] = 12288;
  ptrs[4] = my_malloc(12962); dc[4] = 12976;
  my_free(free_ptrs[3]);
  ptrs[35] = my_malloc(12389); dc[35] = 12400;
  ptrs[13] = my_malloc(12546); dc[13] = 12560;
  my_free(free_ptrs[8]);
  my_free(free_ptrs[9]);
  ptrs[28] = my_malloc(12234); dc[28] = 12248;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[13]);
  ptrs[7] = my_malloc(12828); dc[7] = 12840;
  my_free(free_ptrs[12]);
  ptrs[26] = my_malloc(12296); dc[26] = 12304;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[14]);

  double_check_memory(ptrs, dc, 36, 18, 606040);
  printf("Correct\n");
  return 0;
}
