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
  int *ptrs[29];
  int *free_ptrs[87];
  int dc[29];

  free_ptrs[15] = my_malloc(2490);  free_ptrs[16] = my_malloc(2525);  free_ptrs[17] = my_malloc(2620);
  ptrs[7] = my_malloc(12938); dc[7] = 12952;
  ptrs[3] = my_malloc(12490); dc[3] = 12504;
  free_ptrs[3] = my_malloc(2611);  free_ptrs[4] = my_malloc(2646);  free_ptrs[5] = my_malloc(2581);
  ptrs[0] = my_malloc(12236); dc[0] = 12248;
  free_ptrs[78] = my_malloc(2382);  free_ptrs[79] = my_malloc(2639);  free_ptrs[80] = my_malloc(2148);
  ptrs[28] = my_malloc(12872); dc[28] = 12880;
  free_ptrs[72] = my_malloc(2422);  free_ptrs[73] = my_malloc(2234);  free_ptrs[74] = my_malloc(2485);
  ptrs[4] = my_malloc(12904); dc[4] = 12912;
  free_ptrs[21] = my_malloc(2507);  free_ptrs[22] = my_malloc(2436);  free_ptrs[23] = my_malloc(2455);
  free_ptrs[57] = my_malloc(2105);  free_ptrs[58] = my_malloc(2479);  free_ptrs[59] = my_malloc(2104);
  ptrs[12] = my_malloc(12193); dc[12] = 12208;
  free_ptrs[42] = my_malloc(2226);  free_ptrs[43] = my_malloc(2396);  free_ptrs[44] = my_malloc(2653);
  ptrs[17] = my_malloc(12552); dc[17] = 12560;
  free_ptrs[33] = my_malloc(2258);  free_ptrs[34] = my_malloc(2274);  free_ptrs[35] = my_malloc(2402);
  ptrs[8] = my_malloc(12541); dc[8] = 12552;
  free_ptrs[45] = my_malloc(2691);  free_ptrs[46] = my_malloc(2634);  free_ptrs[47] = my_malloc(2172);
  free_ptrs[24] = my_malloc(2052);  free_ptrs[25] = my_malloc(2324);  free_ptrs[26] = my_malloc(2489);
  free_ptrs[48] = my_malloc(2385);  free_ptrs[49] = my_malloc(2156);  free_ptrs[50] = my_malloc(2553);
  free_ptrs[63] = my_malloc(2242);  free_ptrs[64] = my_malloc(2655);  free_ptrs[65] = my_malloc(2602);
  free_ptrs[69] = my_malloc(2237);  free_ptrs[70] = my_malloc(2443);  free_ptrs[71] = my_malloc(2455);
  ptrs[22] = my_malloc(12074); dc[22] = 12088;
  free_ptrs[75] = my_malloc(2137);  free_ptrs[76] = my_malloc(2319);  free_ptrs[77] = my_malloc(2243);
  free_ptrs[84] = my_malloc(2144);  free_ptrs[85] = my_malloc(2080);  free_ptrs[86] = my_malloc(2333);
  ptrs[5] = my_malloc(12887); dc[5] = 12896;
  ptrs[27] = my_malloc(12342); dc[27] = 12352;
  free_ptrs[54] = my_malloc(2478);  free_ptrs[55] = my_malloc(2329);  free_ptrs[56] = my_malloc(2260);
  ptrs[19] = my_malloc(12544); dc[19] = 12552;
  free_ptrs[6] = my_malloc(2243);  free_ptrs[7] = my_malloc(2095);  free_ptrs[8] = my_malloc(2475);
  ptrs[26] = my_malloc(12366); dc[26] = 12376;
  free_ptrs[9] = my_malloc(2177);  free_ptrs[10] = my_malloc(2588);  free_ptrs[11] = my_malloc(2070);
  ptrs[14] = my_malloc(12133); dc[14] = 12144;
  free_ptrs[27] = my_malloc(2051);  free_ptrs[28] = my_malloc(2074);  free_ptrs[29] = my_malloc(2481);
  free_ptrs[0] = my_malloc(2605);  free_ptrs[1] = my_malloc(2115);  free_ptrs[2] = my_malloc(2282);
  free_ptrs[12] = my_malloc(2469);  free_ptrs[13] = my_malloc(2315);  free_ptrs[14] = my_malloc(2289);
  free_ptrs[60] = my_malloc(2463);  free_ptrs[61] = my_malloc(2577);  free_ptrs[62] = my_malloc(2664);
  free_ptrs[81] = my_malloc(2319);  free_ptrs[82] = my_malloc(2667);  free_ptrs[83] = my_malloc(2118);
  free_ptrs[30] = my_malloc(2161);  free_ptrs[31] = my_malloc(2345);  free_ptrs[32] = my_malloc(2313);
  free_ptrs[36] = my_malloc(2423);  free_ptrs[37] = my_malloc(2493);  free_ptrs[38] = my_malloc(2292);
  free_ptrs[39] = my_malloc(2691);  free_ptrs[40] = my_malloc(2259);  free_ptrs[41] = my_malloc(2425);
  free_ptrs[18] = my_malloc(2681);  free_ptrs[19] = my_malloc(2275);  free_ptrs[20] = my_malloc(2087);
  ptrs[13] = my_malloc(12864); dc[13] = 12872;
  free_ptrs[51] = my_malloc(2631);  free_ptrs[52] = my_malloc(2065);  free_ptrs[53] = my_malloc(2307);
  free_ptrs[66] = my_malloc(2370);  free_ptrs[67] = my_malloc(2335);  free_ptrs[68] = my_malloc(2138);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[7]);
  ptrs[16] = my_malloc(12364); dc[16] = 12376;
  my_free(free_ptrs[21]);
  ptrs[15] = my_malloc(12410); dc[15] = 12424;
  my_free(free_ptrs[84]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[55]);
  ptrs[6] = my_malloc(12432); dc[6] = 12440;
  my_free(free_ptrs[73]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[25]);
  ptrs[11] = my_malloc(12257); dc[11] = 12272;
  my_free(free_ptrs[86]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[47]);
  ptrs[9] = my_malloc(12657); dc[9] = 12672;
  my_free(free_ptrs[70]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[48]);
  ptrs[2] = my_malloc(12206); dc[2] = 12216;
  my_free(free_ptrs[35]);
  my_free(free_ptrs[39]);
  ptrs[20] = my_malloc(12768); dc[20] = 12776;
  ptrs[10] = my_malloc(12509); dc[10] = 12520;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[3]);
  ptrs[24] = my_malloc(12567); dc[24] = 12576;
  ptrs[25] = my_malloc(12925); dc[25] = 12936;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[43]);
  ptrs[18] = my_malloc(12761); dc[18] = 12776;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[49]);
  ptrs[21] = my_malloc(12261); dc[21] = 12272;
  my_free(free_ptrs[56]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[19]);
  ptrs[23] = my_malloc(12438); dc[23] = 12448;
  my_free(free_ptrs[10]);
  ptrs[1] = my_malloc(12301); dc[1] = 12312;
  my_free(free_ptrs[85]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[62]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 14, 600680);
  printf("Correct\n");
  return 0;
}
