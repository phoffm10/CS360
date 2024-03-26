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

  ptrs[19] = my_malloc(12179); dc[19] = 12192;
  free_ptrs[4] = my_malloc(8268);
  ptrs[25] = my_malloc(12232); dc[25] = 12240;
  ptrs[11] = my_malloc(12325); dc[11] = 12336;
  free_ptrs[10] = my_malloc(8726);
  ptrs[7] = my_malloc(12413); dc[7] = 12424;
  ptrs[13] = my_malloc(12628); dc[13] = 12640;
  ptrs[24] = my_malloc(12975); dc[24] = 12984;
  free_ptrs[8] = my_malloc(8696);
  free_ptrs[1] = my_malloc(9172);
  free_ptrs[2] = my_malloc(8583);
  free_ptrs[7] = my_malloc(8337);
  ptrs[15] = my_malloc(12718); dc[15] = 12728;
  ptrs[23] = my_malloc(12138); dc[23] = 12152;
  free_ptrs[15] = my_malloc(9027);
  free_ptrs[9] = my_malloc(8353);
  free_ptrs[11] = my_malloc(8700);
  ptrs[3] = my_malloc(12622); dc[3] = 12632;
  free_ptrs[0] = my_malloc(9066);
  free_ptrs[3] = my_malloc(8384);
  ptrs[16] = my_malloc(12684); dc[16] = 12696;
  ptrs[6] = my_malloc(12599); dc[6] = 12608;
  ptrs[0] = my_malloc(12916); dc[0] = 12928;
  free_ptrs[12] = my_malloc(8477);
  free_ptrs[13] = my_malloc(8741);
  free_ptrs[6] = my_malloc(8735);
  free_ptrs[5] = my_malloc(8567);
  free_ptrs[14] = my_malloc(8431);
  ptrs[4] = my_malloc(12935); dc[4] = 12944;
  ptrs[5] = my_malloc(12363); dc[5] = 12376;
  ptrs[1] = my_malloc(12696); dc[1] = 12704;
  ptrs[21] = my_malloc(12617); dc[21] = 12632;
  ptrs[17] = my_malloc(12028); dc[17] = 12040;
  my_free(free_ptrs[9]);
  my_free(free_ptrs[3]);
  ptrs[26] = my_malloc(12550); dc[26] = 12560;
  my_free(free_ptrs[13]);
  ptrs[30] = my_malloc(12571); dc[30] = 12584;
  my_free(free_ptrs[6]);
  ptrs[10] = my_malloc(12317); dc[10] = 12328;
  ptrs[22] = my_malloc(12154); dc[22] = 12168;
  my_free(free_ptrs[0]);
  ptrs[27] = my_malloc(12329); dc[27] = 12344;
  ptrs[14] = my_malloc(12149); dc[14] = 12160;
  ptrs[20] = my_malloc(12263); dc[20] = 12272;
  ptrs[2] = my_malloc(12694); dc[2] = 12704;
  ptrs[9] = my_malloc(12420); dc[9] = 12432;
  ptrs[31] = my_malloc(12506); dc[31] = 12520;
  ptrs[12] = my_malloc(12017); dc[12] = 12032;
  my_free(free_ptrs[2]);
  ptrs[29] = my_malloc(12882); dc[29] = 12896;
  ptrs[18] = my_malloc(12104); dc[18] = 12112;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[1]);
  ptrs[28] = my_malloc(12504); dc[28] = 12512;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[11]);
  ptrs[8] = my_malloc(12236); dc[8] = 12248;
  my_free(free_ptrs[14]);

  double_check_memory(ptrs, dc, 32, 16, 537568);
  printf("Correct\n");
  return 0;
}
