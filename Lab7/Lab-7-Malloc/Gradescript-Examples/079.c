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

  free_ptrs[75] = my_malloc(2351);  free_ptrs[76] = my_malloc(2151);  free_ptrs[77] = my_malloc(2413);
  free_ptrs[21] = my_malloc(2235);  free_ptrs[22] = my_malloc(2448);  free_ptrs[23] = my_malloc(2295);
  ptrs[14] = my_malloc(12261); dc[14] = 12272;
  free_ptrs[33] = my_malloc(2431);  free_ptrs[34] = my_malloc(2239);  free_ptrs[35] = my_malloc(2486);
  free_ptrs[0] = my_malloc(2286);  free_ptrs[1] = my_malloc(2634);  free_ptrs[2] = my_malloc(2453);
  free_ptrs[72] = my_malloc(2078);  free_ptrs[73] = my_malloc(2138);  free_ptrs[74] = my_malloc(2566);
  free_ptrs[63] = my_malloc(2226);  free_ptrs[64] = my_malloc(2330);  free_ptrs[65] = my_malloc(2456);
  ptrs[16] = my_malloc(12044); dc[16] = 12056;
  free_ptrs[78] = my_malloc(2130);  free_ptrs[79] = my_malloc(2563);  free_ptrs[80] = my_malloc(2226);
  free_ptrs[66] = my_malloc(2551);  free_ptrs[67] = my_malloc(2153);  free_ptrs[68] = my_malloc(2168);
  ptrs[9] = my_malloc(12737); dc[9] = 12752;
  free_ptrs[60] = my_malloc(2274);  free_ptrs[61] = my_malloc(2659);  free_ptrs[62] = my_malloc(2315);
  free_ptrs[45] = my_malloc(2248);  free_ptrs[46] = my_malloc(2252);  free_ptrs[47] = my_malloc(2113);
  ptrs[23] = my_malloc(12054); dc[23] = 12064;
  free_ptrs[3] = my_malloc(2100);  free_ptrs[4] = my_malloc(2080);  free_ptrs[5] = my_malloc(2485);
  ptrs[1] = my_malloc(12485); dc[1] = 12496;
  ptrs[7] = my_malloc(12914); dc[7] = 12928;
  ptrs[24] = my_malloc(12951); dc[24] = 12960;
  free_ptrs[51] = my_malloc(2420);  free_ptrs[52] = my_malloc(2118);  free_ptrs[53] = my_malloc(2691);
  free_ptrs[48] = my_malloc(2348);  free_ptrs[49] = my_malloc(2127);  free_ptrs[50] = my_malloc(2635);
  ptrs[25] = my_malloc(12885); dc[25] = 12896;
  ptrs[0] = my_malloc(12004); dc[0] = 12016;
  free_ptrs[15] = my_malloc(2557);  free_ptrs[16] = my_malloc(2316);  free_ptrs[17] = my_malloc(2668);
  free_ptrs[69] = my_malloc(2587);  free_ptrs[70] = my_malloc(2123);  free_ptrs[71] = my_malloc(2075);
  ptrs[18] = my_malloc(12945); dc[18] = 12960;
  free_ptrs[57] = my_malloc(2370);  free_ptrs[58] = my_malloc(2235);  free_ptrs[59] = my_malloc(2387);
  ptrs[26] = my_malloc(12878); dc[26] = 12888;
  free_ptrs[12] = my_malloc(2248);  free_ptrs[13] = my_malloc(2512);  free_ptrs[14] = my_malloc(2159);
  free_ptrs[6] = my_malloc(2434);  free_ptrs[7] = my_malloc(2071);  free_ptrs[8] = my_malloc(2321);
  free_ptrs[30] = my_malloc(2212);  free_ptrs[31] = my_malloc(2568);  free_ptrs[32] = my_malloc(2303);
  free_ptrs[18] = my_malloc(2183);  free_ptrs[19] = my_malloc(2630);  free_ptrs[20] = my_malloc(2515);
  ptrs[21] = my_malloc(12013); dc[21] = 12024;
  free_ptrs[27] = my_malloc(2658);  free_ptrs[28] = my_malloc(2297);  free_ptrs[29] = my_malloc(2651);
  free_ptrs[9] = my_malloc(2448);  free_ptrs[10] = my_malloc(2355);  free_ptrs[11] = my_malloc(2515);
  free_ptrs[36] = my_malloc(2160);  free_ptrs[37] = my_malloc(2213);  free_ptrs[38] = my_malloc(2373);
  free_ptrs[24] = my_malloc(2514);  free_ptrs[25] = my_malloc(2505);  free_ptrs[26] = my_malloc(2512);
  free_ptrs[54] = my_malloc(2528);  free_ptrs[55] = my_malloc(2354);  free_ptrs[56] = my_malloc(2676);
  free_ptrs[39] = my_malloc(2593);  free_ptrs[40] = my_malloc(2224);  free_ptrs[41] = my_malloc(2557);
  ptrs[10] = my_malloc(12933); dc[10] = 12944;
  free_ptrs[42] = my_malloc(2094);  free_ptrs[43] = my_malloc(2357);  free_ptrs[44] = my_malloc(2176);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[39]);
  ptrs[13] = my_malloc(12720); dc[13] = 12728;
  my_free(free_ptrs[19]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[30]);
  ptrs[22] = my_malloc(12434); dc[22] = 12448;
  my_free(free_ptrs[20]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[21]);
  ptrs[4] = my_malloc(12280); dc[4] = 12288;
  my_free(free_ptrs[70]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[8]);
  ptrs[6] = my_malloc(12056); dc[6] = 12064;
  my_free(free_ptrs[48]);
  my_free(free_ptrs[17]);
  ptrs[20] = my_malloc(12496); dc[20] = 12504;
  my_free(free_ptrs[58]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[69]);
  ptrs[17] = my_malloc(12240); dc[17] = 12248;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[41]);
  ptrs[15] = my_malloc(12530); dc[15] = 12544;
  ptrs[8] = my_malloc(12093); dc[8] = 12104;
  my_free(free_ptrs[67]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[9]);
  ptrs[12] = my_malloc(12985); dc[12] = 13000;
  ptrs[11] = my_malloc(12169); dc[11] = 12184;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[56]);
  ptrs[2] = my_malloc(12726); dc[2] = 12736;
  my_free(free_ptrs[35]);
  ptrs[5] = my_malloc(12559); dc[5] = 12568;
  my_free(free_ptrs[34]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[52]);
  ptrs[19] = my_malloc(12312); dc[19] = 12320;
  my_free(free_ptrs[72]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[16]);
  ptrs[3] = my_malloc(12666); dc[3] = 12680;
  my_free(free_ptrs[22]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[29]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 11, 558856);
  printf("Correct\n");
  return 0;
}
