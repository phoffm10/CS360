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

  free_ptrs[72] = my_malloc(2424);  free_ptrs[73] = my_malloc(2170);  free_ptrs[74] = my_malloc(2244);
  free_ptrs[36] = my_malloc(2616);  free_ptrs[37] = my_malloc(2627);  free_ptrs[38] = my_malloc(2429);
  free_ptrs[18] = my_malloc(2624);  free_ptrs[19] = my_malloc(2496);  free_ptrs[20] = my_malloc(2525);
  free_ptrs[60] = my_malloc(2288);  free_ptrs[61] = my_malloc(2423);  free_ptrs[62] = my_malloc(2306);
  ptrs[4] = my_malloc(12412); dc[4] = 12424;
  free_ptrs[30] = my_malloc(2242);  free_ptrs[31] = my_malloc(2126);  free_ptrs[32] = my_malloc(2181);
  free_ptrs[90] = my_malloc(2455);  free_ptrs[91] = my_malloc(2236);  free_ptrs[92] = my_malloc(2444);
  free_ptrs[48] = my_malloc(2134);  free_ptrs[49] = my_malloc(2201);  free_ptrs[50] = my_malloc(2415);
  ptrs[7] = my_malloc(12986); dc[7] = 13000;
  ptrs[27] = my_malloc(12934); dc[27] = 12944;
  free_ptrs[3] = my_malloc(2636);  free_ptrs[4] = my_malloc(2539);  free_ptrs[5] = my_malloc(2495);
  free_ptrs[54] = my_malloc(2575);  free_ptrs[55] = my_malloc(2299);  free_ptrs[56] = my_malloc(2466);
  free_ptrs[27] = my_malloc(2575);  free_ptrs[28] = my_malloc(2292);  free_ptrs[29] = my_malloc(2449);
  free_ptrs[9] = my_malloc(2303);  free_ptrs[10] = my_malloc(2238);  free_ptrs[11] = my_malloc(2346);
  free_ptrs[12] = my_malloc(2108);  free_ptrs[13] = my_malloc(2527);  free_ptrs[14] = my_malloc(2277);
  free_ptrs[84] = my_malloc(2367);  free_ptrs[85] = my_malloc(2539);  free_ptrs[86] = my_malloc(2566);
  ptrs[0] = my_malloc(12977); dc[0] = 12992;
  free_ptrs[42] = my_malloc(2488);  free_ptrs[43] = my_malloc(2337);  free_ptrs[44] = my_malloc(2514);
  free_ptrs[63] = my_malloc(2163);  free_ptrs[64] = my_malloc(2228);  free_ptrs[65] = my_malloc(2263);
  free_ptrs[45] = my_malloc(2512);  free_ptrs[46] = my_malloc(2622);  free_ptrs[47] = my_malloc(2508);
  ptrs[15] = my_malloc(12459); dc[15] = 12472;
  ptrs[30] = my_malloc(12624); dc[30] = 12632;
  free_ptrs[66] = my_malloc(2607);  free_ptrs[67] = my_malloc(2455);  free_ptrs[68] = my_malloc(2350);
  free_ptrs[21] = my_malloc(2340);  free_ptrs[22] = my_malloc(2593);  free_ptrs[23] = my_malloc(2301);
  ptrs[26] = my_malloc(12259); dc[26] = 12272;
  free_ptrs[51] = my_malloc(2509);  free_ptrs[52] = my_malloc(2423);  free_ptrs[53] = my_malloc(2096);
  ptrs[21] = my_malloc(12942); dc[21] = 12952;
  free_ptrs[87] = my_malloc(2179);  free_ptrs[88] = my_malloc(2145);  free_ptrs[89] = my_malloc(2531);
  free_ptrs[24] = my_malloc(2206);  free_ptrs[25] = my_malloc(2103);  free_ptrs[26] = my_malloc(2591);
  free_ptrs[57] = my_malloc(2333);  free_ptrs[58] = my_malloc(2329);  free_ptrs[59] = my_malloc(2380);
  free_ptrs[81] = my_malloc(2466);  free_ptrs[82] = my_malloc(2386);  free_ptrs[83] = my_malloc(2483);
  ptrs[6] = my_malloc(12644); dc[6] = 12656;
  free_ptrs[15] = my_malloc(2395);  free_ptrs[16] = my_malloc(2503);  free_ptrs[17] = my_malloc(2181);
  ptrs[1] = my_malloc(12333); dc[1] = 12344;
  ptrs[11] = my_malloc(12066); dc[11] = 12080;
  free_ptrs[69] = my_malloc(2184);  free_ptrs[70] = my_malloc(2194);  free_ptrs[71] = my_malloc(2480);
  ptrs[17] = my_malloc(12345); dc[17] = 12360;
  free_ptrs[75] = my_malloc(2685);  free_ptrs[76] = my_malloc(2130);  free_ptrs[77] = my_malloc(2363);
  free_ptrs[6] = my_malloc(2241);  free_ptrs[7] = my_malloc(2658);  free_ptrs[8] = my_malloc(2635);
  free_ptrs[78] = my_malloc(2541);  free_ptrs[79] = my_malloc(2358);  free_ptrs[80] = my_malloc(2384);
  ptrs[8] = my_malloc(12697); dc[8] = 12712;
  ptrs[24] = my_malloc(12860); dc[24] = 12872;
  ptrs[20] = my_malloc(12060); dc[20] = 12072;
  free_ptrs[0] = my_malloc(2365);  free_ptrs[1] = my_malloc(2461);  free_ptrs[2] = my_malloc(2220);
  free_ptrs[39] = my_malloc(2584);  free_ptrs[40] = my_malloc(2153);  free_ptrs[41] = my_malloc(2097);
  ptrs[14] = my_malloc(12906); dc[14] = 12920;
  ptrs[2] = my_malloc(12603); dc[2] = 12616;
  ptrs[12] = my_malloc(12278); dc[12] = 12288;
  free_ptrs[33] = my_malloc(2544);  free_ptrs[34] = my_malloc(2208);  free_ptrs[35] = my_malloc(2567);
  ptrs[19] = my_malloc(12088); dc[19] = 12096;
  my_free(free_ptrs[72]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[15]);
  ptrs[10] = my_malloc(12514); dc[10] = 12528;
  my_free(free_ptrs[59]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[65]);
  ptrs[18] = my_malloc(12669); dc[18] = 12680;
  my_free(free_ptrs[67]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[17]);
  ptrs[22] = my_malloc(12919); dc[22] = 12928;
  my_free(free_ptrs[6]);
  ptrs[9] = my_malloc(12977); dc[9] = 12992;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[34]);
  ptrs[16] = my_malloc(12601); dc[16] = 12616;
  my_free(free_ptrs[47]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[92]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[27]);
  ptrs[13] = my_malloc(12721); dc[13] = 12736;
  my_free(free_ptrs[31]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[7]);
  ptrs[28] = my_malloc(12989); dc[28] = 13000;
  my_free(free_ptrs[42]);
  my_free(free_ptrs[66]);
  ptrs[25] = my_malloc(12685); dc[25] = 12696;
  my_free(free_ptrs[88]);
  my_free(free_ptrs[14]);
  ptrs[3] = my_malloc(12651); dc[3] = 12664;
  my_free(free_ptrs[33]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[39]);
  ptrs[29] = my_malloc(12967); dc[29] = 12976;
  my_free(free_ptrs[44]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[51]);
  ptrs[5] = my_malloc(12936); dc[5] = 12944;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[13]);
  ptrs[23] = my_malloc(12735); dc[23] = 12744;
  my_free(free_ptrs[80]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[75]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 12, 646160);
  printf("Correct\n");
  return 0;
}
