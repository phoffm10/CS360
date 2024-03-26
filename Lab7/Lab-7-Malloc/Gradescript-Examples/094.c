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

  free_ptrs[69] = my_malloc(2076);  free_ptrs[70] = my_malloc(2180);  free_ptrs[71] = my_malloc(2232);
  free_ptrs[48] = my_malloc(2577);  free_ptrs[49] = my_malloc(2182);  free_ptrs[50] = my_malloc(2401);
  free_ptrs[15] = my_malloc(2482);  free_ptrs[16] = my_malloc(2509);  free_ptrs[17] = my_malloc(2480);
  free_ptrs[27] = my_malloc(2087);  free_ptrs[28] = my_malloc(2244);  free_ptrs[29] = my_malloc(2573);
  ptrs[9] = my_malloc(12978); dc[9] = 12992;
  ptrs[26] = my_malloc(12103); dc[26] = 12112;
  ptrs[5] = my_malloc(12648); dc[5] = 12656;
  ptrs[19] = my_malloc(12617); dc[19] = 12632;
  free_ptrs[60] = my_malloc(2358);  free_ptrs[61] = my_malloc(2625);  free_ptrs[62] = my_malloc(2554);
  free_ptrs[0] = my_malloc(2608);  free_ptrs[1] = my_malloc(2591);  free_ptrs[2] = my_malloc(2633);
  free_ptrs[63] = my_malloc(2338);  free_ptrs[64] = my_malloc(2671);  free_ptrs[65] = my_malloc(2122);
  free_ptrs[51] = my_malloc(2280);  free_ptrs[52] = my_malloc(2064);  free_ptrs[53] = my_malloc(2050);
  free_ptrs[39] = my_malloc(2102);  free_ptrs[40] = my_malloc(2080);  free_ptrs[41] = my_malloc(2598);
  free_ptrs[18] = my_malloc(2116);  free_ptrs[19] = my_malloc(2660);  free_ptrs[20] = my_malloc(2304);
  free_ptrs[45] = my_malloc(2067);  free_ptrs[46] = my_malloc(2149);  free_ptrs[47] = my_malloc(2421);
  free_ptrs[54] = my_malloc(2118);  free_ptrs[55] = my_malloc(2555);  free_ptrs[56] = my_malloc(2216);
  ptrs[23] = my_malloc(12567); dc[23] = 12576;
  free_ptrs[84] = my_malloc(2385);  free_ptrs[85] = my_malloc(2392);  free_ptrs[86] = my_malloc(2616);
  free_ptrs[6] = my_malloc(2506);  free_ptrs[7] = my_malloc(2050);  free_ptrs[8] = my_malloc(2309);
  free_ptrs[12] = my_malloc(2246);  free_ptrs[13] = my_malloc(2132);  free_ptrs[14] = my_malloc(2362);
  ptrs[12] = my_malloc(12786); dc[12] = 12800;
  free_ptrs[21] = my_malloc(2203);  free_ptrs[22] = my_malloc(2442);  free_ptrs[23] = my_malloc(2152);
  free_ptrs[72] = my_malloc(2351);  free_ptrs[73] = my_malloc(2384);  free_ptrs[74] = my_malloc(2656);
  free_ptrs[57] = my_malloc(2624);  free_ptrs[58] = my_malloc(2635);  free_ptrs[59] = my_malloc(2153);
  free_ptrs[30] = my_malloc(2526);  free_ptrs[31] = my_malloc(2568);  free_ptrs[32] = my_malloc(2559);
  free_ptrs[3] = my_malloc(2099);  free_ptrs[4] = my_malloc(2284);  free_ptrs[5] = my_malloc(2333);
  ptrs[25] = my_malloc(12254); dc[25] = 12264;
  free_ptrs[66] = my_malloc(2626);  free_ptrs[67] = my_malloc(2255);  free_ptrs[68] = my_malloc(2308);
  free_ptrs[24] = my_malloc(2683);  free_ptrs[25] = my_malloc(2340);  free_ptrs[26] = my_malloc(2449);
  free_ptrs[33] = my_malloc(2415);  free_ptrs[34] = my_malloc(2101);  free_ptrs[35] = my_malloc(2217);
  ptrs[11] = my_malloc(12282); dc[11] = 12296;
  ptrs[27] = my_malloc(12943); dc[27] = 12952;
  ptrs[17] = my_malloc(12385); dc[17] = 12400;
  free_ptrs[78] = my_malloc(2316);  free_ptrs[79] = my_malloc(2311);  free_ptrs[80] = my_malloc(2072);
  ptrs[29] = my_malloc(12488); dc[29] = 12496;
  ptrs[8] = my_malloc(12590); dc[8] = 12600;
  free_ptrs[75] = my_malloc(2506);  free_ptrs[76] = my_malloc(2674);  free_ptrs[77] = my_malloc(2161);
  free_ptrs[81] = my_malloc(2598);  free_ptrs[82] = my_malloc(2117);  free_ptrs[83] = my_malloc(2441);
  free_ptrs[9] = my_malloc(2659);  free_ptrs[10] = my_malloc(2537);  free_ptrs[11] = my_malloc(2417);
  free_ptrs[36] = my_malloc(2084);  free_ptrs[37] = my_malloc(2419);  free_ptrs[38] = my_malloc(2074);
  free_ptrs[87] = my_malloc(2486);  free_ptrs[88] = my_malloc(2437);  free_ptrs[89] = my_malloc(2566);
  free_ptrs[42] = my_malloc(2399);  free_ptrs[43] = my_malloc(2078);  free_ptrs[44] = my_malloc(2423);
  ptrs[7] = my_malloc(12779); dc[7] = 12792;
  my_free(free_ptrs[30]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[26]);
  ptrs[0] = my_malloc(12589); dc[0] = 12600;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[41]);
  ptrs[16] = my_malloc(12117); dc[16] = 12128;
  my_free(free_ptrs[31]);
  ptrs[20] = my_malloc(12441); dc[20] = 12456;
  my_free(free_ptrs[24]);
  ptrs[22] = my_malloc(12323); dc[22] = 12336;
  my_free(free_ptrs[5]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[76]);
  ptrs[21] = my_malloc(12910); dc[21] = 12920;
  my_free(free_ptrs[67]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[72]);
  ptrs[13] = my_malloc(12801); dc[13] = 12816;
  my_free(free_ptrs[61]);
  my_free(free_ptrs[50]);
  ptrs[6] = my_malloc(12361); dc[6] = 12376;
  my_free(free_ptrs[65]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[9]);
  ptrs[24] = my_malloc(12320); dc[24] = 12328;
  my_free(free_ptrs[85]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[75]);
  ptrs[18] = my_malloc(12194); dc[18] = 12208;
  my_free(free_ptrs[79]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[42]);
  ptrs[10] = my_malloc(12118); dc[10] = 12128;
  ptrs[3] = my_malloc(12755); dc[3] = 12768;
  my_free(free_ptrs[32]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[8]);
  ptrs[28] = my_malloc(12601); dc[28] = 12616;
  my_free(free_ptrs[45]);
  my_free(free_ptrs[15]);
  ptrs[2] = my_malloc(12215); dc[2] = 12224;
  my_free(free_ptrs[80]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[7]);
  ptrs[14] = my_malloc(12110); dc[14] = 12120;
  ptrs[15] = my_malloc(12675); dc[15] = 12688;
  my_free(free_ptrs[33]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[73]);
  ptrs[4] = my_malloc(12769); dc[4] = 12784;
  my_free(free_ptrs[55]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[1]);
  ptrs[1] = my_malloc(12278); dc[1] = 12288;
  my_free(free_ptrs[43]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[51]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 7, 621112);
  printf("Correct\n");
  return 0;
}
