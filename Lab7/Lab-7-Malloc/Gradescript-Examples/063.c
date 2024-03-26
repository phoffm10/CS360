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

  ptrs[17] = my_malloc(12679); dc[17] = 12688;
  free_ptrs[30] = my_malloc(2380);  free_ptrs[31] = my_malloc(2548);  free_ptrs[32] = my_malloc(2295);
  free_ptrs[84] = my_malloc(2245);  free_ptrs[85] = my_malloc(2431);  free_ptrs[86] = my_malloc(2498);
  free_ptrs[81] = my_malloc(2468);  free_ptrs[82] = my_malloc(2164);  free_ptrs[83] = my_malloc(2215);
  free_ptrs[51] = my_malloc(2347);  free_ptrs[52] = my_malloc(2093);  free_ptrs[53] = my_malloc(2108);
  free_ptrs[3] = my_malloc(2580);  free_ptrs[4] = my_malloc(2387);  free_ptrs[5] = my_malloc(2067);
  free_ptrs[48] = my_malloc(2226);  free_ptrs[49] = my_malloc(2235);  free_ptrs[50] = my_malloc(2607);
  ptrs[8] = my_malloc(12247); dc[8] = 12256;
  free_ptrs[66] = my_malloc(2375);  free_ptrs[67] = my_malloc(2297);  free_ptrs[68] = my_malloc(2164);
  free_ptrs[42] = my_malloc(2340);  free_ptrs[43] = my_malloc(2267);  free_ptrs[44] = my_malloc(2568);
  free_ptrs[75] = my_malloc(2471);  free_ptrs[76] = my_malloc(2460);  free_ptrs[77] = my_malloc(2283);
  free_ptrs[15] = my_malloc(2617);  free_ptrs[16] = my_malloc(2683);  free_ptrs[17] = my_malloc(2689);
  ptrs[6] = my_malloc(12138); dc[6] = 12152;
  free_ptrs[12] = my_malloc(2422);  free_ptrs[13] = my_malloc(2685);  free_ptrs[14] = my_malloc(2663);
  ptrs[7] = my_malloc(12304); dc[7] = 12312;
  free_ptrs[27] = my_malloc(2399);  free_ptrs[28] = my_malloc(2534);  free_ptrs[29] = my_malloc(2693);
  free_ptrs[36] = my_malloc(2364);  free_ptrs[37] = my_malloc(2141);  free_ptrs[38] = my_malloc(2393);
  free_ptrs[69] = my_malloc(2086);  free_ptrs[70] = my_malloc(2542);  free_ptrs[71] = my_malloc(2410);
  free_ptrs[45] = my_malloc(2556);  free_ptrs[46] = my_malloc(2194);  free_ptrs[47] = my_malloc(2318);
  free_ptrs[39] = my_malloc(2624);  free_ptrs[40] = my_malloc(2197);  free_ptrs[41] = my_malloc(2173);
  ptrs[0] = my_malloc(12919); dc[0] = 12928;
  free_ptrs[9] = my_malloc(2669);  free_ptrs[10] = my_malloc(2688);  free_ptrs[11] = my_malloc(2076);
  free_ptrs[54] = my_malloc(2637);  free_ptrs[55] = my_malloc(2427);  free_ptrs[56] = my_malloc(2460);
  free_ptrs[21] = my_malloc(2368);  free_ptrs[22] = my_malloc(2311);  free_ptrs[23] = my_malloc(2079);
  free_ptrs[72] = my_malloc(2626);  free_ptrs[73] = my_malloc(2446);  free_ptrs[74] = my_malloc(2152);
  ptrs[5] = my_malloc(12766); dc[5] = 12776;
  free_ptrs[78] = my_malloc(2215);  free_ptrs[79] = my_malloc(2194);  free_ptrs[80] = my_malloc(2474);
  free_ptrs[87] = my_malloc(2383);  free_ptrs[88] = my_malloc(2095);  free_ptrs[89] = my_malloc(2551);
  free_ptrs[57] = my_malloc(2571);  free_ptrs[58] = my_malloc(2075);  free_ptrs[59] = my_malloc(2548);
  free_ptrs[63] = my_malloc(2673);  free_ptrs[64] = my_malloc(2458);  free_ptrs[65] = my_malloc(2221);
  ptrs[13] = my_malloc(12847); dc[13] = 12856;
  ptrs[3] = my_malloc(12769); dc[3] = 12784;
  free_ptrs[60] = my_malloc(2366);  free_ptrs[61] = my_malloc(2507);  free_ptrs[62] = my_malloc(2286);
  free_ptrs[33] = my_malloc(2500);  free_ptrs[34] = my_malloc(2324);  free_ptrs[35] = my_malloc(2073);
  ptrs[14] = my_malloc(12600); dc[14] = 12608;
  ptrs[12] = my_malloc(12388); dc[12] = 12400;
  ptrs[28] = my_malloc(12179); dc[28] = 12192;
  ptrs[1] = my_malloc(12731); dc[1] = 12744;
  free_ptrs[0] = my_malloc(2397);  free_ptrs[1] = my_malloc(2599);  free_ptrs[2] = my_malloc(2438);
  free_ptrs[90] = my_malloc(2201);  free_ptrs[91] = my_malloc(2108);  free_ptrs[92] = my_malloc(2546);
  ptrs[4] = my_malloc(12682); dc[4] = 12696;
  free_ptrs[24] = my_malloc(2506);  free_ptrs[25] = my_malloc(2159);  free_ptrs[26] = my_malloc(2329);
  free_ptrs[6] = my_malloc(2441);  free_ptrs[7] = my_malloc(2130);  free_ptrs[8] = my_malloc(2099);
  ptrs[30] = my_malloc(12438); dc[30] = 12448;
  ptrs[23] = my_malloc(12477); dc[23] = 12488;
  ptrs[2] = my_malloc(12233); dc[2] = 12248;
  free_ptrs[18] = my_malloc(2126);  free_ptrs[19] = my_malloc(2244);  free_ptrs[20] = my_malloc(2683);
  ptrs[15] = my_malloc(12577); dc[15] = 12592;
  my_free(free_ptrs[92]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[10]);
  ptrs[16] = my_malloc(12447); dc[16] = 12456;
  my_free(free_ptrs[19]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[87]);
  ptrs[29] = my_malloc(12005); dc[29] = 12016;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[73]);
  ptrs[10] = my_malloc(12944); dc[10] = 12952;
  ptrs[26] = my_malloc(12137); dc[26] = 12152;
  my_free(free_ptrs[74]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[50]);
  ptrs[24] = my_malloc(12706); dc[24] = 12720;
  my_free(free_ptrs[30]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[54]);
  ptrs[21] = my_malloc(12292); dc[21] = 12304;
  my_free(free_ptrs[1]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[29]);
  ptrs[20] = my_malloc(12066); dc[20] = 12080;
  my_free(free_ptrs[58]);
  my_free(free_ptrs[8]);
  ptrs[11] = my_malloc(12368); dc[11] = 12376;
  my_free(free_ptrs[70]);
  ptrs[18] = my_malloc(12451); dc[18] = 12464;
  my_free(free_ptrs[59]);
  my_free(free_ptrs[5]);
  ptrs[19] = my_malloc(12942); dc[19] = 12952;
  my_free(free_ptrs[22]);
  ptrs[22] = my_malloc(12421); dc[22] = 12432;
  my_free(free_ptrs[28]);
  ptrs[25] = my_malloc(12675); dc[25] = 12688;
  my_free(free_ptrs[25]);
  my_free(free_ptrs[17]);
  ptrs[9] = my_malloc(12335); dc[9] = 12344;
  ptrs[27] = my_malloc(12084); dc[27] = 12096;
  my_free(free_ptrs[64]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[80]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 10, 641152);
  printf("Correct\n");
  return 0;
}
