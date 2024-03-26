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
  int *ptrs[27];
  int *free_ptrs[81];
  int dc[27];

  free_ptrs[15] = my_malloc(2570);  free_ptrs[16] = my_malloc(2071);  free_ptrs[17] = my_malloc(2651);
  ptrs[13] = my_malloc(12658); dc[13] = 12672;
  free_ptrs[3] = my_malloc(2473);  free_ptrs[4] = my_malloc(2177);  free_ptrs[5] = my_malloc(2507);
  free_ptrs[39] = my_malloc(2353);  free_ptrs[40] = my_malloc(2379);  free_ptrs[41] = my_malloc(2366);
  ptrs[11] = my_malloc(12739); dc[11] = 12752;
  free_ptrs[72] = my_malloc(2616);  free_ptrs[73] = my_malloc(2157);  free_ptrs[74] = my_malloc(2683);
  free_ptrs[78] = my_malloc(2186);  free_ptrs[79] = my_malloc(2077);  free_ptrs[80] = my_malloc(2139);
  free_ptrs[60] = my_malloc(2510);  free_ptrs[61] = my_malloc(2680);  free_ptrs[62] = my_malloc(2436);
  free_ptrs[33] = my_malloc(2508);  free_ptrs[34] = my_malloc(2542);  free_ptrs[35] = my_malloc(2510);
  free_ptrs[21] = my_malloc(2597);  free_ptrs[22] = my_malloc(2192);  free_ptrs[23] = my_malloc(2692);
  free_ptrs[45] = my_malloc(2167);  free_ptrs[46] = my_malloc(2135);  free_ptrs[47] = my_malloc(2616);
  free_ptrs[75] = my_malloc(2328);  free_ptrs[76] = my_malloc(2349);  free_ptrs[77] = my_malloc(2149);
  ptrs[23] = my_malloc(12864); dc[23] = 12872;
  free_ptrs[18] = my_malloc(2604);  free_ptrs[19] = my_malloc(2685);  free_ptrs[20] = my_malloc(2419);
  free_ptrs[9] = my_malloc(2278);  free_ptrs[10] = my_malloc(2244);  free_ptrs[11] = my_malloc(2423);
  ptrs[20] = my_malloc(12381); dc[20] = 12392;
  free_ptrs[51] = my_malloc(2484);  free_ptrs[52] = my_malloc(2270);  free_ptrs[53] = my_malloc(2495);
  free_ptrs[27] = my_malloc(2432);  free_ptrs[28] = my_malloc(2696);  free_ptrs[29] = my_malloc(2690);
  ptrs[24] = my_malloc(12613); dc[24] = 12624;
  free_ptrs[6] = my_malloc(2291);  free_ptrs[7] = my_malloc(2495);  free_ptrs[8] = my_malloc(2263);
  ptrs[25] = my_malloc(12014); dc[25] = 12024;
  ptrs[19] = my_malloc(12161); dc[19] = 12176;
  free_ptrs[54] = my_malloc(2658);  free_ptrs[55] = my_malloc(2339);  free_ptrs[56] = my_malloc(2675);
  free_ptrs[69] = my_malloc(2316);  free_ptrs[70] = my_malloc(2057);  free_ptrs[71] = my_malloc(2146);
  ptrs[1] = my_malloc(12310); dc[1] = 12320;
  free_ptrs[63] = my_malloc(2268);  free_ptrs[64] = my_malloc(2618);  free_ptrs[65] = my_malloc(2142);
  free_ptrs[30] = my_malloc(2507);  free_ptrs[31] = my_malloc(2623);  free_ptrs[32] = my_malloc(2538);
  free_ptrs[24] = my_malloc(2184);  free_ptrs[25] = my_malloc(2688);  free_ptrs[26] = my_malloc(2278);
  free_ptrs[66] = my_malloc(2607);  free_ptrs[67] = my_malloc(2113);  free_ptrs[68] = my_malloc(2614);
  free_ptrs[42] = my_malloc(2530);  free_ptrs[43] = my_malloc(2645);  free_ptrs[44] = my_malloc(2218);
  ptrs[18] = my_malloc(12102); dc[18] = 12112;
  free_ptrs[36] = my_malloc(2309);  free_ptrs[37] = my_malloc(2143);  free_ptrs[38] = my_malloc(2697);
  free_ptrs[48] = my_malloc(2458);  free_ptrs[49] = my_malloc(2139);  free_ptrs[50] = my_malloc(2596);
  free_ptrs[0] = my_malloc(2283);  free_ptrs[1] = my_malloc(2116);  free_ptrs[2] = my_malloc(2246);
  ptrs[6] = my_malloc(12573); dc[6] = 12584;
  ptrs[2] = my_malloc(12964); dc[2] = 12976;
  free_ptrs[57] = my_malloc(2278);  free_ptrs[58] = my_malloc(2113);  free_ptrs[59] = my_malloc(2049);
  ptrs[10] = my_malloc(12123); dc[10] = 12136;
  free_ptrs[12] = my_malloc(2547);  free_ptrs[13] = my_malloc(2695);  free_ptrs[14] = my_malloc(2357);
  my_free(free_ptrs[48]);
  ptrs[12] = my_malloc(12223); dc[12] = 12232;
  my_free(free_ptrs[8]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[2]);
  ptrs[15] = my_malloc(12076); dc[15] = 12088;
  my_free(free_ptrs[71]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[53]);
  ptrs[17] = my_malloc(12178); dc[17] = 12192;
  my_free(free_ptrs[38]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[36]);
  ptrs[7] = my_malloc(12475); dc[7] = 12488;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[54]);
  ptrs[8] = my_malloc(12746); dc[8] = 12760;
  ptrs[3] = my_malloc(12916); dc[3] = 12928;
  my_free(free_ptrs[29]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[33]);
  ptrs[0] = my_malloc(12330); dc[0] = 12344;
  my_free(free_ptrs[41]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[15]);
  ptrs[5] = my_malloc(12345); dc[5] = 12360;
  my_free(free_ptrs[18]);
  ptrs[16] = my_malloc(12354); dc[16] = 12368;
  my_free(free_ptrs[55]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[24]);
  ptrs[4] = my_malloc(12629); dc[4] = 12640;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[65]);
  ptrs[21] = my_malloc(12591); dc[21] = 12600;
  my_free(free_ptrs[62]);
  my_free(free_ptrs[10]);
  ptrs[22] = my_malloc(12168); dc[22] = 12176;
  ptrs[9] = my_malloc(12298); dc[9] = 12312;
  my_free(free_ptrs[32]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[74]);
  ptrs[26] = my_malloc(12644); dc[26] = 12656;
  my_free(free_ptrs[76]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[12]);
  ptrs[14] = my_malloc(12883); dc[14] = 12896;
  my_free(free_ptrs[57]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 11, 557864);
  printf("Correct\n");
  return 0;
}
