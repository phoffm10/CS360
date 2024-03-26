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
  int *ptrs[30];
  int *free_ptrs[90];
  int dc[30];

  free_ptrs[66] = my_malloc(2091);  free_ptrs[67] = my_malloc(2239);  free_ptrs[68] = my_malloc(2443);
  free_ptrs[12] = my_malloc(2185);  free_ptrs[13] = my_malloc(2160);  free_ptrs[14] = my_malloc(2545);
  free_ptrs[39] = my_malloc(2125);  free_ptrs[40] = my_malloc(2418);  free_ptrs[41] = my_malloc(2625);
  free_ptrs[3] = my_malloc(2527);  free_ptrs[4] = my_malloc(2210);  free_ptrs[5] = my_malloc(2499);
  free_ptrs[60] = my_malloc(2267);  free_ptrs[61] = my_malloc(2630);  free_ptrs[62] = my_malloc(2093);
  free_ptrs[81] = my_malloc(2219);  free_ptrs[82] = my_malloc(2454);  free_ptrs[83] = my_malloc(2630);
  free_ptrs[36] = my_malloc(2646);  free_ptrs[37] = my_malloc(2322);  free_ptrs[38] = my_malloc(2615);
  ptrs[24] = my_malloc(12828); dc[24] = 12840;
  ptrs[16] = my_malloc(12921); dc[16] = 12936;
  ptrs[29] = my_malloc(12519); dc[29] = 12528;
  free_ptrs[54] = my_malloc(2289);  free_ptrs[55] = my_malloc(2329);  free_ptrs[56] = my_malloc(2435);
  free_ptrs[18] = my_malloc(2489);  free_ptrs[19] = my_malloc(2660);  free_ptrs[20] = my_malloc(2206);
  free_ptrs[21] = my_malloc(2222);  free_ptrs[22] = my_malloc(2232);  free_ptrs[23] = my_malloc(2419);
  free_ptrs[72] = my_malloc(2655);  free_ptrs[73] = my_malloc(2268);  free_ptrs[74] = my_malloc(2366);
  ptrs[1] = my_malloc(12149); dc[1] = 12160;
  free_ptrs[42] = my_malloc(2050);  free_ptrs[43] = my_malloc(2426);  free_ptrs[44] = my_malloc(2615);
  free_ptrs[45] = my_malloc(2652);  free_ptrs[46] = my_malloc(2336);  free_ptrs[47] = my_malloc(2386);
  ptrs[11] = my_malloc(12506); dc[11] = 12520;
  ptrs[18] = my_malloc(12485); dc[18] = 12496;
  free_ptrs[63] = my_malloc(2428);  free_ptrs[64] = my_malloc(2075);  free_ptrs[65] = my_malloc(2610);
  ptrs[26] = my_malloc(12747); dc[26] = 12760;
  free_ptrs[75] = my_malloc(2542);  free_ptrs[76] = my_malloc(2247);  free_ptrs[77] = my_malloc(2106);
  ptrs[6] = my_malloc(12020); dc[6] = 12032;
  free_ptrs[0] = my_malloc(2318);  free_ptrs[1] = my_malloc(2239);  free_ptrs[2] = my_malloc(2565);
  free_ptrs[27] = my_malloc(2296);  free_ptrs[28] = my_malloc(2631);  free_ptrs[29] = my_malloc(2626);
  ptrs[9] = my_malloc(12897); dc[9] = 12912;
  ptrs[22] = my_malloc(12559); dc[22] = 12568;
  free_ptrs[87] = my_malloc(2471);  free_ptrs[88] = my_malloc(2659);  free_ptrs[89] = my_malloc(2349);
  free_ptrs[6] = my_malloc(2254);  free_ptrs[7] = my_malloc(2089);  free_ptrs[8] = my_malloc(2174);
  ptrs[5] = my_malloc(12264); dc[5] = 12272;
  free_ptrs[51] = my_malloc(2077);  free_ptrs[52] = my_malloc(2509);  free_ptrs[53] = my_malloc(2439);
  free_ptrs[33] = my_malloc(2526);  free_ptrs[34] = my_malloc(2072);  free_ptrs[35] = my_malloc(2390);
  free_ptrs[69] = my_malloc(2270);  free_ptrs[70] = my_malloc(2576);  free_ptrs[71] = my_malloc(2094);
  ptrs[2] = my_malloc(12083); dc[2] = 12096;
  free_ptrs[78] = my_malloc(2465);  free_ptrs[79] = my_malloc(2549);  free_ptrs[80] = my_malloc(2356);
  free_ptrs[57] = my_malloc(2691);  free_ptrs[58] = my_malloc(2677);  free_ptrs[59] = my_malloc(2697);
  free_ptrs[30] = my_malloc(2620);  free_ptrs[31] = my_malloc(2342);  free_ptrs[32] = my_malloc(2394);
  free_ptrs[15] = my_malloc(2192);  free_ptrs[16] = my_malloc(2155);  free_ptrs[17] = my_malloc(2433);
  free_ptrs[9] = my_malloc(2058);  free_ptrs[10] = my_malloc(2141);  free_ptrs[11] = my_malloc(2384);
  ptrs[25] = my_malloc(12725); dc[25] = 12736;
  free_ptrs[48] = my_malloc(2581);  free_ptrs[49] = my_malloc(2412);  free_ptrs[50] = my_malloc(2063);
  free_ptrs[24] = my_malloc(2569);  free_ptrs[25] = my_malloc(2310);  free_ptrs[26] = my_malloc(2527);
  free_ptrs[84] = my_malloc(2072);  free_ptrs[85] = my_malloc(2201);  free_ptrs[86] = my_malloc(2319);
  my_free(free_ptrs[65]);
  ptrs[4] = my_malloc(12036); dc[4] = 12048;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[86]);
  ptrs[20] = my_malloc(12332); dc[20] = 12344;
  my_free(free_ptrs[51]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[3]);
  ptrs[28] = my_malloc(12525); dc[28] = 12536;
  my_free(free_ptrs[48]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[78]);
  ptrs[13] = my_malloc(12865); dc[13] = 12880;
  my_free(free_ptrs[77]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[79]);
  ptrs[27] = my_malloc(12038); dc[27] = 12048;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[53]);
  ptrs[23] = my_malloc(12119); dc[23] = 12128;
  ptrs[21] = my_malloc(12838); dc[21] = 12848;
  my_free(free_ptrs[87]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[25]);
  ptrs[14] = my_malloc(12426); dc[14] = 12440;
  my_free(free_ptrs[19]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[5]);
  ptrs[17] = my_malloc(12657); dc[17] = 12672;
  my_free(free_ptrs[43]);
  my_free(free_ptrs[32]);
  ptrs[12] = my_malloc(12134); dc[12] = 12144;
  my_free(free_ptrs[29]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[12]);
  ptrs[19] = my_malloc(12672); dc[19] = 12680;
  my_free(free_ptrs[84]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[61]);
  ptrs[8] = my_malloc(12793); dc[8] = 12808;
  ptrs[3] = my_malloc(12475); dc[3] = 12488;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[73]);
  ptrs[7] = my_malloc(12010); dc[7] = 12024;
  my_free(free_ptrs[13]);
  ptrs[10] = my_malloc(12738); dc[10] = 12752;
  my_free(free_ptrs[71]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[1]);
  ptrs[15] = my_malloc(12339); dc[15] = 12352;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[31]);
  ptrs[0] = my_malloc(12857); dc[0] = 12872;
  my_free(free_ptrs[20]);
  my_free(free_ptrs[62]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 10, 620680);
  printf("Correct\n");
  return 0;
}
