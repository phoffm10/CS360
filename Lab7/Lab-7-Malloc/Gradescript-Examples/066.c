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

  ptrs[15] = my_malloc(12650); dc[15] = 12664;
  free_ptrs[57] = my_malloc(2385);  free_ptrs[58] = my_malloc(2671);  free_ptrs[59] = my_malloc(2109);
  ptrs[27] = my_malloc(12134); dc[27] = 12144;
  free_ptrs[21] = my_malloc(2184);  free_ptrs[22] = my_malloc(2083);  free_ptrs[23] = my_malloc(2242);
  free_ptrs[69] = my_malloc(2641);  free_ptrs[70] = my_malloc(2563);  free_ptrs[71] = my_malloc(2463);
  ptrs[10] = my_malloc(12709); dc[10] = 12720;
  free_ptrs[60] = my_malloc(2485);  free_ptrs[61] = my_malloc(2165);  free_ptrs[62] = my_malloc(2177);
  free_ptrs[12] = my_malloc(2140);  free_ptrs[13] = my_malloc(2501);  free_ptrs[14] = my_malloc(2123);
  free_ptrs[63] = my_malloc(2084);  free_ptrs[64] = my_malloc(2668);  free_ptrs[65] = my_malloc(2517);
  free_ptrs[51] = my_malloc(2354);  free_ptrs[52] = my_malloc(2101);  free_ptrs[53] = my_malloc(2525);
  free_ptrs[45] = my_malloc(2508);  free_ptrs[46] = my_malloc(2183);  free_ptrs[47] = my_malloc(2590);
  free_ptrs[81] = my_malloc(2201);  free_ptrs[82] = my_malloc(2119);  free_ptrs[83] = my_malloc(2491);
  ptrs[4] = my_malloc(12656); dc[4] = 12664;
  free_ptrs[27] = my_malloc(2589);  free_ptrs[28] = my_malloc(2599);  free_ptrs[29] = my_malloc(2506);
  free_ptrs[0] = my_malloc(2296);  free_ptrs[1] = my_malloc(2301);  free_ptrs[2] = my_malloc(2675);
  free_ptrs[18] = my_malloc(2348);  free_ptrs[19] = my_malloc(2347);  free_ptrs[20] = my_malloc(2213);
  free_ptrs[24] = my_malloc(2131);  free_ptrs[25] = my_malloc(2324);  free_ptrs[26] = my_malloc(2454);
  free_ptrs[6] = my_malloc(2293);  free_ptrs[7] = my_malloc(2401);  free_ptrs[8] = my_malloc(2651);
  free_ptrs[66] = my_malloc(2153);  free_ptrs[67] = my_malloc(2616);  free_ptrs[68] = my_malloc(2209);
  ptrs[17] = my_malloc(12928); dc[17] = 12936;
  free_ptrs[54] = my_malloc(2236);  free_ptrs[55] = my_malloc(2226);  free_ptrs[56] = my_malloc(2461);
  free_ptrs[36] = my_malloc(2477);  free_ptrs[37] = my_malloc(2323);  free_ptrs[38] = my_malloc(2557);
  free_ptrs[15] = my_malloc(2164);  free_ptrs[16] = my_malloc(2198);  free_ptrs[17] = my_malloc(2551);
  free_ptrs[3] = my_malloc(2448);  free_ptrs[4] = my_malloc(2361);  free_ptrs[5] = my_malloc(2304);
  ptrs[23] = my_malloc(12670); dc[23] = 12680;
  ptrs[8] = my_malloc(12997); dc[8] = 13008;
  free_ptrs[42] = my_malloc(2359);  free_ptrs[43] = my_malloc(2126);  free_ptrs[44] = my_malloc(2352);
  ptrs[26] = my_malloc(12390); dc[26] = 12400;
  free_ptrs[48] = my_malloc(2341);  free_ptrs[49] = my_malloc(2237);  free_ptrs[50] = my_malloc(2586);
  ptrs[7] = my_malloc(12890); dc[7] = 12904;
  free_ptrs[39] = my_malloc(2366);  free_ptrs[40] = my_malloc(2421);  free_ptrs[41] = my_malloc(2149);
  ptrs[1] = my_malloc(12021); dc[1] = 12032;
  free_ptrs[72] = my_malloc(2114);  free_ptrs[73] = my_malloc(2060);  free_ptrs[74] = my_malloc(2306);
  free_ptrs[78] = my_malloc(2265);  free_ptrs[79] = my_malloc(2068);  free_ptrs[80] = my_malloc(2613);
  free_ptrs[9] = my_malloc(2269);  free_ptrs[10] = my_malloc(2201);  free_ptrs[11] = my_malloc(2108);
  ptrs[0] = my_malloc(12124); dc[0] = 12136;
  ptrs[9] = my_malloc(12817); dc[9] = 12832;
  ptrs[12] = my_malloc(12129); dc[12] = 12144;
  free_ptrs[30] = my_malloc(2286);  free_ptrs[31] = my_malloc(2443);  free_ptrs[32] = my_malloc(2061);
  free_ptrs[75] = my_malloc(2393);  free_ptrs[76] = my_malloc(2689);  free_ptrs[77] = my_malloc(2579);
  free_ptrs[33] = my_malloc(2163);  free_ptrs[34] = my_malloc(2064);  free_ptrs[35] = my_malloc(2640);
  ptrs[5] = my_malloc(12879); dc[5] = 12888;
  ptrs[24] = my_malloc(12335); dc[24] = 12344;
  my_free(free_ptrs[44]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[56]);
  ptrs[20] = my_malloc(12224); dc[20] = 12232;
  my_free(free_ptrs[58]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[6]);
  ptrs[19] = my_malloc(12728); dc[19] = 12736;
  ptrs[25] = my_malloc(12845); dc[25] = 12856;
  my_free(free_ptrs[3]);
  ptrs[16] = my_malloc(12724); dc[16] = 12736;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[51]);
  ptrs[18] = my_malloc(12777); dc[18] = 12792;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[70]);
  ptrs[14] = my_malloc(12741); dc[14] = 12752;
  ptrs[13] = my_malloc(12576); dc[13] = 12584;
  my_free(free_ptrs[77]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[83]);
  ptrs[6] = my_malloc(12032); dc[6] = 12040;
  my_free(free_ptrs[59]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[10]);
  ptrs[21] = my_malloc(12117); dc[21] = 12128;
  my_free(free_ptrs[82]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[52]);
  ptrs[22] = my_malloc(12794); dc[22] = 12808;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[8]);
  ptrs[2] = my_malloc(12598); dc[2] = 12608;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[55]);
  ptrs[3] = my_malloc(12842); dc[3] = 12856;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[12]);
  ptrs[11] = my_malloc(12729); dc[11] = 12744;
  my_free(free_ptrs[9]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 10, 581744);
  printf("Correct\n");
  return 0;
}
