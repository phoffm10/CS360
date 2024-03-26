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

  ptrs[4] = my_malloc(12198); dc[4] = 12208;
  free_ptrs[18] = my_malloc(2561);  free_ptrs[19] = my_malloc(2201);  free_ptrs[20] = my_malloc(2215);
  free_ptrs[36] = my_malloc(2697);  free_ptrs[37] = my_malloc(2334);  free_ptrs[38] = my_malloc(2659);
  ptrs[21] = my_malloc(12715); dc[21] = 12728;
  free_ptrs[27] = my_malloc(2588);  free_ptrs[28] = my_malloc(2247);  free_ptrs[29] = my_malloc(2604);
  free_ptrs[24] = my_malloc(2650);  free_ptrs[25] = my_malloc(2683);  free_ptrs[26] = my_malloc(2434);
  free_ptrs[54] = my_malloc(2493);  free_ptrs[55] = my_malloc(2568);  free_ptrs[56] = my_malloc(2271);
  free_ptrs[72] = my_malloc(2360);  free_ptrs[73] = my_malloc(2193);  free_ptrs[74] = my_malloc(2549);
  free_ptrs[60] = my_malloc(2163);  free_ptrs[61] = my_malloc(2402);  free_ptrs[62] = my_malloc(2683);
  free_ptrs[3] = my_malloc(2270);  free_ptrs[4] = my_malloc(2301);  free_ptrs[5] = my_malloc(2470);
  ptrs[15] = my_malloc(12648); dc[15] = 12656;
  free_ptrs[66] = my_malloc(2661);  free_ptrs[67] = my_malloc(2272);  free_ptrs[68] = my_malloc(2407);
  ptrs[13] = my_malloc(12198); dc[13] = 12208;
  free_ptrs[81] = my_malloc(2069);  free_ptrs[82] = my_malloc(2134);  free_ptrs[83] = my_malloc(2188);
  free_ptrs[9] = my_malloc(2532);  free_ptrs[10] = my_malloc(2598);  free_ptrs[11] = my_malloc(2298);
  ptrs[20] = my_malloc(12854); dc[20] = 12864;
  free_ptrs[51] = my_malloc(2515);  free_ptrs[52] = my_malloc(2145);  free_ptrs[53] = my_malloc(2515);
  ptrs[1] = my_malloc(12883); dc[1] = 12896;
  ptrs[7] = my_malloc(12584); dc[7] = 12592;
  free_ptrs[87] = my_malloc(2277);  free_ptrs[88] = my_malloc(2264);  free_ptrs[89] = my_malloc(2285);
  ptrs[0] = my_malloc(12298); dc[0] = 12312;
  ptrs[5] = my_malloc(12389); dc[5] = 12400;
  free_ptrs[15] = my_malloc(2297);  free_ptrs[16] = my_malloc(2432);  free_ptrs[17] = my_malloc(2497);
  free_ptrs[30] = my_malloc(2493);  free_ptrs[31] = my_malloc(2351);  free_ptrs[32] = my_malloc(2272);
  free_ptrs[21] = my_malloc(2152);  free_ptrs[22] = my_malloc(2591);  free_ptrs[23] = my_malloc(2229);
  ptrs[25] = my_malloc(12875); dc[25] = 12888;
  free_ptrs[12] = my_malloc(2357);  free_ptrs[13] = my_malloc(2549);  free_ptrs[14] = my_malloc(2257);
  free_ptrs[0] = my_malloc(2383);  free_ptrs[1] = my_malloc(2440);  free_ptrs[2] = my_malloc(2084);
  free_ptrs[39] = my_malloc(2515);  free_ptrs[40] = my_malloc(2631);  free_ptrs[41] = my_malloc(2519);
  ptrs[11] = my_malloc(12471); dc[11] = 12480;
  free_ptrs[33] = my_malloc(2178);  free_ptrs[34] = my_malloc(2180);  free_ptrs[35] = my_malloc(2212);
  ptrs[19] = my_malloc(12166); dc[19] = 12176;
  ptrs[17] = my_malloc(12574); dc[17] = 12584;
  free_ptrs[6] = my_malloc(2523);  free_ptrs[7] = my_malloc(2177);  free_ptrs[8] = my_malloc(2326);
  ptrs[8] = my_malloc(12995); dc[8] = 13008;
  free_ptrs[48] = my_malloc(2506);  free_ptrs[49] = my_malloc(2365);  free_ptrs[50] = my_malloc(2268);
  ptrs[9] = my_malloc(12095); dc[9] = 12104;
  free_ptrs[84] = my_malloc(2286);  free_ptrs[85] = my_malloc(2375);  free_ptrs[86] = my_malloc(2347);
  ptrs[6] = my_malloc(12550); dc[6] = 12560;
  free_ptrs[69] = my_malloc(2211);  free_ptrs[70] = my_malloc(2615);  free_ptrs[71] = my_malloc(2205);
  free_ptrs[45] = my_malloc(2444);  free_ptrs[46] = my_malloc(2392);  free_ptrs[47] = my_malloc(2340);
  free_ptrs[78] = my_malloc(2623);  free_ptrs[79] = my_malloc(2464);  free_ptrs[80] = my_malloc(2479);
  free_ptrs[42] = my_malloc(2370);  free_ptrs[43] = my_malloc(2567);  free_ptrs[44] = my_malloc(2366);
  free_ptrs[63] = my_malloc(2569);  free_ptrs[64] = my_malloc(2548);  free_ptrs[65] = my_malloc(2409);
  free_ptrs[57] = my_malloc(2329);  free_ptrs[58] = my_malloc(2650);  free_ptrs[59] = my_malloc(2054);
  free_ptrs[75] = my_malloc(2401);  free_ptrs[76] = my_malloc(2465);  free_ptrs[77] = my_malloc(2358);
  ptrs[3] = my_malloc(12136); dc[3] = 12144;
  my_free(free_ptrs[88]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[27]);
  ptrs[24] = my_malloc(12797); dc[24] = 12808;
  ptrs[27] = my_malloc(12388); dc[27] = 12400;
  my_free(free_ptrs[48]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[83]);
  ptrs[18] = my_malloc(12727); dc[18] = 12736;
  ptrs[10] = my_malloc(12715); dc[10] = 12728;
  my_free(free_ptrs[66]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[35]);
  ptrs[23] = my_malloc(12796); dc[23] = 12808;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[70]);
  ptrs[12] = my_malloc(12447); dc[12] = 12456;
  my_free(free_ptrs[42]);
  ptrs[29] = my_malloc(12141); dc[29] = 12152;
  my_free(free_ptrs[29]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[55]);
  ptrs[28] = my_malloc(12526); dc[28] = 12536;
  my_free(free_ptrs[36]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[4]);
  ptrs[26] = my_malloc(12756); dc[26] = 12768;
  my_free(free_ptrs[24]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[78]);
  ptrs[2] = my_malloc(12708); dc[2] = 12720;
  my_free(free_ptrs[85]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[38]);
  ptrs[22] = my_malloc(12936); dc[22] = 12944;
  ptrs[14] = my_malloc(12307); dc[14] = 12320;
  my_free(free_ptrs[64]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[58]);
  ptrs[16] = my_malloc(12890); dc[16] = 12904;
  my_free(free_ptrs[89]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[65]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 13, 622848);
  printf("Correct\n");
  return 0;
}
