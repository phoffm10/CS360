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

  ptrs[10] = my_malloc(12102); dc[10] = 12112;
  free_ptrs[6] = my_malloc(2187);  free_ptrs[7] = my_malloc(2098);  free_ptrs[8] = my_malloc(2159);
  ptrs[17] = my_malloc(12301); dc[17] = 12312;
  free_ptrs[78] = my_malloc(2559);  free_ptrs[79] = my_malloc(2682);  free_ptrs[80] = my_malloc(2150);
  free_ptrs[45] = my_malloc(2072);  free_ptrs[46] = my_malloc(2358);  free_ptrs[47] = my_malloc(2448);
  ptrs[8] = my_malloc(12437); dc[8] = 12448;
  free_ptrs[66] = my_malloc(2337);  free_ptrs[67] = my_malloc(2099);  free_ptrs[68] = my_malloc(2266);
  ptrs[21] = my_malloc(12386); dc[21] = 12400;
  free_ptrs[60] = my_malloc(2164);  free_ptrs[61] = my_malloc(2245);  free_ptrs[62] = my_malloc(2514);
  ptrs[15] = my_malloc(12983); dc[15] = 12992;
  free_ptrs[18] = my_malloc(2392);  free_ptrs[19] = my_malloc(2422);  free_ptrs[20] = my_malloc(2257);
  free_ptrs[75] = my_malloc(2239);  free_ptrs[76] = my_malloc(2070);  free_ptrs[77] = my_malloc(2513);
  free_ptrs[51] = my_malloc(2185);  free_ptrs[52] = my_malloc(2463);  free_ptrs[53] = my_malloc(2636);
  free_ptrs[27] = my_malloc(2389);  free_ptrs[28] = my_malloc(2476);  free_ptrs[29] = my_malloc(2603);
  free_ptrs[63] = my_malloc(2267);  free_ptrs[64] = my_malloc(2532);  free_ptrs[65] = my_malloc(2679);
  ptrs[24] = my_malloc(12752); dc[24] = 12760;
  free_ptrs[48] = my_malloc(2508);  free_ptrs[49] = my_malloc(2503);  free_ptrs[50] = my_malloc(2437);
  free_ptrs[12] = my_malloc(2236);  free_ptrs[13] = my_malloc(2247);  free_ptrs[14] = my_malloc(2311);
  ptrs[18] = my_malloc(12385); dc[18] = 12400;
  free_ptrs[84] = my_malloc(2279);  free_ptrs[85] = my_malloc(2317);  free_ptrs[86] = my_malloc(2598);
  ptrs[26] = my_malloc(12479); dc[26] = 12488;
  free_ptrs[87] = my_malloc(2079);  free_ptrs[88] = my_malloc(2653);  free_ptrs[89] = my_malloc(2327);
  free_ptrs[33] = my_malloc(2340);  free_ptrs[34] = my_malloc(2338);  free_ptrs[35] = my_malloc(2321);
  free_ptrs[42] = my_malloc(2660);  free_ptrs[43] = my_malloc(2383);  free_ptrs[44] = my_malloc(2618);
  ptrs[9] = my_malloc(12101); dc[9] = 12112;
  free_ptrs[69] = my_malloc(2514);  free_ptrs[70] = my_malloc(2596);  free_ptrs[71] = my_malloc(2534);
  ptrs[4] = my_malloc(12472); dc[4] = 12480;
  ptrs[2] = my_malloc(12951); dc[2] = 12960;
  ptrs[22] = my_malloc(12843); dc[22] = 12856;
  ptrs[14] = my_malloc(12206); dc[14] = 12216;
  free_ptrs[21] = my_malloc(2070);  free_ptrs[22] = my_malloc(2157);  free_ptrs[23] = my_malloc(2561);
  free_ptrs[39] = my_malloc(2170);  free_ptrs[40] = my_malloc(2357);  free_ptrs[41] = my_malloc(2643);
  free_ptrs[3] = my_malloc(2546);  free_ptrs[4] = my_malloc(2111);  free_ptrs[5] = my_malloc(2229);
  free_ptrs[57] = my_malloc(2541);  free_ptrs[58] = my_malloc(2273);  free_ptrs[59] = my_malloc(2656);
  free_ptrs[36] = my_malloc(2534);  free_ptrs[37] = my_malloc(2271);  free_ptrs[38] = my_malloc(2129);
  ptrs[28] = my_malloc(12681); dc[28] = 12696;
  ptrs[19] = my_malloc(12548); dc[19] = 12560;
  free_ptrs[0] = my_malloc(2049);  free_ptrs[1] = my_malloc(2393);  free_ptrs[2] = my_malloc(2640);
  ptrs[12] = my_malloc(12418); dc[12] = 12432;
  free_ptrs[9] = my_malloc(2549);  free_ptrs[10] = my_malloc(2276);  free_ptrs[11] = my_malloc(2448);
  free_ptrs[72] = my_malloc(2356);  free_ptrs[73] = my_malloc(2660);  free_ptrs[74] = my_malloc(2522);
  free_ptrs[15] = my_malloc(2119);  free_ptrs[16] = my_malloc(2653);  free_ptrs[17] = my_malloc(2293);
  free_ptrs[24] = my_malloc(2466);  free_ptrs[25] = my_malloc(2187);  free_ptrs[26] = my_malloc(2609);
  ptrs[30] = my_malloc(12836); dc[30] = 12848;
  free_ptrs[81] = my_malloc(2436);  free_ptrs[82] = my_malloc(2668);  free_ptrs[83] = my_malloc(2575);
  free_ptrs[90] = my_malloc(2397);  free_ptrs[91] = my_malloc(2220);  free_ptrs[92] = my_malloc(2070);
  free_ptrs[30] = my_malloc(2166);  free_ptrs[31] = my_malloc(2472);  free_ptrs[32] = my_malloc(2323);
  free_ptrs[54] = my_malloc(2611);  free_ptrs[55] = my_malloc(2315);  free_ptrs[56] = my_malloc(2534);
  ptrs[13] = my_malloc(12405); dc[13] = 12416;
  my_free(free_ptrs[55]);
  ptrs[23] = my_malloc(12019); dc[23] = 12032;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[60]);
  ptrs[6] = my_malloc(12760); dc[6] = 12768;
  my_free(free_ptrs[77]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[49]);
  ptrs[27] = my_malloc(12194); dc[27] = 12208;
  my_free(free_ptrs[88]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[0]);
  ptrs[7] = my_malloc(12046); dc[7] = 12056;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[61]);
  ptrs[0] = my_malloc(12853); dc[0] = 12864;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[92]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[78]);
  ptrs[20] = my_malloc(12240); dc[20] = 12248;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[76]);
  ptrs[16] = my_malloc(12901); dc[16] = 12912;
  my_free(free_ptrs[46]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[38]);
  ptrs[1] = my_malloc(12521); dc[1] = 12536;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[73]);
  ptrs[5] = my_malloc(12932); dc[5] = 12944;
  my_free(free_ptrs[66]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[90]);
  ptrs[3] = my_malloc(12711); dc[3] = 12720;
  ptrs[11] = my_malloc(12990); dc[11] = 13000;
  my_free(free_ptrs[3]);
  ptrs[25] = my_malloc(12433); dc[25] = 12448;
  my_free(free_ptrs[19]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[83]);
  ptrs[29] = my_malloc(12347); dc[29] = 12360;
  my_free(free_ptrs[32]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[37]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 13, 642536);
  printf("Correct\n");
  return 0;
}
