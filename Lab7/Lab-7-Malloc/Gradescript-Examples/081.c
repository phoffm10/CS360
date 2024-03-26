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

  free_ptrs[33] = my_malloc(2573);  free_ptrs[34] = my_malloc(2685);  free_ptrs[35] = my_malloc(2397);
  free_ptrs[54] = my_malloc(2151);  free_ptrs[55] = my_malloc(2078);  free_ptrs[56] = my_malloc(2658);
  free_ptrs[27] = my_malloc(2188);  free_ptrs[28] = my_malloc(2241);  free_ptrs[29] = my_malloc(2385);
  free_ptrs[78] = my_malloc(2305);  free_ptrs[79] = my_malloc(2072);  free_ptrs[80] = my_malloc(2333);
  free_ptrs[36] = my_malloc(2061);  free_ptrs[37] = my_malloc(2086);  free_ptrs[38] = my_malloc(2251);
  ptrs[24] = my_malloc(12352); dc[24] = 12360;
  free_ptrs[87] = my_malloc(2607);  free_ptrs[88] = my_malloc(2362);  free_ptrs[89] = my_malloc(2443);
  free_ptrs[18] = my_malloc(2622);  free_ptrs[19] = my_malloc(2594);  free_ptrs[20] = my_malloc(2183);
  free_ptrs[3] = my_malloc(2060);  free_ptrs[4] = my_malloc(2373);  free_ptrs[5] = my_malloc(2690);
  ptrs[26] = my_malloc(12615); dc[26] = 12624;
  ptrs[21] = my_malloc(12014); dc[21] = 12024;
  free_ptrs[12] = my_malloc(2082);  free_ptrs[13] = my_malloc(2344);  free_ptrs[14] = my_malloc(2096);
  ptrs[18] = my_malloc(12378); dc[18] = 12392;
  ptrs[15] = my_malloc(12795); dc[15] = 12808;
  ptrs[16] = my_malloc(12797); dc[16] = 12808;
  free_ptrs[75] = my_malloc(2464);  free_ptrs[76] = my_malloc(2185);  free_ptrs[77] = my_malloc(2540);
  ptrs[1] = my_malloc(12462); dc[1] = 12472;
  free_ptrs[63] = my_malloc(2109);  free_ptrs[64] = my_malloc(2390);  free_ptrs[65] = my_malloc(2278);
  free_ptrs[51] = my_malloc(2062);  free_ptrs[52] = my_malloc(2684);  free_ptrs[53] = my_malloc(2375);
  free_ptrs[90] = my_malloc(2074);  free_ptrs[91] = my_malloc(2133);  free_ptrs[92] = my_malloc(2658);
  free_ptrs[60] = my_malloc(2285);  free_ptrs[61] = my_malloc(2234);  free_ptrs[62] = my_malloc(2557);
  ptrs[29] = my_malloc(12936); dc[29] = 12944;
  free_ptrs[57] = my_malloc(2291);  free_ptrs[58] = my_malloc(2435);  free_ptrs[59] = my_malloc(2156);
  free_ptrs[30] = my_malloc(2470);  free_ptrs[31] = my_malloc(2291);  free_ptrs[32] = my_malloc(2176);
  free_ptrs[24] = my_malloc(2236);  free_ptrs[25] = my_malloc(2675);  free_ptrs[26] = my_malloc(2077);
  free_ptrs[45] = my_malloc(2325);  free_ptrs[46] = my_malloc(2657);  free_ptrs[47] = my_malloc(2337);
  free_ptrs[0] = my_malloc(2069);  free_ptrs[1] = my_malloc(2529);  free_ptrs[2] = my_malloc(2106);
  free_ptrs[66] = my_malloc(2623);  free_ptrs[67] = my_malloc(2322);  free_ptrs[68] = my_malloc(2169);
  free_ptrs[21] = my_malloc(2550);  free_ptrs[22] = my_malloc(2326);  free_ptrs[23] = my_malloc(2427);
  free_ptrs[72] = my_malloc(2542);  free_ptrs[73] = my_malloc(2460);  free_ptrs[74] = my_malloc(2314);
  free_ptrs[81] = my_malloc(2129);  free_ptrs[82] = my_malloc(2199);  free_ptrs[83] = my_malloc(2328);
  free_ptrs[15] = my_malloc(2099);  free_ptrs[16] = my_malloc(2552);  free_ptrs[17] = my_malloc(2293);
  free_ptrs[39] = my_malloc(2244);  free_ptrs[40] = my_malloc(2126);  free_ptrs[41] = my_malloc(2266);
  free_ptrs[6] = my_malloc(2202);  free_ptrs[7] = my_malloc(2145);  free_ptrs[8] = my_malloc(2481);
  ptrs[23] = my_malloc(12183); dc[23] = 12192;
  free_ptrs[42] = my_malloc(2138);  free_ptrs[43] = my_malloc(2145);  free_ptrs[44] = my_malloc(2119);
  ptrs[10] = my_malloc(12894); dc[10] = 12904;
  free_ptrs[69] = my_malloc(2438);  free_ptrs[70] = my_malloc(2332);  free_ptrs[71] = my_malloc(2130);
  ptrs[9] = my_malloc(12058); dc[9] = 12072;
  free_ptrs[84] = my_malloc(2558);  free_ptrs[85] = my_malloc(2184);  free_ptrs[86] = my_malloc(2694);
  ptrs[4] = my_malloc(12145); dc[4] = 12160;
  ptrs[20] = my_malloc(12169); dc[20] = 12184;
  free_ptrs[9] = my_malloc(2049);  free_ptrs[10] = my_malloc(2271);  free_ptrs[11] = my_malloc(2194);
  free_ptrs[48] = my_malloc(2552);  free_ptrs[49] = my_malloc(2541);  free_ptrs[50] = my_malloc(2084);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[34]);
  ptrs[30] = my_malloc(12516); dc[30] = 12528;
  my_free(free_ptrs[69]);
  ptrs[11] = my_malloc(12842); dc[11] = 12856;
  my_free(free_ptrs[40]);
  my_free(free_ptrs[51]);
  ptrs[14] = my_malloc(12590); dc[14] = 12600;
  my_free(free_ptrs[70]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[22]);
  ptrs[7] = my_malloc(12755); dc[7] = 12768;
  my_free(free_ptrs[33]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[92]);
  my_free(free_ptrs[32]);
  ptrs[5] = my_malloc(12968); dc[5] = 12976;
  ptrs[25] = my_malloc(12214); dc[25] = 12224;
  my_free(free_ptrs[62]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[50]);
  ptrs[0] = my_malloc(12709); dc[0] = 12720;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[76]);
  ptrs[3] = my_malloc(12283); dc[3] = 12296;
  ptrs[19] = my_malloc(12385); dc[19] = 12400;
  my_free(free_ptrs[15]);
  ptrs[27] = my_malloc(12839); dc[27] = 12848;
  my_free(free_ptrs[25]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[67]);
  ptrs[6] = my_malloc(12985); dc[6] = 13000;
  my_free(free_ptrs[55]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[56]);
  ptrs[13] = my_malloc(12657); dc[13] = 12672;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[8]);
  ptrs[12] = my_malloc(12930); dc[12] = 12944;
  my_free(free_ptrs[57]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[87]);
  ptrs[2] = my_malloc(12087); dc[2] = 12096;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[43]);
  ptrs[17] = my_malloc(12073); dc[17] = 12088;
  my_free(free_ptrs[41]);
  ptrs[22] = my_malloc(12683); dc[22] = 12696;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[21]);
  ptrs[8] = my_malloc(12494); dc[8] = 12504;
  my_free(free_ptrs[17]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[74]);
  ptrs[28] = my_malloc(12065); dc[28] = 12080;
  my_free(free_ptrs[83]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[77]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 10, 642192);
  printf("Correct\n");
  return 0;
}
