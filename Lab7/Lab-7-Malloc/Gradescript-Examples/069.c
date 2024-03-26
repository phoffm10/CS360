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

  free_ptrs[66] = my_malloc(2315);  free_ptrs[67] = my_malloc(2180);  free_ptrs[68] = my_malloc(2143);
  free_ptrs[9] = my_malloc(2453);  free_ptrs[10] = my_malloc(2279);  free_ptrs[11] = my_malloc(2248);
  free_ptrs[30] = my_malloc(2520);  free_ptrs[31] = my_malloc(2571);  free_ptrs[32] = my_malloc(2421);
  free_ptrs[69] = my_malloc(2511);  free_ptrs[70] = my_malloc(2441);  free_ptrs[71] = my_malloc(2379);
  free_ptrs[39] = my_malloc(2168);  free_ptrs[40] = my_malloc(2131);  free_ptrs[41] = my_malloc(2487);
  free_ptrs[12] = my_malloc(2232);  free_ptrs[13] = my_malloc(2091);  free_ptrs[14] = my_malloc(2635);
  free_ptrs[78] = my_malloc(2665);  free_ptrs[79] = my_malloc(2596);  free_ptrs[80] = my_malloc(2617);
  ptrs[20] = my_malloc(12218); dc[20] = 12232;
  ptrs[5] = my_malloc(12049); dc[5] = 12064;
  free_ptrs[33] = my_malloc(2671);  free_ptrs[34] = my_malloc(2658);  free_ptrs[35] = my_malloc(2268);
  ptrs[9] = my_malloc(12459); dc[9] = 12472;
  free_ptrs[45] = my_malloc(2444);  free_ptrs[46] = my_malloc(2327);  free_ptrs[47] = my_malloc(2108);
  free_ptrs[6] = my_malloc(2563);  free_ptrs[7] = my_malloc(2217);  free_ptrs[8] = my_malloc(2175);
  ptrs[13] = my_malloc(12450); dc[13] = 12464;
  free_ptrs[42] = my_malloc(2521);  free_ptrs[43] = my_malloc(2464);  free_ptrs[44] = my_malloc(2358);
  free_ptrs[15] = my_malloc(2690);  free_ptrs[16] = my_malloc(2154);  free_ptrs[17] = my_malloc(2467);
  ptrs[24] = my_malloc(12489); dc[24] = 12504;
  ptrs[19] = my_malloc(12874); dc[19] = 12888;
  free_ptrs[48] = my_malloc(2287);  free_ptrs[49] = my_malloc(2499);  free_ptrs[50] = my_malloc(2126);
  ptrs[27] = my_malloc(12336); dc[27] = 12344;
  free_ptrs[36] = my_malloc(2249);  free_ptrs[37] = my_malloc(2173);  free_ptrs[38] = my_malloc(2387);
  free_ptrs[63] = my_malloc(2144);  free_ptrs[64] = my_malloc(2614);  free_ptrs[65] = my_malloc(2535);
  free_ptrs[51] = my_malloc(2458);  free_ptrs[52] = my_malloc(2411);  free_ptrs[53] = my_malloc(2305);
  free_ptrs[0] = my_malloc(2056);  free_ptrs[1] = my_malloc(2663);  free_ptrs[2] = my_malloc(2361);
  ptrs[21] = my_malloc(12415); dc[21] = 12424;
  free_ptrs[60] = my_malloc(2529);  free_ptrs[61] = my_malloc(2527);  free_ptrs[62] = my_malloc(2389);
  free_ptrs[57] = my_malloc(2671);  free_ptrs[58] = my_malloc(2275);  free_ptrs[59] = my_malloc(2399);
  free_ptrs[27] = my_malloc(2517);  free_ptrs[28] = my_malloc(2287);  free_ptrs[29] = my_malloc(2534);
  free_ptrs[21] = my_malloc(2412);  free_ptrs[22] = my_malloc(2461);  free_ptrs[23] = my_malloc(2430);
  free_ptrs[75] = my_malloc(2333);  free_ptrs[76] = my_malloc(2619);  free_ptrs[77] = my_malloc(2303);
  ptrs[18] = my_malloc(12643); dc[18] = 12656;
  ptrs[7] = my_malloc(12572); dc[7] = 12584;
  ptrs[1] = my_malloc(12975); dc[1] = 12984;
  free_ptrs[3] = my_malloc(2520);  free_ptrs[4] = my_malloc(2555);  free_ptrs[5] = my_malloc(2510);
  ptrs[0] = my_malloc(12182); dc[0] = 12192;
  free_ptrs[54] = my_malloc(2590);  free_ptrs[55] = my_malloc(2176);  free_ptrs[56] = my_malloc(2689);
  free_ptrs[72] = my_malloc(2606);  free_ptrs[73] = my_malloc(2674);  free_ptrs[74] = my_malloc(2542);
  free_ptrs[81] = my_malloc(2269);  free_ptrs[82] = my_malloc(2469);  free_ptrs[83] = my_malloc(2349);
  free_ptrs[18] = my_malloc(2580);  free_ptrs[19] = my_malloc(2227);  free_ptrs[20] = my_malloc(2545);
  ptrs[11] = my_malloc(12075); dc[11] = 12088;
  ptrs[3] = my_malloc(12724); dc[3] = 12736;
  free_ptrs[24] = my_malloc(2225);  free_ptrs[25] = my_malloc(2696);  free_ptrs[26] = my_malloc(2520);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[79]);
  ptrs[25] = my_malloc(12855); dc[25] = 12864;
  my_free(free_ptrs[8]);
  ptrs[12] = my_malloc(12019); dc[12] = 12032;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[35]);
  ptrs[22] = my_malloc(12292); dc[22] = 12304;
  my_free(free_ptrs[28]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[34]);
  ptrs[17] = my_malloc(12594); dc[17] = 12608;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[53]);
  ptrs[8] = my_malloc(12447); dc[8] = 12456;
  my_free(free_ptrs[55]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[10]);
  ptrs[15] = my_malloc(12532); dc[15] = 12544;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[9]);
  ptrs[16] = my_malloc(12230); dc[16] = 12240;
  my_free(free_ptrs[82]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[80]);
  ptrs[14] = my_malloc(12047); dc[14] = 12056;
  ptrs[4] = my_malloc(12386); dc[4] = 12400;
  my_free(free_ptrs[33]);
  ptrs[23] = my_malloc(12928); dc[23] = 12936;
  my_free(free_ptrs[54]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[72]);
  ptrs[26] = my_malloc(12512); dc[26] = 12520;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[26]);
  ptrs[10] = my_malloc(12927); dc[10] = 12936;
  my_free(free_ptrs[68]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[41]);
  ptrs[2] = my_malloc(12968); dc[2] = 12976;
  my_free(free_ptrs[65]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[40]);
  ptrs[6] = my_malloc(12538); dc[6] = 12552;

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 10, 579432);
  printf("Correct\n");
  return 0;
}
