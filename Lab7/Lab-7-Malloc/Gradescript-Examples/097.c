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

  ptrs[25] = my_malloc(12423); dc[25] = 12432;
  free_ptrs[84] = my_malloc(2159);  free_ptrs[85] = my_malloc(2209);  free_ptrs[86] = my_malloc(2530);
  ptrs[13] = my_malloc(12531); dc[13] = 12544;
  free_ptrs[18] = my_malloc(2546);  free_ptrs[19] = my_malloc(2168);  free_ptrs[20] = my_malloc(2415);
  ptrs[23] = my_malloc(12761); dc[23] = 12776;
  free_ptrs[6] = my_malloc(2387);  free_ptrs[7] = my_malloc(2218);  free_ptrs[8] = my_malloc(2271);
  free_ptrs[45] = my_malloc(2116);  free_ptrs[46] = my_malloc(2580);  free_ptrs[47] = my_malloc(2260);
  free_ptrs[69] = my_malloc(2416);  free_ptrs[70] = my_malloc(2296);  free_ptrs[71] = my_malloc(2464);
  free_ptrs[39] = my_malloc(2212);  free_ptrs[40] = my_malloc(2401);  free_ptrs[41] = my_malloc(2069);
  free_ptrs[12] = my_malloc(2548);  free_ptrs[13] = my_malloc(2405);  free_ptrs[14] = my_malloc(2697);
  free_ptrs[54] = my_malloc(2671);  free_ptrs[55] = my_malloc(2443);  free_ptrs[56] = my_malloc(2526);
  free_ptrs[33] = my_malloc(2296);  free_ptrs[34] = my_malloc(2454);  free_ptrs[35] = my_malloc(2477);
  free_ptrs[24] = my_malloc(2116);  free_ptrs[25] = my_malloc(2245);  free_ptrs[26] = my_malloc(2347);
  free_ptrs[27] = my_malloc(2213);  free_ptrs[28] = my_malloc(2066);  free_ptrs[29] = my_malloc(2199);
  free_ptrs[48] = my_malloc(2600);  free_ptrs[49] = my_malloc(2539);  free_ptrs[50] = my_malloc(2631);
  free_ptrs[42] = my_malloc(2514);  free_ptrs[43] = my_malloc(2313);  free_ptrs[44] = my_malloc(2672);
  ptrs[10] = my_malloc(12532); dc[10] = 12544;
  free_ptrs[15] = my_malloc(2343);  free_ptrs[16] = my_malloc(2183);  free_ptrs[17] = my_malloc(2153);
  free_ptrs[72] = my_malloc(2558);  free_ptrs[73] = my_malloc(2286);  free_ptrs[74] = my_malloc(2430);
  free_ptrs[81] = my_malloc(2440);  free_ptrs[82] = my_malloc(2446);  free_ptrs[83] = my_malloc(2307);
  ptrs[14] = my_malloc(12252); dc[14] = 12264;
  ptrs[20] = my_malloc(12246); dc[20] = 12256;
  free_ptrs[3] = my_malloc(2490);  free_ptrs[4] = my_malloc(2609);  free_ptrs[5] = my_malloc(2449);
  free_ptrs[87] = my_malloc(2283);  free_ptrs[88] = my_malloc(2603);  free_ptrs[89] = my_malloc(2347);
  free_ptrs[63] = my_malloc(2127);  free_ptrs[64] = my_malloc(2112);  free_ptrs[65] = my_malloc(2637);
  free_ptrs[75] = my_malloc(2673);  free_ptrs[76] = my_malloc(2400);  free_ptrs[77] = my_malloc(2433);
  ptrs[2] = my_malloc(12581); dc[2] = 12592;
  ptrs[5] = my_malloc(12114); dc[5] = 12128;
  ptrs[12] = my_malloc(12528); dc[12] = 12536;
  free_ptrs[21] = my_malloc(2098);  free_ptrs[22] = my_malloc(2525);  free_ptrs[23] = my_malloc(2339);
  free_ptrs[90] = my_malloc(2143);  free_ptrs[91] = my_malloc(2092);  free_ptrs[92] = my_malloc(2172);
  free_ptrs[0] = my_malloc(2081);  free_ptrs[1] = my_malloc(2529);  free_ptrs[2] = my_malloc(2208);
  ptrs[6] = my_malloc(12902); dc[6] = 12912;
  free_ptrs[57] = my_malloc(2131);  free_ptrs[58] = my_malloc(2669);  free_ptrs[59] = my_malloc(2174);
  free_ptrs[60] = my_malloc(2242);  free_ptrs[61] = my_malloc(2329);  free_ptrs[62] = my_malloc(2494);
  ptrs[3] = my_malloc(12829); dc[3] = 12840;
  ptrs[15] = my_malloc(12749); dc[15] = 12760;
  free_ptrs[66] = my_malloc(2105);  free_ptrs[67] = my_malloc(2591);  free_ptrs[68] = my_malloc(2080);
  free_ptrs[78] = my_malloc(2231);  free_ptrs[79] = my_malloc(2518);  free_ptrs[80] = my_malloc(2238);
  free_ptrs[51] = my_malloc(2673);  free_ptrs[52] = my_malloc(2133);  free_ptrs[53] = my_malloc(2646);
  free_ptrs[30] = my_malloc(2304);  free_ptrs[31] = my_malloc(2242);  free_ptrs[32] = my_malloc(2439);
  free_ptrs[36] = my_malloc(2282);  free_ptrs[37] = my_malloc(2437);  free_ptrs[38] = my_malloc(2093);
  ptrs[11] = my_malloc(12292); dc[11] = 12304;
  ptrs[24] = my_malloc(12598); dc[24] = 12608;
  free_ptrs[9] = my_malloc(2263);  free_ptrs[10] = my_malloc(2078);  free_ptrs[11] = my_malloc(2178);
  ptrs[27] = my_malloc(12344); dc[27] = 12352;
  ptrs[18] = my_malloc(12519); dc[18] = 12528;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[92]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[3]);
  ptrs[9] = my_malloc(12459); dc[9] = 12472;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[76]);
  ptrs[22] = my_malloc(12697); dc[22] = 12712;
  my_free(free_ptrs[54]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[48]);
  ptrs[4] = my_malloc(12742); dc[4] = 12752;
  my_free(free_ptrs[47]);
  ptrs[29] = my_malloc(12385); dc[29] = 12400;
  my_free(free_ptrs[13]);
  ptrs[17] = my_malloc(12635); dc[17] = 12648;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[20]);
  ptrs[16] = my_malloc(12747); dc[16] = 12760;
  my_free(free_ptrs[72]);
  ptrs[21] = my_malloc(12736); dc[21] = 12744;
  my_free(free_ptrs[46]);
  my_free(free_ptrs[66]);
  ptrs[8] = my_malloc(12339); dc[8] = 12352;
  my_free(free_ptrs[50]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[38]);
  ptrs[26] = my_malloc(12357); dc[26] = 12368;
  ptrs[7] = my_malloc(12364); dc[7] = 12376;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[29]);
  ptrs[30] = my_malloc(12650); dc[30] = 12664;
  my_free(free_ptrs[53]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[28]);
  ptrs[0] = my_malloc(12795); dc[0] = 12808;
  my_free(free_ptrs[82]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[80]);
  ptrs[19] = my_malloc(12402); dc[19] = 12416;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[58]);
  ptrs[28] = my_malloc(12871); dc[28] = 12880;
  my_free(free_ptrs[36]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[43]);
  ptrs[1] = my_malloc(12567); dc[1] = 12576;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[61]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 9, 643256);
  printf("Correct\n");
  return 0;
}
