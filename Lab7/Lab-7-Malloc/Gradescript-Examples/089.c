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
  int *ptrs[29];
  int *free_ptrs[87];
  int dc[29];

  ptrs[10] = my_malloc(12291); dc[10] = 12304;
  free_ptrs[15] = my_malloc(2534);  free_ptrs[16] = my_malloc(2609);  free_ptrs[17] = my_malloc(2192);
  ptrs[1] = my_malloc(12347); dc[1] = 12360;
  free_ptrs[30] = my_malloc(2683);  free_ptrs[31] = my_malloc(2635);  free_ptrs[32] = my_malloc(2451);
  free_ptrs[75] = my_malloc(2207);  free_ptrs[76] = my_malloc(2595);  free_ptrs[77] = my_malloc(2677);
  ptrs[7] = my_malloc(12608); dc[7] = 12616;
  free_ptrs[57] = my_malloc(2501);  free_ptrs[58] = my_malloc(2189);  free_ptrs[59] = my_malloc(2344);
  free_ptrs[39] = my_malloc(2333);  free_ptrs[40] = my_malloc(2569);  free_ptrs[41] = my_malloc(2467);
  ptrs[9] = my_malloc(12015); dc[9] = 12024;
  ptrs[12] = my_malloc(12303); dc[12] = 12312;
  free_ptrs[81] = my_malloc(2619);  free_ptrs[82] = my_malloc(2159);  free_ptrs[83] = my_malloc(2122);
  free_ptrs[0] = my_malloc(2241);  free_ptrs[1] = my_malloc(2429);  free_ptrs[2] = my_malloc(2314);
  free_ptrs[45] = my_malloc(2547);  free_ptrs[46] = my_malloc(2466);  free_ptrs[47] = my_malloc(2216);
  ptrs[0] = my_malloc(12178); dc[0] = 12192;
  free_ptrs[9] = my_malloc(2099);  free_ptrs[10] = my_malloc(2446);  free_ptrs[11] = my_malloc(2436);
  free_ptrs[60] = my_malloc(2101);  free_ptrs[61] = my_malloc(2365);  free_ptrs[62] = my_malloc(2092);
  free_ptrs[6] = my_malloc(2425);  free_ptrs[7] = my_malloc(2571);  free_ptrs[8] = my_malloc(2675);
  free_ptrs[72] = my_malloc(2458);  free_ptrs[73] = my_malloc(2648);  free_ptrs[74] = my_malloc(2687);
  ptrs[27] = my_malloc(12492); dc[27] = 12504;
  free_ptrs[63] = my_malloc(2296);  free_ptrs[64] = my_malloc(2637);  free_ptrs[65] = my_malloc(2460);
  free_ptrs[66] = my_malloc(2156);  free_ptrs[67] = my_malloc(2399);  free_ptrs[68] = my_malloc(2554);
  ptrs[11] = my_malloc(12911); dc[11] = 12920;
  ptrs[24] = my_malloc(12413); dc[24] = 12424;
  free_ptrs[69] = my_malloc(2359);  free_ptrs[70] = my_malloc(2525);  free_ptrs[71] = my_malloc(2357);
  free_ptrs[51] = my_malloc(2321);  free_ptrs[52] = my_malloc(2285);  free_ptrs[53] = my_malloc(2145);
  ptrs[18] = my_malloc(12895); dc[18] = 12904;
  ptrs[14] = my_malloc(12827); dc[14] = 12840;
  free_ptrs[21] = my_malloc(2129);  free_ptrs[22] = my_malloc(2248);  free_ptrs[23] = my_malloc(2483);
  free_ptrs[42] = my_malloc(2540);  free_ptrs[43] = my_malloc(2392);  free_ptrs[44] = my_malloc(2507);
  free_ptrs[36] = my_malloc(2573);  free_ptrs[37] = my_malloc(2665);  free_ptrs[38] = my_malloc(2690);
  ptrs[20] = my_malloc(12126); dc[20] = 12136;
  free_ptrs[84] = my_malloc(2234);  free_ptrs[85] = my_malloc(2122);  free_ptrs[86] = my_malloc(2211);
  free_ptrs[27] = my_malloc(2363);  free_ptrs[28] = my_malloc(2696);  free_ptrs[29] = my_malloc(2303);
  free_ptrs[18] = my_malloc(2153);  free_ptrs[19] = my_malloc(2591);  free_ptrs[20] = my_malloc(2239);
  ptrs[6] = my_malloc(12926); dc[6] = 12936;
  free_ptrs[24] = my_malloc(2330);  free_ptrs[25] = my_malloc(2260);  free_ptrs[26] = my_malloc(2137);
  free_ptrs[54] = my_malloc(2528);  free_ptrs[55] = my_malloc(2101);  free_ptrs[56] = my_malloc(2322);
  free_ptrs[12] = my_malloc(2229);  free_ptrs[13] = my_malloc(2455);  free_ptrs[14] = my_malloc(2601);
  ptrs[16] = my_malloc(12210); dc[16] = 12224;
  free_ptrs[48] = my_malloc(2123);  free_ptrs[49] = my_malloc(2616);  free_ptrs[50] = my_malloc(2645);
  free_ptrs[78] = my_malloc(2506);  free_ptrs[79] = my_malloc(2637);  free_ptrs[80] = my_malloc(2472);
  free_ptrs[33] = my_malloc(2316);  free_ptrs[34] = my_malloc(2646);  free_ptrs[35] = my_malloc(2358);
  free_ptrs[3] = my_malloc(2417);  free_ptrs[4] = my_malloc(2442);  free_ptrs[5] = my_malloc(2525);
  ptrs[4] = my_malloc(12822); dc[4] = 12832;
  my_free(free_ptrs[67]);
  ptrs[3] = my_malloc(12960); dc[3] = 12968;
  my_free(free_ptrs[10]);
  ptrs[23] = my_malloc(12828); dc[23] = 12840;
  my_free(free_ptrs[30]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[54]);
  ptrs[21] = my_malloc(12611); dc[21] = 12624;
  my_free(free_ptrs[68]);
  my_free(free_ptrs[47]);
  ptrs[22] = my_malloc(12576); dc[22] = 12584;
  my_free(free_ptrs[70]);
  ptrs[28] = my_malloc(12062); dc[28] = 12072;
  my_free(free_ptrs[53]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[79]);
  ptrs[5] = my_malloc(12069); dc[5] = 12080;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[40]);
  ptrs[19] = my_malloc(12398); dc[19] = 12408;
  my_free(free_ptrs[71]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[17]);
  ptrs[17] = my_malloc(12886); dc[17] = 12896;
  ptrs[2] = my_malloc(12836); dc[2] = 12848;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[8]);
  ptrs[26] = my_malloc(12244); dc[26] = 12256;
  my_free(free_ptrs[34]);
  my_free(free_ptrs[61]);
  ptrs[15] = my_malloc(12176); dc[15] = 12184;
  my_free(free_ptrs[24]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[12]);
  ptrs[8] = my_malloc(12091); dc[8] = 12104;
  my_free(free_ptrs[81]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[49]);
  ptrs[25] = my_malloc(12915); dc[25] = 12928;
  my_free(free_ptrs[14]);
  ptrs[13] = my_malloc(12342); dc[13] = 12352;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[86]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 11, 600240);
  printf("Correct\n");
  return 0;
}
