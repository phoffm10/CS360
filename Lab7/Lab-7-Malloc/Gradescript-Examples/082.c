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

  ptrs[17] = my_malloc(12490); dc[17] = 12504;
  free_ptrs[87] = my_malloc(2556);  free_ptrs[88] = my_malloc(2374);  free_ptrs[89] = my_malloc(2438);
  free_ptrs[21] = my_malloc(2219);  free_ptrs[22] = my_malloc(2234);  free_ptrs[23] = my_malloc(2320);
  ptrs[18] = my_malloc(12918); dc[18] = 12928;
  free_ptrs[33] = my_malloc(2421);  free_ptrs[34] = my_malloc(2331);  free_ptrs[35] = my_malloc(2196);
  ptrs[8] = my_malloc(12842); dc[8] = 12856;
  free_ptrs[9] = my_malloc(2608);  free_ptrs[10] = my_malloc(2157);  free_ptrs[11] = my_malloc(2261);
  free_ptrs[84] = my_malloc(2262);  free_ptrs[85] = my_malloc(2048);  free_ptrs[86] = my_malloc(2549);
  free_ptrs[75] = my_malloc(2680);  free_ptrs[76] = my_malloc(2265);  free_ptrs[77] = my_malloc(2398);
  ptrs[5] = my_malloc(12025); dc[5] = 12040;
  free_ptrs[72] = my_malloc(2167);  free_ptrs[73] = my_malloc(2553);  free_ptrs[74] = my_malloc(2661);
  ptrs[1] = my_malloc(12126); dc[1] = 12136;
  free_ptrs[42] = my_malloc(2501);  free_ptrs[43] = my_malloc(2326);  free_ptrs[44] = my_malloc(2593);
  ptrs[16] = my_malloc(12674); dc[16] = 12688;
  free_ptrs[78] = my_malloc(2062);  free_ptrs[79] = my_malloc(2437);  free_ptrs[80] = my_malloc(2637);
  free_ptrs[3] = my_malloc(2563);  free_ptrs[4] = my_malloc(2250);  free_ptrs[5] = my_malloc(2472);
  free_ptrs[90] = my_malloc(2624);  free_ptrs[91] = my_malloc(2165);  free_ptrs[92] = my_malloc(2633);
  free_ptrs[69] = my_malloc(2301);  free_ptrs[70] = my_malloc(2569);  free_ptrs[71] = my_malloc(2147);
  free_ptrs[63] = my_malloc(2146);  free_ptrs[64] = my_malloc(2169);  free_ptrs[65] = my_malloc(2124);
  free_ptrs[81] = my_malloc(2453);  free_ptrs[82] = my_malloc(2417);  free_ptrs[83] = my_malloc(2394);
  free_ptrs[30] = my_malloc(2597);  free_ptrs[31] = my_malloc(2185);  free_ptrs[32] = my_malloc(2634);
  free_ptrs[15] = my_malloc(2694);  free_ptrs[16] = my_malloc(2668);  free_ptrs[17] = my_malloc(2492);
  free_ptrs[39] = my_malloc(2073);  free_ptrs[40] = my_malloc(2278);  free_ptrs[41] = my_malloc(2084);
  ptrs[29] = my_malloc(12000); dc[29] = 12008;
  free_ptrs[18] = my_malloc(2585);  free_ptrs[19] = my_malloc(2333);  free_ptrs[20] = my_malloc(2470);
  ptrs[15] = my_malloc(12604); dc[15] = 12616;
  free_ptrs[66] = my_malloc(2356);  free_ptrs[67] = my_malloc(2198);  free_ptrs[68] = my_malloc(2541);
  free_ptrs[51] = my_malloc(2266);  free_ptrs[52] = my_malloc(2278);  free_ptrs[53] = my_malloc(2697);
  free_ptrs[57] = my_malloc(2556);  free_ptrs[58] = my_malloc(2174);  free_ptrs[59] = my_malloc(2601);
  ptrs[14] = my_malloc(12403); dc[14] = 12416;
  ptrs[6] = my_malloc(12949); dc[6] = 12960;
  ptrs[20] = my_malloc(12653); dc[20] = 12664;
  free_ptrs[48] = my_malloc(2691);  free_ptrs[49] = my_malloc(2370);  free_ptrs[50] = my_malloc(2522);
  ptrs[4] = my_malloc(12901); dc[4] = 12912;
  ptrs[28] = my_malloc(12606); dc[28] = 12616;
  free_ptrs[54] = my_malloc(2624);  free_ptrs[55] = my_malloc(2370);  free_ptrs[56] = my_malloc(2171);
  free_ptrs[12] = my_malloc(2653);  free_ptrs[13] = my_malloc(2142);  free_ptrs[14] = my_malloc(2162);
  free_ptrs[45] = my_malloc(2315);  free_ptrs[46] = my_malloc(2277);  free_ptrs[47] = my_malloc(2059);
  ptrs[2] = my_malloc(12092); dc[2] = 12104;
  free_ptrs[27] = my_malloc(2394);  free_ptrs[28] = my_malloc(2505);  free_ptrs[29] = my_malloc(2648);
  free_ptrs[0] = my_malloc(2548);  free_ptrs[1] = my_malloc(2496);  free_ptrs[2] = my_malloc(2213);
  ptrs[7] = my_malloc(12499); dc[7] = 12512;
  free_ptrs[24] = my_malloc(2161);  free_ptrs[25] = my_malloc(2174);  free_ptrs[26] = my_malloc(2468);
  ptrs[21] = my_malloc(12839); dc[21] = 12848;
  ptrs[0] = my_malloc(12562); dc[0] = 12576;
  free_ptrs[60] = my_malloc(2591);  free_ptrs[61] = my_malloc(2376);  free_ptrs[62] = my_malloc(2075);
  free_ptrs[6] = my_malloc(2314);  free_ptrs[7] = my_malloc(2113);  free_ptrs[8] = my_malloc(2128);
  free_ptrs[36] = my_malloc(2449);  free_ptrs[37] = my_malloc(2206);  free_ptrs[38] = my_malloc(2586);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[42]);
  ptrs[9] = my_malloc(12218); dc[9] = 12232;
  my_free(free_ptrs[72]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[43]);
  ptrs[22] = my_malloc(12808); dc[22] = 12816;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[24]);
  ptrs[3] = my_malloc(12740); dc[3] = 12752;
  my_free(free_ptrs[64]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[47]);
  ptrs[19] = my_malloc(12745); dc[19] = 12760;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[65]);
  ptrs[27] = my_malloc(12639); dc[27] = 12648;
  my_free(free_ptrs[76]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[1]);
  ptrs[10] = my_malloc(12699); dc[10] = 12712;
  my_free(free_ptrs[80]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[92]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[29]);
  ptrs[12] = my_malloc(12079); dc[12] = 12088;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[33]);
  ptrs[11] = my_malloc(12179); dc[11] = 12192;
  my_free(free_ptrs[88]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[84]);
  ptrs[13] = my_malloc(12802); dc[13] = 12816;
  ptrs[25] = my_malloc(12054); dc[25] = 12064;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[87]);
  ptrs[24] = my_malloc(12229); dc[24] = 12240;
  my_free(free_ptrs[46]);
  ptrs[30] = my_malloc(12313); dc[30] = 12328;
  my_free(free_ptrs[77]);
  ptrs[26] = my_malloc(12484); dc[26] = 12496;
  my_free(free_ptrs[9]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[35]);
  ptrs[23] = my_malloc(12248); dc[23] = 12256;
  my_free(free_ptrs[82]);
  my_free(free_ptrs[69]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 13, 641736);
  printf("Correct\n");
  return 0;
}
