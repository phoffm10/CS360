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

  ptrs[18] = my_malloc(12868); dc[18] = 12880;
  free_ptrs[36] = my_malloc(2375);  free_ptrs[37] = my_malloc(2553);  free_ptrs[38] = my_malloc(2360);
  ptrs[6] = my_malloc(12467); dc[6] = 12480;
  free_ptrs[27] = my_malloc(2391);  free_ptrs[28] = my_malloc(2272);  free_ptrs[29] = my_malloc(2429);
  free_ptrs[15] = my_malloc(2547);  free_ptrs[16] = my_malloc(2676);  free_ptrs[17] = my_malloc(2128);
  free_ptrs[21] = my_malloc(2551);  free_ptrs[22] = my_malloc(2137);  free_ptrs[23] = my_malloc(2428);
  free_ptrs[39] = my_malloc(2336);  free_ptrs[40] = my_malloc(2599);  free_ptrs[41] = my_malloc(2144);
  free_ptrs[63] = my_malloc(2163);  free_ptrs[64] = my_malloc(2566);  free_ptrs[65] = my_malloc(2131);
  free_ptrs[33] = my_malloc(2205);  free_ptrs[34] = my_malloc(2553);  free_ptrs[35] = my_malloc(2629);
  ptrs[17] = my_malloc(12136); dc[17] = 12144;
  free_ptrs[3] = my_malloc(2596);  free_ptrs[4] = my_malloc(2081);  free_ptrs[5] = my_malloc(2056);
  free_ptrs[78] = my_malloc(2150);  free_ptrs[79] = my_malloc(2392);  free_ptrs[80] = my_malloc(2275);
  ptrs[3] = my_malloc(12034); dc[3] = 12048;
  ptrs[8] = my_malloc(12840); dc[8] = 12848;
  free_ptrs[9] = my_malloc(2553);  free_ptrs[10] = my_malloc(2162);  free_ptrs[11] = my_malloc(2105);
  free_ptrs[87] = my_malloc(2368);  free_ptrs[88] = my_malloc(2590);  free_ptrs[89] = my_malloc(2526);
  ptrs[12] = my_malloc(12045); dc[12] = 12056;
  free_ptrs[84] = my_malloc(2253);  free_ptrs[85] = my_malloc(2626);  free_ptrs[86] = my_malloc(2372);
  ptrs[29] = my_malloc(12590); dc[29] = 12600;
  free_ptrs[75] = my_malloc(2551);  free_ptrs[76] = my_malloc(2676);  free_ptrs[77] = my_malloc(2571);
  free_ptrs[69] = my_malloc(2301);  free_ptrs[70] = my_malloc(2593);  free_ptrs[71] = my_malloc(2171);
  ptrs[4] = my_malloc(12795); dc[4] = 12808;
  free_ptrs[30] = my_malloc(2581);  free_ptrs[31] = my_malloc(2185);  free_ptrs[32] = my_malloc(2223);
  free_ptrs[18] = my_malloc(2678);  free_ptrs[19] = my_malloc(2125);  free_ptrs[20] = my_malloc(2441);
  free_ptrs[12] = my_malloc(2350);  free_ptrs[13] = my_malloc(2367);  free_ptrs[14] = my_malloc(2318);
  free_ptrs[60] = my_malloc(2686);  free_ptrs[61] = my_malloc(2359);  free_ptrs[62] = my_malloc(2128);
  ptrs[27] = my_malloc(12541); dc[27] = 12552;
  ptrs[11] = my_malloc(12921); dc[11] = 12936;
  ptrs[7] = my_malloc(12193); dc[7] = 12208;
  ptrs[2] = my_malloc(12202); dc[2] = 12216;
  ptrs[0] = my_malloc(12384); dc[0] = 12392;
  ptrs[13] = my_malloc(12072); dc[13] = 12080;
  free_ptrs[81] = my_malloc(2378);  free_ptrs[82] = my_malloc(2443);  free_ptrs[83] = my_malloc(2435);
  free_ptrs[51] = my_malloc(2282);  free_ptrs[52] = my_malloc(2104);  free_ptrs[53] = my_malloc(2614);
  ptrs[23] = my_malloc(12374); dc[23] = 12384;
  free_ptrs[45] = my_malloc(2591);  free_ptrs[46] = my_malloc(2183);  free_ptrs[47] = my_malloc(2261);
  ptrs[15] = my_malloc(12602); dc[15] = 12616;
  free_ptrs[24] = my_malloc(2472);  free_ptrs[25] = my_malloc(2563);  free_ptrs[26] = my_malloc(2654);
  free_ptrs[48] = my_malloc(2272);  free_ptrs[49] = my_malloc(2413);  free_ptrs[50] = my_malloc(2266);
  ptrs[10] = my_malloc(12705); dc[10] = 12720;
  free_ptrs[57] = my_malloc(2406);  free_ptrs[58] = my_malloc(2490);  free_ptrs[59] = my_malloc(2288);
  ptrs[19] = my_malloc(12183); dc[19] = 12192;
  free_ptrs[42] = my_malloc(2071);  free_ptrs[43] = my_malloc(2293);  free_ptrs[44] = my_malloc(2534);
  free_ptrs[54] = my_malloc(2110);  free_ptrs[55] = my_malloc(2438);  free_ptrs[56] = my_malloc(2636);
  ptrs[26] = my_malloc(12850); dc[26] = 12864;
  free_ptrs[6] = my_malloc(2539);  free_ptrs[7] = my_malloc(2362);  free_ptrs[8] = my_malloc(2401);
  free_ptrs[66] = my_malloc(2188);  free_ptrs[67] = my_malloc(2406);  free_ptrs[68] = my_malloc(2676);
  free_ptrs[0] = my_malloc(2519);  free_ptrs[1] = my_malloc(2454);  free_ptrs[2] = my_malloc(2086);
  free_ptrs[72] = my_malloc(2176);  free_ptrs[73] = my_malloc(2211);  free_ptrs[74] = my_malloc(2375);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[81]);
  ptrs[16] = my_malloc(12840); dc[16] = 12848;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[0]);
  ptrs[14] = my_malloc(12969); dc[14] = 12984;
  my_free(free_ptrs[40]);
  my_free(free_ptrs[43]);
  ptrs[9] = my_malloc(12496); dc[9] = 12504;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[34]);
  ptrs[21] = my_malloc(12437); dc[21] = 12448;
  ptrs[22] = my_malloc(12950); dc[22] = 12960;
  my_free(free_ptrs[38]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[19]);
  ptrs[25] = my_malloc(12084); dc[25] = 12096;
  my_free(free_ptrs[5]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[71]);
  ptrs[28] = my_malloc(12332); dc[28] = 12344;
  my_free(free_ptrs[53]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[24]);
  ptrs[5] = my_malloc(12183); dc[5] = 12192;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[14]);
  ptrs[20] = my_malloc(12283); dc[20] = 12296;
  my_free(free_ptrs[89]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[20]);
  ptrs[24] = my_malloc(12691); dc[24] = 12704;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[31]);
  ptrs[1] = my_malloc(12636); dc[1] = 12648;
  my_free(free_ptrs[56]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 13, 620808);
  printf("Correct\n");
  return 0;
}
