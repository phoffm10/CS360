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

  free_ptrs[60] = my_malloc(2072);  free_ptrs[61] = my_malloc(2405);  free_ptrs[62] = my_malloc(2222);
  free_ptrs[63] = my_malloc(2659);  free_ptrs[64] = my_malloc(2602);  free_ptrs[65] = my_malloc(2247);
  ptrs[18] = my_malloc(12018); dc[18] = 12032;
  free_ptrs[87] = my_malloc(2264);  free_ptrs[88] = my_malloc(2486);  free_ptrs[89] = my_malloc(2068);
  ptrs[13] = my_malloc(12910); dc[13] = 12920;
  ptrs[19] = my_malloc(12869); dc[19] = 12880;
  ptrs[20] = my_malloc(12745); dc[20] = 12760;
  free_ptrs[12] = my_malloc(2296);  free_ptrs[13] = my_malloc(2577);  free_ptrs[14] = my_malloc(2440);
  free_ptrs[57] = my_malloc(2398);  free_ptrs[58] = my_malloc(2692);  free_ptrs[59] = my_malloc(2598);
  ptrs[21] = my_malloc(12643); dc[21] = 12656;
  free_ptrs[42] = my_malloc(2671);  free_ptrs[43] = my_malloc(2267);  free_ptrs[44] = my_malloc(2558);
  free_ptrs[36] = my_malloc(2609);  free_ptrs[37] = my_malloc(2237);  free_ptrs[38] = my_malloc(2550);
  ptrs[15] = my_malloc(12960); dc[15] = 12968;
  free_ptrs[9] = my_malloc(2579);  free_ptrs[10] = my_malloc(2202);  free_ptrs[11] = my_malloc(2265);
  ptrs[11] = my_malloc(12695); dc[11] = 12704;
  free_ptrs[24] = my_malloc(2536);  free_ptrs[25] = my_malloc(2655);  free_ptrs[26] = my_malloc(2512);
  free_ptrs[27] = my_malloc(2147);  free_ptrs[28] = my_malloc(2636);  free_ptrs[29] = my_malloc(2655);
  free_ptrs[21] = my_malloc(2171);  free_ptrs[22] = my_malloc(2381);  free_ptrs[23] = my_malloc(2496);
  free_ptrs[15] = my_malloc(2657);  free_ptrs[16] = my_malloc(2078);  free_ptrs[17] = my_malloc(2448);
  free_ptrs[39] = my_malloc(2538);  free_ptrs[40] = my_malloc(2319);  free_ptrs[41] = my_malloc(2546);
  free_ptrs[84] = my_malloc(2625);  free_ptrs[85] = my_malloc(2184);  free_ptrs[86] = my_malloc(2052);
  ptrs[23] = my_malloc(12348); dc[23] = 12360;
  free_ptrs[81] = my_malloc(2340);  free_ptrs[82] = my_malloc(2469);  free_ptrs[83] = my_malloc(2377);
  free_ptrs[69] = my_malloc(2405);  free_ptrs[70] = my_malloc(2363);  free_ptrs[71] = my_malloc(2067);
  free_ptrs[66] = my_malloc(2128);  free_ptrs[67] = my_malloc(2258);  free_ptrs[68] = my_malloc(2542);
  free_ptrs[75] = my_malloc(2437);  free_ptrs[76] = my_malloc(2688);  free_ptrs[77] = my_malloc(2301);
  free_ptrs[51] = my_malloc(2312);  free_ptrs[52] = my_malloc(2590);  free_ptrs[53] = my_malloc(2254);
  ptrs[12] = my_malloc(12443); dc[12] = 12456;
  free_ptrs[33] = my_malloc(2289);  free_ptrs[34] = my_malloc(2153);  free_ptrs[35] = my_malloc(2383);
  free_ptrs[3] = my_malloc(2048);  free_ptrs[4] = my_malloc(2227);  free_ptrs[5] = my_malloc(2636);
  free_ptrs[48] = my_malloc(2510);  free_ptrs[49] = my_malloc(2597);  free_ptrs[50] = my_malloc(2578);
  free_ptrs[45] = my_malloc(2379);  free_ptrs[46] = my_malloc(2577);  free_ptrs[47] = my_malloc(2305);
  ptrs[1] = my_malloc(12754); dc[1] = 12768;
  ptrs[29] = my_malloc(12172); dc[29] = 12184;
  free_ptrs[78] = my_malloc(2120);  free_ptrs[79] = my_malloc(2052);  free_ptrs[80] = my_malloc(2113);
  free_ptrs[30] = my_malloc(2587);  free_ptrs[31] = my_malloc(2123);  free_ptrs[32] = my_malloc(2107);
  free_ptrs[6] = my_malloc(2271);  free_ptrs[7] = my_malloc(2216);  free_ptrs[8] = my_malloc(2189);
  free_ptrs[72] = my_malloc(2664);  free_ptrs[73] = my_malloc(2077);  free_ptrs[74] = my_malloc(2259);
  free_ptrs[18] = my_malloc(2284);  free_ptrs[19] = my_malloc(2203);  free_ptrs[20] = my_malloc(2119);
  free_ptrs[0] = my_malloc(2093);  free_ptrs[1] = my_malloc(2088);  free_ptrs[2] = my_malloc(2668);
  free_ptrs[54] = my_malloc(2664);  free_ptrs[55] = my_malloc(2342);  free_ptrs[56] = my_malloc(2492);
  ptrs[25] = my_malloc(12994); dc[25] = 13008;
  ptrs[16] = my_malloc(12694); dc[16] = 12704;
  ptrs[2] = my_malloc(12224); dc[2] = 12232;
  ptrs[5] = my_malloc(12005); dc[5] = 12016;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[5]);
  ptrs[22] = my_malloc(12172); dc[22] = 12184;
  ptrs[3] = my_malloc(12504); dc[3] = 12512;
  my_free(free_ptrs[60]);
  ptrs[9] = my_malloc(12014); dc[9] = 12024;
  my_free(free_ptrs[76]);
  ptrs[4] = my_malloc(12817); dc[4] = 12832;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[84]);
  ptrs[28] = my_malloc(12450); dc[28] = 12464;
  my_free(free_ptrs[71]);
  ptrs[7] = my_malloc(12463); dc[7] = 12472;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[14]);
  ptrs[0] = my_malloc(12566); dc[0] = 12576;
  my_free(free_ptrs[70]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[36]);
  ptrs[10] = my_malloc(12335); dc[10] = 12344;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[35]);
  ptrs[17] = my_malloc(12846); dc[17] = 12856;
  my_free(free_ptrs[89]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[13]);
  ptrs[14] = my_malloc(12623); dc[14] = 12632;
  my_free(free_ptrs[65]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[61]);
  ptrs[27] = my_malloc(12483); dc[27] = 12496;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[59]);
  ptrs[8] = my_malloc(12198); dc[8] = 12208;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[50]);
  ptrs[24] = my_malloc(12305); dc[24] = 12320;
  my_free(free_ptrs[8]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[21]);
  ptrs[26] = my_malloc(12400); dc[26] = 12408;
  my_free(free_ptrs[73]);
  ptrs[6] = my_malloc(12561); dc[6] = 12576;
  my_free(free_ptrs[86]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[10]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 9, 621312);
  printf("Correct\n");
  return 0;
}
