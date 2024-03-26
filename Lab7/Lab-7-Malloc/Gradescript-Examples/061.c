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

  free_ptrs[75] = my_malloc(2668);  free_ptrs[76] = my_malloc(2472);  free_ptrs[77] = my_malloc(2223);
  free_ptrs[72] = my_malloc(2605);  free_ptrs[73] = my_malloc(2452);  free_ptrs[74] = my_malloc(2166);
  free_ptrs[54] = my_malloc(2444);  free_ptrs[55] = my_malloc(2519);  free_ptrs[56] = my_malloc(2198);
  free_ptrs[81] = my_malloc(2050);  free_ptrs[82] = my_malloc(2145);  free_ptrs[83] = my_malloc(2159);
  ptrs[14] = my_malloc(12458); dc[14] = 12472;
  free_ptrs[0] = my_malloc(2496);  free_ptrs[1] = my_malloc(2259);  free_ptrs[2] = my_malloc(2051);
  ptrs[26] = my_malloc(12531); dc[26] = 12544;
  ptrs[5] = my_malloc(12300); dc[5] = 12312;
  free_ptrs[18] = my_malloc(2690);  free_ptrs[19] = my_malloc(2240);  free_ptrs[20] = my_malloc(2380);
  free_ptrs[21] = my_malloc(2287);  free_ptrs[22] = my_malloc(2062);  free_ptrs[23] = my_malloc(2588);
  ptrs[18] = my_malloc(12126); dc[18] = 12136;
  free_ptrs[48] = my_malloc(2625);  free_ptrs[49] = my_malloc(2458);  free_ptrs[50] = my_malloc(2099);
  free_ptrs[39] = my_malloc(2616);  free_ptrs[40] = my_malloc(2492);  free_ptrs[41] = my_malloc(2394);
  free_ptrs[24] = my_malloc(2683);  free_ptrs[25] = my_malloc(2080);  free_ptrs[26] = my_malloc(2363);
  free_ptrs[63] = my_malloc(2166);  free_ptrs[64] = my_malloc(2567);  free_ptrs[65] = my_malloc(2466);
  free_ptrs[84] = my_malloc(2147);  free_ptrs[85] = my_malloc(2480);  free_ptrs[86] = my_malloc(2188);
  ptrs[19] = my_malloc(12509); dc[19] = 12520;
  free_ptrs[60] = my_malloc(2182);  free_ptrs[61] = my_malloc(2099);  free_ptrs[62] = my_malloc(2082);
  free_ptrs[33] = my_malloc(2221);  free_ptrs[34] = my_malloc(2305);  free_ptrs[35] = my_malloc(2087);
  ptrs[20] = my_malloc(12261); dc[20] = 12272;
  ptrs[25] = my_malloc(12506); dc[25] = 12520;
  ptrs[28] = my_malloc(12909); dc[28] = 12920;
  ptrs[12] = my_malloc(12646); dc[12] = 12656;
  free_ptrs[42] = my_malloc(2345);  free_ptrs[43] = my_malloc(2554);  free_ptrs[44] = my_malloc(2377);
  free_ptrs[12] = my_malloc(2330);  free_ptrs[13] = my_malloc(2654);  free_ptrs[14] = my_malloc(2642);
  ptrs[10] = my_malloc(12530); dc[10] = 12544;
  free_ptrs[36] = my_malloc(2488);  free_ptrs[37] = my_malloc(2501);  free_ptrs[38] = my_malloc(2430);
  free_ptrs[78] = my_malloc(2282);  free_ptrs[79] = my_malloc(2295);  free_ptrs[80] = my_malloc(2398);
  ptrs[29] = my_malloc(12108); dc[29] = 12120;
  free_ptrs[57] = my_malloc(2326);  free_ptrs[58] = my_malloc(2425);  free_ptrs[59] = my_malloc(2209);
  free_ptrs[27] = my_malloc(2465);  free_ptrs[28] = my_malloc(2428);  free_ptrs[29] = my_malloc(2391);
  free_ptrs[6] = my_malloc(2064);  free_ptrs[7] = my_malloc(2104);  free_ptrs[8] = my_malloc(2221);
  free_ptrs[51] = my_malloc(2530);  free_ptrs[52] = my_malloc(2388);  free_ptrs[53] = my_malloc(2660);
  free_ptrs[15] = my_malloc(2678);  free_ptrs[16] = my_malloc(2133);  free_ptrs[17] = my_malloc(2332);
  free_ptrs[9] = my_malloc(2545);  free_ptrs[10] = my_malloc(2293);  free_ptrs[11] = my_malloc(2377);
  ptrs[6] = my_malloc(12597); dc[6] = 12608;
  free_ptrs[30] = my_malloc(2170);  free_ptrs[31] = my_malloc(2646);  free_ptrs[32] = my_malloc(2213);
  ptrs[1] = my_malloc(12090); dc[1] = 12104;
  ptrs[9] = my_malloc(12854); dc[9] = 12864;
  ptrs[16] = my_malloc(12817); dc[16] = 12832;
  free_ptrs[3] = my_malloc(2647);  free_ptrs[4] = my_malloc(2374);  free_ptrs[5] = my_malloc(2111);
  free_ptrs[45] = my_malloc(2337);  free_ptrs[46] = my_malloc(2589);  free_ptrs[47] = my_malloc(2685);
  free_ptrs[66] = my_malloc(2632);  free_ptrs[67] = my_malloc(2525);  free_ptrs[68] = my_malloc(2666);
  free_ptrs[69] = my_malloc(2262);  free_ptrs[70] = my_malloc(2500);  free_ptrs[71] = my_malloc(2480);
  free_ptrs[87] = my_malloc(2224);  free_ptrs[88] = my_malloc(2537);  free_ptrs[89] = my_malloc(2056);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[28]);
  ptrs[23] = my_malloc(12283); dc[23] = 12296;
  my_free(free_ptrs[55]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[78]);
  ptrs[3] = my_malloc(12047); dc[3] = 12056;
  ptrs[4] = my_malloc(12709); dc[4] = 12720;
  my_free(free_ptrs[11]);
  my_free(free_ptrs[13]);
  ptrs[17] = my_malloc(12429); dc[17] = 12440;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[72]);
  ptrs[8] = my_malloc(12498); dc[8] = 12512;
  my_free(free_ptrs[22]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[20]);
  ptrs[21] = my_malloc(12466); dc[21] = 12480;
  my_free(free_ptrs[52]);
  ptrs[11] = my_malloc(12006); dc[11] = 12016;
  my_free(free_ptrs[86]);
  my_free(free_ptrs[15]);
  ptrs[27] = my_malloc(12683); dc[27] = 12696;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[42]);
  ptrs[7] = my_malloc(12719); dc[7] = 12728;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[51]);
  ptrs[22] = my_malloc(12047); dc[22] = 12056;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[69]);
  ptrs[15] = my_malloc(12151); dc[15] = 12160;
  my_free(free_ptrs[33]);
  ptrs[13] = my_malloc(12117); dc[13] = 12128;
  my_free(free_ptrs[60]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[44]);
  ptrs[2] = my_malloc(12219); dc[2] = 12232;
  my_free(free_ptrs[3]);
  ptrs[24] = my_malloc(12428); dc[24] = 12440;
  ptrs[0] = my_malloc(12713); dc[0] = 12728;

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 10, 618872);
  printf("Correct\n");
  return 0;
}
