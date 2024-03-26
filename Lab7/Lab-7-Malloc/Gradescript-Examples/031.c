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
  int *free_ptrs[14];
  int dc[28];

  free_ptrs[7] = my_malloc(8923);
  ptrs[5] = my_malloc(12784); dc[5] = 12792;
  ptrs[16] = my_malloc(12777); dc[16] = 12792;
  ptrs[15] = my_malloc(12219); dc[15] = 12232;
  free_ptrs[8] = my_malloc(8751);
  free_ptrs[6] = my_malloc(8262);
  free_ptrs[2] = my_malloc(8671);
  free_ptrs[9] = my_malloc(8567);
  free_ptrs[11] = my_malloc(8591);
  ptrs[26] = my_malloc(12043); dc[26] = 12056;
  free_ptrs[5] = my_malloc(8389);
  free_ptrs[12] = my_malloc(8399);
  ptrs[18] = my_malloc(12453); dc[18] = 12464;
  free_ptrs[10] = my_malloc(8466);
  free_ptrs[4] = my_malloc(8270);
  free_ptrs[3] = my_malloc(8498);
  free_ptrs[13] = my_malloc(8432);
  ptrs[20] = my_malloc(12300); dc[20] = 12312;
  free_ptrs[0] = my_malloc(9157);
  ptrs[27] = my_malloc(12878); dc[27] = 12888;
  ptrs[21] = my_malloc(12318); dc[21] = 12328;
  ptrs[8] = my_malloc(12737); dc[8] = 12752;
  ptrs[13] = my_malloc(12817); dc[13] = 12832;
  free_ptrs[1] = my_malloc(8578);
  my_free(free_ptrs[7]);
  ptrs[1] = my_malloc(12765); dc[1] = 12776;
  ptrs[23] = my_malloc(12751); dc[23] = 12760;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[5]);
  ptrs[22] = my_malloc(12407); dc[22] = 12416;
  ptrs[12] = my_malloc(12534); dc[12] = 12544;
  ptrs[19] = my_malloc(12960); dc[19] = 12968;
  ptrs[24] = my_malloc(12420); dc[24] = 12432;
  my_free(free_ptrs[3]);
  ptrs[25] = my_malloc(12893); dc[25] = 12904;
  ptrs[7] = my_malloc(12890); dc[7] = 12904;
  ptrs[9] = my_malloc(12105); dc[9] = 12120;
  ptrs[2] = my_malloc(12315); dc[2] = 12328;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[2]);
  ptrs[10] = my_malloc(12138); dc[10] = 12152;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[8]);
  ptrs[0] = my_malloc(12505); dc[0] = 12520;
  my_free(free_ptrs[11]);
  ptrs[11] = my_malloc(12954); dc[11] = 12968;
  my_free(free_ptrs[9]);
  ptrs[6] = my_malloc(12164); dc[6] = 12176;
  ptrs[17] = my_malloc(12529); dc[17] = 12544;
  my_free(free_ptrs[1]);
  ptrs[3] = my_malloc(12475); dc[3] = 12488;
  ptrs[4] = my_malloc(12988); dc[4] = 13000;
  ptrs[14] = my_malloc(12866); dc[14] = 12880;

  double_check_memory(ptrs, dc, 28, 14, 472432);
  printf("Correct\n");
  return 0;
}
