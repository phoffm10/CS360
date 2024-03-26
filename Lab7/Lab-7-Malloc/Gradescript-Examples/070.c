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
  int *free_ptrs[84];
  int dc[28];

  free_ptrs[0] = my_malloc(2645);  free_ptrs[1] = my_malloc(2429);  free_ptrs[2] = my_malloc(2608);
  free_ptrs[9] = my_malloc(2661);  free_ptrs[10] = my_malloc(2136);  free_ptrs[11] = my_malloc(2284);
  ptrs[7] = my_malloc(12316); dc[7] = 12328;
  free_ptrs[60] = my_malloc(2377);  free_ptrs[61] = my_malloc(2617);  free_ptrs[62] = my_malloc(2279);
  free_ptrs[3] = my_malloc(2212);  free_ptrs[4] = my_malloc(2604);  free_ptrs[5] = my_malloc(2561);
  free_ptrs[36] = my_malloc(2354);  free_ptrs[37] = my_malloc(2298);  free_ptrs[38] = my_malloc(2508);
  ptrs[19] = my_malloc(12234); dc[19] = 12248;
  ptrs[24] = my_malloc(12014); dc[24] = 12024;
  free_ptrs[78] = my_malloc(2602);  free_ptrs[79] = my_malloc(2402);  free_ptrs[80] = my_malloc(2455);
  ptrs[0] = my_malloc(12035); dc[0] = 12048;
  free_ptrs[33] = my_malloc(2147);  free_ptrs[34] = my_malloc(2157);  free_ptrs[35] = my_malloc(2338);
  free_ptrs[6] = my_malloc(2630);  free_ptrs[7] = my_malloc(2172);  free_ptrs[8] = my_malloc(2382);
  free_ptrs[15] = my_malloc(2658);  free_ptrs[16] = my_malloc(2304);  free_ptrs[17] = my_malloc(2446);
  free_ptrs[24] = my_malloc(2411);  free_ptrs[25] = my_malloc(2465);  free_ptrs[26] = my_malloc(2373);
  free_ptrs[66] = my_malloc(2518);  free_ptrs[67] = my_malloc(2395);  free_ptrs[68] = my_malloc(2289);
  free_ptrs[21] = my_malloc(2633);  free_ptrs[22] = my_malloc(2231);  free_ptrs[23] = my_malloc(2312);
  ptrs[18] = my_malloc(12535); dc[18] = 12544;
  free_ptrs[39] = my_malloc(2604);  free_ptrs[40] = my_malloc(2545);  free_ptrs[41] = my_malloc(2409);
  free_ptrs[75] = my_malloc(2318);  free_ptrs[76] = my_malloc(2440);  free_ptrs[77] = my_malloc(2072);
  free_ptrs[18] = my_malloc(2476);  free_ptrs[19] = my_malloc(2684);  free_ptrs[20] = my_malloc(2141);
  ptrs[27] = my_malloc(12136); dc[27] = 12144;
  ptrs[22] = my_malloc(12417); dc[22] = 12432;
  free_ptrs[45] = my_malloc(2102);  free_ptrs[46] = my_malloc(2689);  free_ptrs[47] = my_malloc(2148);
  ptrs[9] = my_malloc(12619); dc[9] = 12632;
  ptrs[13] = my_malloc(12595); dc[13] = 12608;
  free_ptrs[27] = my_malloc(2335);  free_ptrs[28] = my_malloc(2533);  free_ptrs[29] = my_malloc(2214);
  ptrs[1] = my_malloc(12287); dc[1] = 12296;
  free_ptrs[54] = my_malloc(2192);  free_ptrs[55] = my_malloc(2326);  free_ptrs[56] = my_malloc(2257);
  ptrs[3] = my_malloc(12181); dc[3] = 12192;
  free_ptrs[81] = my_malloc(2123);  free_ptrs[82] = my_malloc(2068);  free_ptrs[83] = my_malloc(2639);
  ptrs[23] = my_malloc(12345); dc[23] = 12360;
  free_ptrs[63] = my_malloc(2323);  free_ptrs[64] = my_malloc(2439);  free_ptrs[65] = my_malloc(2376);
  ptrs[10] = my_malloc(12732); dc[10] = 12744;
  free_ptrs[69] = my_malloc(2318);  free_ptrs[70] = my_malloc(2085);  free_ptrs[71] = my_malloc(2520);
  free_ptrs[12] = my_malloc(2418);  free_ptrs[13] = my_malloc(2476);  free_ptrs[14] = my_malloc(2599);
  free_ptrs[51] = my_malloc(2647);  free_ptrs[52] = my_malloc(2326);  free_ptrs[53] = my_malloc(2087);
  free_ptrs[48] = my_malloc(2436);  free_ptrs[49] = my_malloc(2401);  free_ptrs[50] = my_malloc(2661);
  free_ptrs[72] = my_malloc(2404);  free_ptrs[73] = my_malloc(2664);  free_ptrs[74] = my_malloc(2601);
  free_ptrs[30] = my_malloc(2416);  free_ptrs[31] = my_malloc(2601);  free_ptrs[32] = my_malloc(2188);
  ptrs[2] = my_malloc(12973); dc[2] = 12984;
  free_ptrs[57] = my_malloc(2582);  free_ptrs[58] = my_malloc(2502);  free_ptrs[59] = my_malloc(2471);
  ptrs[5] = my_malloc(12106); dc[5] = 12120;
  free_ptrs[42] = my_malloc(2400);  free_ptrs[43] = my_malloc(2061);  free_ptrs[44] = my_malloc(2684);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[83]);
  ptrs[14] = my_malloc(12860); dc[14] = 12872;
  my_free(free_ptrs[9]);
  ptrs[6] = my_malloc(12502); dc[6] = 12512;
  my_free(free_ptrs[74]);
  my_free(free_ptrs[51]);
  ptrs[12] = my_malloc(12816); dc[12] = 12824;
  my_free(free_ptrs[46]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[70]);
  ptrs[21] = my_malloc(12240); dc[21] = 12248;
  my_free(free_ptrs[72]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[50]);
  ptrs[4] = my_malloc(12494); dc[4] = 12504;
  my_free(free_ptrs[8]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[39]);
  ptrs[26] = my_malloc(12381); dc[26] = 12392;
  my_free(free_ptrs[3]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[22]);
  ptrs[17] = my_malloc(12011); dc[17] = 12024;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[62]);
  ptrs[25] = my_malloc(12695); dc[25] = 12704;
  my_free(free_ptrs[77]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[65]);
  ptrs[16] = my_malloc(12107); dc[16] = 12120;
  my_free(free_ptrs[47]);
  ptrs[8] = my_malloc(12795); dc[8] = 12808;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[7]);
  ptrs[11] = my_malloc(12412); dc[11] = 12424;
  my_free(free_ptrs[82]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[11]);
  ptrs[15] = my_malloc(12341); dc[15] = 12352;
  my_free(free_ptrs[60]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[24]);
  ptrs[20] = my_malloc(12702); dc[20] = 12712;
  my_free(free_ptrs[52]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[19]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 13, 577576);
  printf("Correct\n");
  return 0;
}
