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

  ptrs[3] = my_malloc(12887); dc[3] = 12896;
  ptrs[9] = my_malloc(12741); dc[9] = 12752;
  free_ptrs[5] = my_malloc(8820);
  ptrs[8] = my_malloc(12285); dc[8] = 12296;
  ptrs[21] = my_malloc(12266); dc[21] = 12280;
  free_ptrs[6] = my_malloc(8310);
  ptrs[14] = my_malloc(12126); dc[14] = 12136;
  free_ptrs[15] = my_malloc(8195);
  free_ptrs[13] = my_malloc(8766);
  free_ptrs[2] = my_malloc(8654);
  free_ptrs[0] = my_malloc(8456);
  ptrs[5] = my_malloc(12124); dc[5] = 12136;
  ptrs[4] = my_malloc(12800); dc[4] = 12808;
  free_ptrs[10] = my_malloc(8309);
  free_ptrs[3] = my_malloc(9074);
  ptrs[26] = my_malloc(12287); dc[26] = 12296;
  ptrs[16] = my_malloc(12437); dc[16] = 12448;
  free_ptrs[14] = my_malloc(9047);
  ptrs[13] = my_malloc(12565); dc[13] = 12576;
  free_ptrs[9] = my_malloc(8803);
  free_ptrs[17] = my_malloc(8980);
  free_ptrs[4] = my_malloc(8200);
  free_ptrs[16] = my_malloc(8375);
  ptrs[6] = my_malloc(12176); dc[6] = 12184;
  ptrs[1] = my_malloc(12673); dc[1] = 12688;
  ptrs[35] = my_malloc(12176); dc[35] = 12184;
  ptrs[30] = my_malloc(12164); dc[30] = 12176;
  ptrs[20] = my_malloc(12936); dc[20] = 12944;
  free_ptrs[7] = my_malloc(8218);
  ptrs[23] = my_malloc(12267); dc[23] = 12280;
  free_ptrs[12] = my_malloc(8891);
  free_ptrs[8] = my_malloc(9155);
  ptrs[32] = my_malloc(12155); dc[32] = 12168;
  free_ptrs[1] = my_malloc(8425);
  free_ptrs[11] = my_malloc(8525);
  ptrs[10] = my_malloc(12926); dc[10] = 12936;
  ptrs[25] = my_malloc(12913); dc[25] = 12928;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[1]);
  ptrs[15] = my_malloc(12335); dc[15] = 12344;
  my_free(free_ptrs[0]);
  ptrs[33] = my_malloc(12642); dc[33] = 12656;
  my_free(free_ptrs[13]);
  ptrs[7] = my_malloc(12902); dc[7] = 12912;
  ptrs[28] = my_malloc(12585); dc[28] = 12600;
  ptrs[18] = my_malloc(12537); dc[18] = 12552;
  ptrs[2] = my_malloc(12055); dc[2] = 12064;
  ptrs[27] = my_malloc(12930); dc[27] = 12944;
  ptrs[17] = my_malloc(12861); dc[17] = 12872;
  ptrs[34] = my_malloc(12266); dc[34] = 12280;
  my_free(free_ptrs[12]);
  ptrs[0] = my_malloc(12621); dc[0] = 12632;
  ptrs[12] = my_malloc(12962); dc[12] = 12976;
  my_free(free_ptrs[7]);
  ptrs[19] = my_malloc(12252); dc[19] = 12264;
  my_free(free_ptrs[15]);
  ptrs[11] = my_malloc(12998); dc[11] = 13008;
  ptrs[31] = my_malloc(12515); dc[31] = 12528;
  my_free(free_ptrs[8]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[4]);
  ptrs[22] = my_malloc(12403); dc[22] = 12416;
  my_free(free_ptrs[10]);
  ptrs[29] = my_malloc(12715); dc[29] = 12728;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[2]);
  ptrs[24] = my_malloc(12728); dc[24] = 12736;

  double_check_memory(ptrs, dc, 36, 18, 607032);
  printf("Correct\n");
  return 0;
}
