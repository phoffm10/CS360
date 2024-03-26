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

  free_ptrs[6] = my_malloc(8972);
  free_ptrs[2] = my_malloc(8523);
  free_ptrs[3] = my_malloc(8859);
  free_ptrs[9] = my_malloc(8975);
  free_ptrs[4] = my_malloc(8347);
  ptrs[4] = my_malloc(12909); dc[4] = 12920;
  free_ptrs[0] = my_malloc(8613);
  ptrs[2] = my_malloc(12059); dc[2] = 12072;
  free_ptrs[7] = my_malloc(8983);
  ptrs[11] = my_malloc(12334); dc[11] = 12344;
  ptrs[9] = my_malloc(12902); dc[9] = 12912;
  free_ptrs[8] = my_malloc(8663);
  ptrs[8] = my_malloc(12986); dc[8] = 13000;
  ptrs[7] = my_malloc(12999); dc[7] = 13008;
  ptrs[16] = my_malloc(12313); dc[16] = 12328;
  free_ptrs[5] = my_malloc(8713);
  ptrs[1] = my_malloc(12986); dc[1] = 13000;
  free_ptrs[1] = my_malloc(8959);
  ptrs[13] = my_malloc(12357); dc[13] = 12368;
  my_free(free_ptrs[5]);
  ptrs[0] = my_malloc(12473); dc[0] = 12488;
  ptrs[18] = my_malloc(12430); dc[18] = 12440;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[9]);
  ptrs[5] = my_malloc(12828); dc[5] = 12840;
  my_free(free_ptrs[4]);
  ptrs[19] = my_malloc(12613); dc[19] = 12624;
  ptrs[15] = my_malloc(12143); dc[15] = 12152;
  my_free(free_ptrs[8]);
  ptrs[17] = my_malloc(12277); dc[17] = 12288;
  my_free(free_ptrs[1]);
  ptrs[12] = my_malloc(12758); dc[12] = 12768;
  my_free(free_ptrs[3]);
  ptrs[3] = my_malloc(12695); dc[3] = 12704;
  ptrs[14] = my_malloc(12290); dc[14] = 12304;
  my_free(free_ptrs[7]);
  ptrs[10] = my_malloc(12730); dc[10] = 12744;
  ptrs[6] = my_malloc(12141); dc[6] = 12152;
  my_free(free_ptrs[0]);

  double_check_memory(ptrs, dc, 20, 10, 339176);
  printf("Correct\n");
  return 0;
}
