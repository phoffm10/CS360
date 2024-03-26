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

  ptrs[17] = my_malloc(12945); dc[17] = 12960;
  ptrs[28] = my_malloc(12505); dc[28] = 12520;
  free_ptrs[14] = my_malloc(8340);
  free_ptrs[8] = my_malloc(9170);
  ptrs[23] = my_malloc(12815); dc[23] = 12824;
  free_ptrs[10] = my_malloc(8348);
  ptrs[16] = my_malloc(12653); dc[16] = 12664;
  free_ptrs[12] = my_malloc(8990);
  free_ptrs[7] = my_malloc(8701);
  ptrs[26] = my_malloc(12559); dc[26] = 12568;
  free_ptrs[6] = my_malloc(9149);
  ptrs[2] = my_malloc(12319); dc[2] = 12328;
  free_ptrs[11] = my_malloc(8727);
  ptrs[18] = my_malloc(12346); dc[18] = 12360;
  ptrs[22] = my_malloc(12531); dc[22] = 12544;
  ptrs[20] = my_malloc(12785); dc[20] = 12800;
  ptrs[10] = my_malloc(12942); dc[10] = 12952;
  free_ptrs[13] = my_malloc(8980);
  ptrs[11] = my_malloc(12290); dc[11] = 12304;
  free_ptrs[3] = my_malloc(8324);
  ptrs[15] = my_malloc(12027); dc[15] = 12040;
  free_ptrs[2] = my_malloc(8796);
  free_ptrs[9] = my_malloc(8409);
  free_ptrs[0] = my_malloc(9187);
  free_ptrs[15] = my_malloc(8207);
  ptrs[29] = my_malloc(12504); dc[29] = 12512;
  free_ptrs[5] = my_malloc(9182);
  ptrs[30] = my_malloc(12236); dc[30] = 12248;
  ptrs[27] = my_malloc(12679); dc[27] = 12688;
  ptrs[31] = my_malloc(12807); dc[31] = 12816;
  ptrs[5] = my_malloc(12488); dc[5] = 12496;
  ptrs[7] = my_malloc(12987); dc[7] = 13000;
  free_ptrs[4] = my_malloc(8206);
  free_ptrs[1] = my_malloc(8715);
  ptrs[8] = my_malloc(12438); dc[8] = 12448;
  ptrs[1] = my_malloc(12430); dc[1] = 12440;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[6]);
  ptrs[6] = my_malloc(12129); dc[6] = 12144;
  ptrs[19] = my_malloc(12321); dc[19] = 12336;
  ptrs[13] = my_malloc(12961); dc[13] = 12976;
  ptrs[24] = my_malloc(12296); dc[24] = 12304;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[1]);
  ptrs[0] = my_malloc(12357); dc[0] = 12368;
  ptrs[12] = my_malloc(12330); dc[12] = 12344;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[0]);
  ptrs[21] = my_malloc(12142); dc[21] = 12152;
  ptrs[14] = my_malloc(12678); dc[14] = 12688;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[14]);
  ptrs[3] = my_malloc(12283); dc[3] = 12296;
  ptrs[9] = my_malloc(12266); dc[9] = 12280;
  my_free(free_ptrs[5]);
  my_free(free_ptrs[12]);
  ptrs[4] = my_malloc(12097); dc[4] = 12112;
  ptrs[25] = my_malloc(12734); dc[25] = 12744;

  double_check_memory(ptrs, dc, 32, 16, 539872);
  printf("Correct\n");
  return 0;
}
