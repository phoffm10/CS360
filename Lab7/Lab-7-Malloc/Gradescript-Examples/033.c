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

  free_ptrs[11] = my_malloc(8722);
  ptrs[9] = my_malloc(12426); dc[9] = 12440;
  ptrs[26] = my_malloc(12428); dc[26] = 12440;
  ptrs[6] = my_malloc(12741); dc[6] = 12752;
  free_ptrs[13] = my_malloc(8803);
  ptrs[21] = my_malloc(12967); dc[21] = 12976;
  ptrs[20] = my_malloc(12621); dc[20] = 12632;
  free_ptrs[2] = my_malloc(8365);
  free_ptrs[1] = my_malloc(8218);
  ptrs[25] = my_malloc(12222); dc[25] = 12232;
  ptrs[17] = my_malloc(12362); dc[17] = 12376;
  ptrs[18] = my_malloc(12886); dc[18] = 12896;
  free_ptrs[15] = my_malloc(8889);
  ptrs[7] = my_malloc(12731); dc[7] = 12744;
  ptrs[16] = my_malloc(12530); dc[16] = 12544;
  free_ptrs[6] = my_malloc(9077);
  free_ptrs[3] = my_malloc(8806);
  free_ptrs[8] = my_malloc(9134);
  free_ptrs[10] = my_malloc(8812);
  free_ptrs[9] = my_malloc(8279);
  free_ptrs[7] = my_malloc(9087);
  ptrs[0] = my_malloc(12210); dc[0] = 12224;
  free_ptrs[0] = my_malloc(9152);
  free_ptrs[14] = my_malloc(8829);
  ptrs[19] = my_malloc(12033); dc[19] = 12048;
  ptrs[27] = my_malloc(12479); dc[27] = 12488;
  ptrs[28] = my_malloc(12046); dc[28] = 12056;
  ptrs[29] = my_malloc(12920); dc[29] = 12928;
  ptrs[31] = my_malloc(12488); dc[31] = 12496;
  ptrs[24] = my_malloc(12821); dc[24] = 12832;
  free_ptrs[5] = my_malloc(8989);
  ptrs[1] = my_malloc(12742); dc[1] = 12752;
  free_ptrs[12] = my_malloc(9099);
  free_ptrs[4] = my_malloc(8818);
  ptrs[15] = my_malloc(12836); dc[15] = 12848;
  ptrs[14] = my_malloc(12843); dc[14] = 12856;
  ptrs[8] = my_malloc(12138); dc[8] = 12152;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[4]);
  ptrs[12] = my_malloc(12127); dc[12] = 12136;
  ptrs[11] = my_malloc(12627); dc[11] = 12640;
  ptrs[13] = my_malloc(12754); dc[13] = 12768;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[14]);
  ptrs[2] = my_malloc(12676); dc[2] = 12688;
  my_free(free_ptrs[9]);
  ptrs[10] = my_malloc(12747); dc[10] = 12760;
  ptrs[3] = my_malloc(12740); dc[3] = 12752;
  ptrs[23] = my_malloc(12880); dc[23] = 12888;
  my_free(free_ptrs[2]);
  ptrs[4] = my_malloc(12853); dc[4] = 12864;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[6]);
  ptrs[5] = my_malloc(12545); dc[5] = 12560;
  ptrs[30] = my_malloc(12385); dc[30] = 12400;
  my_free(free_ptrs[1]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[10]);
  ptrs[22] = my_malloc(12656); dc[22] = 12664;
  my_free(free_ptrs[3]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[8]);

  double_check_memory(ptrs, dc, 32, 16, 544096);
  printf("Correct\n");
  return 0;
}
