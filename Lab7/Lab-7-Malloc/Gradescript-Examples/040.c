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
  int *ptrs[20];
  int *free_ptrs[10];
  int dc[20];

  free_ptrs[4] = my_malloc(8864);
  ptrs[5] = my_malloc(12533); dc[5] = 12544;
  ptrs[4] = my_malloc(12665); dc[4] = 12680;
  free_ptrs[6] = my_malloc(8388);
  ptrs[7] = my_malloc(12743); dc[7] = 12752;
  free_ptrs[0] = my_malloc(8449);
  free_ptrs[8] = my_malloc(8980);
  free_ptrs[9] = my_malloc(8478);
  free_ptrs[5] = my_malloc(8527);
  ptrs[0] = my_malloc(12974); dc[0] = 12984;
  ptrs[8] = my_malloc(12686); dc[8] = 12696;
  free_ptrs[2] = my_malloc(8588);
  ptrs[9] = my_malloc(12062); dc[9] = 12072;
  ptrs[1] = my_malloc(12650); dc[1] = 12664;
  free_ptrs[3] = my_malloc(8854);
  ptrs[16] = my_malloc(12190); dc[16] = 12200;
  ptrs[10] = my_malloc(12535); dc[10] = 12544;
  free_ptrs[1] = my_malloc(8582);
  free_ptrs[7] = my_malloc(8505);
  ptrs[18] = my_malloc(12970); dc[18] = 12984;
  ptrs[6] = my_malloc(12105); dc[6] = 12120;
  ptrs[11] = my_malloc(12671); dc[11] = 12680;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[4]);
  ptrs[19] = my_malloc(12973); dc[19] = 12984;
  my_free(free_ptrs[8]);
  ptrs[13] = my_malloc(12150); dc[13] = 12160;
  my_free(free_ptrs[1]);
  ptrs[2] = my_malloc(12064); dc[2] = 12072;
  my_free(free_ptrs[5]);
  ptrs[14] = my_malloc(12103); dc[14] = 12112;
  ptrs[3] = my_malloc(12152); dc[3] = 12160;
  ptrs[12] = my_malloc(12555); dc[12] = 12568;
  my_free(free_ptrs[9]);
  ptrs[17] = my_malloc(12694); dc[17] = 12704;
  ptrs[15] = my_malloc(12600); dc[15] = 12608;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[3]);

  double_check_memory(ptrs, dc, 20, 10, 336616);
  printf("Correct\n");
  return 0;
}
