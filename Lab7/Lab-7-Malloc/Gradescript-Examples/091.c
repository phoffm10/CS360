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

  ptrs[1] = my_malloc(12324); dc[1] = 12336;
  ptrs[17] = my_malloc(12719); dc[17] = 12728;
  free_ptrs[39] = my_malloc(2414);  free_ptrs[40] = my_malloc(2122);  free_ptrs[41] = my_malloc(2642);
  free_ptrs[54] = my_malloc(2540);  free_ptrs[55] = my_malloc(2617);  free_ptrs[56] = my_malloc(2344);
  ptrs[24] = my_malloc(12814); dc[24] = 12824;
  free_ptrs[78] = my_malloc(2314);  free_ptrs[79] = my_malloc(2635);  free_ptrs[80] = my_malloc(2560);
  ptrs[8] = my_malloc(12140); dc[8] = 12152;
  ptrs[20] = my_malloc(12447); dc[20] = 12456;
  free_ptrs[87] = my_malloc(2330);  free_ptrs[88] = my_malloc(2641);  free_ptrs[89] = my_malloc(2514);
  free_ptrs[72] = my_malloc(2117);  free_ptrs[73] = my_malloc(2586);  free_ptrs[74] = my_malloc(2282);
  ptrs[18] = my_malloc(12328); dc[18] = 12336;
  free_ptrs[42] = my_malloc(2395);  free_ptrs[43] = my_malloc(2580);  free_ptrs[44] = my_malloc(2353);
  ptrs[29] = my_malloc(12174); dc[29] = 12184;
  free_ptrs[57] = my_malloc(2334);  free_ptrs[58] = my_malloc(2223);  free_ptrs[59] = my_malloc(2549);
  free_ptrs[0] = my_malloc(2272);  free_ptrs[1] = my_malloc(2623);  free_ptrs[2] = my_malloc(2119);
  ptrs[12] = my_malloc(12248); dc[12] = 12256;
  free_ptrs[81] = my_malloc(2088);  free_ptrs[82] = my_malloc(2121);  free_ptrs[83] = my_malloc(2217);
  free_ptrs[84] = my_malloc(2427);  free_ptrs[85] = my_malloc(2272);  free_ptrs[86] = my_malloc(2508);
  free_ptrs[48] = my_malloc(2387);  free_ptrs[49] = my_malloc(2274);  free_ptrs[50] = my_malloc(2437);
  free_ptrs[30] = my_malloc(2166);  free_ptrs[31] = my_malloc(2056);  free_ptrs[32] = my_malloc(2329);
  free_ptrs[36] = my_malloc(2254);  free_ptrs[37] = my_malloc(2167);  free_ptrs[38] = my_malloc(2240);
  ptrs[15] = my_malloc(12793); dc[15] = 12808;
  free_ptrs[27] = my_malloc(2059);  free_ptrs[28] = my_malloc(2066);  free_ptrs[29] = my_malloc(2165);
  free_ptrs[66] = my_malloc(2692);  free_ptrs[67] = my_malloc(2671);  free_ptrs[68] = my_malloc(2150);
  ptrs[13] = my_malloc(12927); dc[13] = 12936;
  free_ptrs[3] = my_malloc(2543);  free_ptrs[4] = my_malloc(2228);  free_ptrs[5] = my_malloc(2181);
  ptrs[27] = my_malloc(12093); dc[27] = 12104;
  free_ptrs[15] = my_malloc(2568);  free_ptrs[16] = my_malloc(2081);  free_ptrs[17] = my_malloc(2662);
  free_ptrs[63] = my_malloc(2322);  free_ptrs[64] = my_malloc(2531);  free_ptrs[65] = my_malloc(2350);
  ptrs[21] = my_malloc(12612); dc[21] = 12624;
  ptrs[3] = my_malloc(12225); dc[3] = 12240;
  ptrs[4] = my_malloc(12687); dc[4] = 12696;
  ptrs[28] = my_malloc(12143); dc[28] = 12152;
  free_ptrs[6] = my_malloc(2332);  free_ptrs[7] = my_malloc(2250);  free_ptrs[8] = my_malloc(2431);
  free_ptrs[12] = my_malloc(2386);  free_ptrs[13] = my_malloc(2444);  free_ptrs[14] = my_malloc(2520);
  free_ptrs[24] = my_malloc(2617);  free_ptrs[25] = my_malloc(2638);  free_ptrs[26] = my_malloc(2505);
  free_ptrs[18] = my_malloc(2432);  free_ptrs[19] = my_malloc(2162);  free_ptrs[20] = my_malloc(2052);
  free_ptrs[9] = my_malloc(2517);  free_ptrs[10] = my_malloc(2253);  free_ptrs[11] = my_malloc(2217);
  free_ptrs[69] = my_malloc(2158);  free_ptrs[70] = my_malloc(2082);  free_ptrs[71] = my_malloc(2582);
  ptrs[9] = my_malloc(12336); dc[9] = 12344;
  ptrs[25] = my_malloc(12244); dc[25] = 12256;
  free_ptrs[45] = my_malloc(2549);  free_ptrs[46] = my_malloc(2193);  free_ptrs[47] = my_malloc(2643);
  free_ptrs[60] = my_malloc(2146);  free_ptrs[61] = my_malloc(2053);  free_ptrs[62] = my_malloc(2636);
  free_ptrs[51] = my_malloc(2500);  free_ptrs[52] = my_malloc(2550);  free_ptrs[53] = my_malloc(2370);
  free_ptrs[75] = my_malloc(2132);  free_ptrs[76] = my_malloc(2460);  free_ptrs[77] = my_malloc(2493);
  ptrs[6] = my_malloc(12855); dc[6] = 12864;
  ptrs[16] = my_malloc(12963); dc[16] = 12976;
  free_ptrs[21] = my_malloc(2667);  free_ptrs[22] = my_malloc(2470);  free_ptrs[23] = my_malloc(2520);
  ptrs[5] = my_malloc(12478); dc[5] = 12488;
  free_ptrs[33] = my_malloc(2135);  free_ptrs[34] = my_malloc(2055);  free_ptrs[35] = my_malloc(2335);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[62]);
  ptrs[19] = my_malloc(12471); dc[19] = 12480;
  my_free(free_ptrs[89]);
  my_free(free_ptrs[32]);
  ptrs[7] = my_malloc(12449); dc[7] = 12464;
  my_free(free_ptrs[42]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[71]);
  ptrs[0] = my_malloc(12531); dc[0] = 12544;
  ptrs[26] = my_malloc(12981); dc[26] = 12992;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[79]);
  ptrs[23] = my_malloc(12309); dc[23] = 12320;
  my_free(free_ptrs[9]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[59]);
  ptrs[14] = my_malloc(12804); dc[14] = 12816;
  my_free(free_ptrs[80]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[53]);
  ptrs[2] = my_malloc(12845); dc[2] = 12856;
  my_free(free_ptrs[82]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[3]);
  ptrs[11] = my_malloc(12584); dc[11] = 12592;
  my_free(free_ptrs[68]);
  my_free(free_ptrs[46]);
  ptrs[10] = my_malloc(12900); dc[10] = 12912;
  my_free(free_ptrs[52]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[11]);
  ptrs[22] = my_malloc(12825); dc[22] = 12840;
  my_free(free_ptrs[31]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[55]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 13, 622336);
  printf("Correct\n");
  return 0;
}
