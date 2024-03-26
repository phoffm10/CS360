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
  int *ptrs[31];
  int *free_ptrs[93];
  int dc[31];

  ptrs[10] = my_malloc(12129); dc[10] = 12144;
  ptrs[25] = my_malloc(12044); dc[25] = 12056;
  free_ptrs[6] = my_malloc(2514);  free_ptrs[7] = my_malloc(2235);  free_ptrs[8] = my_malloc(2242);
  free_ptrs[69] = my_malloc(2203);  free_ptrs[70] = my_malloc(2269);  free_ptrs[71] = my_malloc(2077);
  free_ptrs[39] = my_malloc(2113);  free_ptrs[40] = my_malloc(2322);  free_ptrs[41] = my_malloc(2158);
  free_ptrs[42] = my_malloc(2353);  free_ptrs[43] = my_malloc(2256);  free_ptrs[44] = my_malloc(2647);
  ptrs[16] = my_malloc(12168); dc[16] = 12176;
  free_ptrs[90] = my_malloc(2370);  free_ptrs[91] = my_malloc(2685);  free_ptrs[92] = my_malloc(2085);
  free_ptrs[78] = my_malloc(2386);  free_ptrs[79] = my_malloc(2275);  free_ptrs[80] = my_malloc(2075);
  free_ptrs[21] = my_malloc(2247);  free_ptrs[22] = my_malloc(2602);  free_ptrs[23] = my_malloc(2100);
  ptrs[19] = my_malloc(12599); dc[19] = 12608;
  free_ptrs[87] = my_malloc(2110);  free_ptrs[88] = my_malloc(2322);  free_ptrs[89] = my_malloc(2460);
  ptrs[21] = my_malloc(12189); dc[21] = 12200;
  free_ptrs[3] = my_malloc(2507);  free_ptrs[4] = my_malloc(2098);  free_ptrs[5] = my_malloc(2694);
  ptrs[6] = my_malloc(12443); dc[6] = 12456;
  free_ptrs[36] = my_malloc(2197);  free_ptrs[37] = my_malloc(2372);  free_ptrs[38] = my_malloc(2550);
  ptrs[3] = my_malloc(12210); dc[3] = 12224;
  free_ptrs[24] = my_malloc(2461);  free_ptrs[25] = my_malloc(2230);  free_ptrs[26] = my_malloc(2208);
  free_ptrs[51] = my_malloc(2102);  free_ptrs[52] = my_malloc(2598);  free_ptrs[53] = my_malloc(2057);
  free_ptrs[9] = my_malloc(2324);  free_ptrs[10] = my_malloc(2609);  free_ptrs[11] = my_malloc(2641);
  free_ptrs[66] = my_malloc(2124);  free_ptrs[67] = my_malloc(2688);  free_ptrs[68] = my_malloc(2353);
  ptrs[1] = my_malloc(12172); dc[1] = 12184;
  free_ptrs[30] = my_malloc(2085);  free_ptrs[31] = my_malloc(2605);  free_ptrs[32] = my_malloc(2100);
  ptrs[30] = my_malloc(12127); dc[30] = 12136;
  free_ptrs[18] = my_malloc(2087);  free_ptrs[19] = my_malloc(2081);  free_ptrs[20] = my_malloc(2626);
  ptrs[14] = my_malloc(12449); dc[14] = 12464;
  free_ptrs[60] = my_malloc(2667);  free_ptrs[61] = my_malloc(2458);  free_ptrs[62] = my_malloc(2053);
  ptrs[24] = my_malloc(12075); dc[24] = 12088;
  free_ptrs[75] = my_malloc(2464);  free_ptrs[76] = my_malloc(2597);  free_ptrs[77] = my_malloc(2318);
  free_ptrs[12] = my_malloc(2317);  free_ptrs[13] = my_malloc(2300);  free_ptrs[14] = my_malloc(2548);
  free_ptrs[48] = my_malloc(2135);  free_ptrs[49] = my_malloc(2404);  free_ptrs[50] = my_malloc(2066);
  free_ptrs[0] = my_malloc(2580);  free_ptrs[1] = my_malloc(2632);  free_ptrs[2] = my_malloc(2431);
  free_ptrs[72] = my_malloc(2369);  free_ptrs[73] = my_malloc(2179);  free_ptrs[74] = my_malloc(2569);
  ptrs[18] = my_malloc(12052); dc[18] = 12064;
  free_ptrs[57] = my_malloc(2146);  free_ptrs[58] = my_malloc(2570);  free_ptrs[59] = my_malloc(2119);
  free_ptrs[63] = my_malloc(2654);  free_ptrs[64] = my_malloc(2399);  free_ptrs[65] = my_malloc(2084);
  free_ptrs[45] = my_malloc(2359);  free_ptrs[46] = my_malloc(2497);  free_ptrs[47] = my_malloc(2519);
  free_ptrs[27] = my_malloc(2218);  free_ptrs[28] = my_malloc(2097);  free_ptrs[29] = my_malloc(2244);
  ptrs[2] = my_malloc(12722); dc[2] = 12736;
  free_ptrs[33] = my_malloc(2375);  free_ptrs[34] = my_malloc(2447);  free_ptrs[35] = my_malloc(2352);
  free_ptrs[84] = my_malloc(2140);  free_ptrs[85] = my_malloc(2590);  free_ptrs[86] = my_malloc(2479);
  ptrs[7] = my_malloc(12169); dc[7] = 12184;
  ptrs[13] = my_malloc(12928); dc[13] = 12936;
  ptrs[11] = my_malloc(12481); dc[11] = 12496;
  ptrs[26] = my_malloc(12010); dc[26] = 12024;
  free_ptrs[54] = my_malloc(2684);  free_ptrs[55] = my_malloc(2500);  free_ptrs[56] = my_malloc(2165);
  free_ptrs[81] = my_malloc(2455);  free_ptrs[82] = my_malloc(2193);  free_ptrs[83] = my_malloc(2126);
  free_ptrs[15] = my_malloc(2266);  free_ptrs[16] = my_malloc(2198);  free_ptrs[17] = my_malloc(2350);
  ptrs[5] = my_malloc(12855); dc[5] = 12864;
  my_free(free_ptrs[71]);
  ptrs[0] = my_malloc(12504); dc[0] = 12512;
  my_free(free_ptrs[54]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[45]);
  ptrs[23] = my_malloc(12990); dc[23] = 13000;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[34]);
  ptrs[15] = my_malloc(12722); dc[15] = 12736;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[86]);
  ptrs[27] = my_malloc(12437); dc[27] = 12448;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[61]);
  ptrs[17] = my_malloc(12824); dc[17] = 12832;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[92]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[87]);
  ptrs[8] = my_malloc(12744); dc[8] = 12752;
  my_free(free_ptrs[28]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[6]);
  ptrs[4] = my_malloc(12171); dc[4] = 12184;
  my_free(free_ptrs[88]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[48]);
  ptrs[12] = my_malloc(12189); dc[12] = 12200;
  my_free(free_ptrs[66]);
  ptrs[20] = my_malloc(12011); dc[20] = 12024;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[10]);
  ptrs[28] = my_malloc(12796); dc[28] = 12808;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[25]);
  ptrs[9] = my_malloc(12576); dc[9] = 12584;
  my_free(free_ptrs[80]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[7]);
  ptrs[22] = my_malloc(12310); dc[22] = 12320;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[31]);
  ptrs[29] = my_malloc(12038); dc[29] = 12048;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[5]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 13, 638440);
  printf("Correct\n");
  return 0;
}
