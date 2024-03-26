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

  free_ptrs[1] = my_malloc(8362);
  free_ptrs[12] = my_malloc(8854);
  ptrs[10] = my_malloc(12121); dc[10] = 12136;
  ptrs[0] = my_malloc(12768); dc[0] = 12776;
  ptrs[8] = my_malloc(12937); dc[8] = 12952;
  free_ptrs[2] = my_malloc(9086);
  free_ptrs[6] = my_malloc(8237);
  ptrs[24] = my_malloc(12851); dc[24] = 12864;
  free_ptrs[11] = my_malloc(8754);
  free_ptrs[7] = my_malloc(8968);
  ptrs[3] = my_malloc(12078); dc[3] = 12088;
  ptrs[2] = my_malloc(12050); dc[2] = 12064;
  free_ptrs[9] = my_malloc(8837);
  free_ptrs[3] = my_malloc(8440);
  ptrs[33] = my_malloc(12833); dc[33] = 12848;
  free_ptrs[17] = my_malloc(8998);
  free_ptrs[4] = my_malloc(8764);
  ptrs[34] = my_malloc(12206); dc[34] = 12216;
  ptrs[22] = my_malloc(12278); dc[22] = 12288;
  ptrs[13] = my_malloc(12420); dc[13] = 12432;
  ptrs[28] = my_malloc(12044); dc[28] = 12056;
  ptrs[25] = my_malloc(12073); dc[25] = 12088;
  free_ptrs[16] = my_malloc(8978);
  free_ptrs[14] = my_malloc(8878);
  ptrs[16] = my_malloc(12560); dc[16] = 12568;
  free_ptrs[0] = my_malloc(8251);
  free_ptrs[10] = my_malloc(8565);
  ptrs[4] = my_malloc(12692); dc[4] = 12704;
  free_ptrs[13] = my_malloc(9047);
  free_ptrs[5] = my_malloc(8653);
  ptrs[15] = my_malloc(12526); dc[15] = 12536;
  ptrs[14] = my_malloc(12961); dc[14] = 12976;
  ptrs[26] = my_malloc(12418); dc[26] = 12432;
  ptrs[1] = my_malloc(12009); dc[1] = 12024;
  ptrs[11] = my_malloc(12661); dc[11] = 12672;
  free_ptrs[8] = my_malloc(8639);
  free_ptrs[15] = my_malloc(8776);
  ptrs[32] = my_malloc(12190); dc[32] = 12200;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[8]);
  ptrs[20] = my_malloc(12100); dc[20] = 12112;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[11]);
  ptrs[17] = my_malloc(12444); dc[17] = 12456;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[15]);
  ptrs[27] = my_malloc(12130); dc[27] = 12144;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[14]);
  ptrs[18] = my_malloc(12645); dc[18] = 12656;
  my_free(free_ptrs[13]);
  ptrs[12] = my_malloc(12813); dc[12] = 12824;
  my_free(free_ptrs[5]);
  ptrs[31] = my_malloc(12186); dc[31] = 12200;
  my_free(free_ptrs[4]);
  ptrs[21] = my_malloc(12441); dc[21] = 12456;
  ptrs[23] = my_malloc(12202); dc[23] = 12216;
  ptrs[5] = my_malloc(12419); dc[5] = 12432;
  my_free(free_ptrs[3]);
  ptrs[6] = my_malloc(12212); dc[6] = 12224;
  ptrs[29] = my_malloc(12299); dc[29] = 12312;
  ptrs[9] = my_malloc(12581); dc[9] = 12592;
  ptrs[7] = my_malloc(12158); dc[7] = 12168;
  ptrs[35] = my_malloc(12959); dc[35] = 12968;
  my_free(free_ptrs[2]);
  ptrs[19] = my_malloc(12540); dc[19] = 12552;
  my_free(free_ptrs[17]);
  my_free(free_ptrs[12]);
  ptrs[30] = my_malloc(12367); dc[30] = 12376;

  double_check_memory(ptrs, dc, 36, 18, 604888);
  printf("Correct\n");
  return 0;
}
