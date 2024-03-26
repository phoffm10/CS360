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

  free_ptrs[24] = my_malloc(2506);  free_ptrs[25] = my_malloc(2190);  free_ptrs[26] = my_malloc(2342);
  free_ptrs[66] = my_malloc(2275);  free_ptrs[67] = my_malloc(2378);  free_ptrs[68] = my_malloc(2318);
  free_ptrs[69] = my_malloc(2061);  free_ptrs[70] = my_malloc(2186);  free_ptrs[71] = my_malloc(2469);
  free_ptrs[15] = my_malloc(2097);  free_ptrs[16] = my_malloc(2427);  free_ptrs[17] = my_malloc(2065);
  free_ptrs[9] = my_malloc(2514);  free_ptrs[10] = my_malloc(2165);  free_ptrs[11] = my_malloc(2269);
  free_ptrs[30] = my_malloc(2489);  free_ptrs[31] = my_malloc(2524);  free_ptrs[32] = my_malloc(2511);
  free_ptrs[36] = my_malloc(2301);  free_ptrs[37] = my_malloc(2599);  free_ptrs[38] = my_malloc(2065);
  free_ptrs[45] = my_malloc(2465);  free_ptrs[46] = my_malloc(2690);  free_ptrs[47] = my_malloc(2255);
  ptrs[1] = my_malloc(12080); dc[1] = 12088;
  free_ptrs[6] = my_malloc(2543);  free_ptrs[7] = my_malloc(2653);  free_ptrs[8] = my_malloc(2191);
  free_ptrs[72] = my_malloc(2675);  free_ptrs[73] = my_malloc(2503);  free_ptrs[74] = my_malloc(2356);
  free_ptrs[3] = my_malloc(2529);  free_ptrs[4] = my_malloc(2175);  free_ptrs[5] = my_malloc(2186);
  ptrs[3] = my_malloc(12622); dc[3] = 12632;
  free_ptrs[54] = my_malloc(2161);  free_ptrs[55] = my_malloc(2427);  free_ptrs[56] = my_malloc(2304);
  free_ptrs[63] = my_malloc(2274);  free_ptrs[64] = my_malloc(2526);  free_ptrs[65] = my_malloc(2129);
  free_ptrs[33] = my_malloc(2476);  free_ptrs[34] = my_malloc(2224);  free_ptrs[35] = my_malloc(2295);
  free_ptrs[57] = my_malloc(2251);  free_ptrs[58] = my_malloc(2671);  free_ptrs[59] = my_malloc(2476);
  ptrs[19] = my_malloc(12891); dc[19] = 12904;
  ptrs[9] = my_malloc(12860); dc[9] = 12872;
  free_ptrs[48] = my_malloc(2521);  free_ptrs[49] = my_malloc(2608);  free_ptrs[50] = my_malloc(2542);
  free_ptrs[60] = my_malloc(2248);  free_ptrs[61] = my_malloc(2298);  free_ptrs[62] = my_malloc(2260);
  ptrs[22] = my_malloc(12306); dc[22] = 12320;
  free_ptrs[27] = my_malloc(2330);  free_ptrs[28] = my_malloc(2428);  free_ptrs[29] = my_malloc(2337);
  free_ptrs[51] = my_malloc(2138);  free_ptrs[52] = my_malloc(2097);  free_ptrs[53] = my_malloc(2072);
  ptrs[16] = my_malloc(12180); dc[16] = 12192;
  free_ptrs[18] = my_malloc(2549);  free_ptrs[19] = my_malloc(2467);  free_ptrs[20] = my_malloc(2662);
  free_ptrs[78] = my_malloc(2127);  free_ptrs[79] = my_malloc(2171);  free_ptrs[80] = my_malloc(2144);
  ptrs[2] = my_malloc(12462); dc[2] = 12472;
  free_ptrs[39] = my_malloc(2689);  free_ptrs[40] = my_malloc(2208);  free_ptrs[41] = my_malloc(2308);
  ptrs[7] = my_malloc(12181); dc[7] = 12192;
  ptrs[11] = my_malloc(12877); dc[11] = 12888;
  ptrs[17] = my_malloc(12156); dc[17] = 12168;
  ptrs[13] = my_malloc(12324); dc[13] = 12336;
  free_ptrs[12] = my_malloc(2511);  free_ptrs[13] = my_malloc(2255);  free_ptrs[14] = my_malloc(2626);
  ptrs[14] = my_malloc(12709); dc[14] = 12720;
  ptrs[0] = my_malloc(12268); dc[0] = 12280;
  free_ptrs[75] = my_malloc(2695);  free_ptrs[76] = my_malloc(2455);  free_ptrs[77] = my_malloc(2453);
  ptrs[8] = my_malloc(12292); dc[8] = 12304;
  free_ptrs[81] = my_malloc(2104);  free_ptrs[82] = my_malloc(2669);  free_ptrs[83] = my_malloc(2658);
  ptrs[23] = my_malloc(12506); dc[23] = 12520;
  ptrs[26] = my_malloc(12606); dc[26] = 12616;
  free_ptrs[0] = my_malloc(2212);  free_ptrs[1] = my_malloc(2112);  free_ptrs[2] = my_malloc(2497);
  free_ptrs[21] = my_malloc(2688);  free_ptrs[22] = my_malloc(2630);  free_ptrs[23] = my_malloc(2177);
  free_ptrs[42] = my_malloc(2155);  free_ptrs[43] = my_malloc(2606);  free_ptrs[44] = my_malloc(2059);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[33]);
  ptrs[6] = my_malloc(12455); dc[6] = 12464;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[69]);
  ptrs[24] = my_malloc(12383); dc[24] = 12392;
  my_free(free_ptrs[61]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[65]);
  ptrs[18] = my_malloc(12136); dc[18] = 12144;
  my_free(free_ptrs[48]);
  my_free(free_ptrs[12]);
  ptrs[5] = my_malloc(12843); dc[5] = 12856;
  ptrs[10] = my_malloc(12917); dc[10] = 12928;
  my_free(free_ptrs[79]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[49]);
  ptrs[25] = my_malloc(12064); dc[25] = 12072;
  my_free(free_ptrs[77]);
  ptrs[21] = my_malloc(12489); dc[21] = 12504;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[41]);
  ptrs[20] = my_malloc(12647); dc[20] = 12656;
  my_free(free_ptrs[72]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[28]);
  ptrs[27] = my_malloc(12489); dc[27] = 12504;
  my_free(free_ptrs[71]);
  ptrs[4] = my_malloc(12983); dc[4] = 12992;
  ptrs[12] = my_malloc(12617); dc[12] = 12632;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[4]);
  ptrs[15] = my_malloc(12486); dc[15] = 12496;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[27]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 11, 579520);
  printf("Correct\n");
  return 0;
}
