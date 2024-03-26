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

  free_ptrs[48] = my_malloc(2470);  free_ptrs[49] = my_malloc(2622);  free_ptrs[50] = my_malloc(2227);
  free_ptrs[57] = my_malloc(2557);  free_ptrs[58] = my_malloc(2256);  free_ptrs[59] = my_malloc(2386);
  ptrs[23] = my_malloc(12732); dc[23] = 12744;
  free_ptrs[27] = my_malloc(2064);  free_ptrs[28] = my_malloc(2255);  free_ptrs[29] = my_malloc(2690);
  free_ptrs[66] = my_malloc(2390);  free_ptrs[67] = my_malloc(2516);  free_ptrs[68] = my_malloc(2540);
  ptrs[4] = my_malloc(12441); dc[4] = 12456;
  ptrs[25] = my_malloc(12034); dc[25] = 12048;
  free_ptrs[60] = my_malloc(2512);  free_ptrs[61] = my_malloc(2272);  free_ptrs[62] = my_malloc(2095);
  free_ptrs[12] = my_malloc(2185);  free_ptrs[13] = my_malloc(2392);  free_ptrs[14] = my_malloc(2629);
  free_ptrs[0] = my_malloc(2322);  free_ptrs[1] = my_malloc(2137);  free_ptrs[2] = my_malloc(2612);
  free_ptrs[36] = my_malloc(2399);  free_ptrs[37] = my_malloc(2577);  free_ptrs[38] = my_malloc(2595);
  ptrs[14] = my_malloc(12143); dc[14] = 12152;
  ptrs[10] = my_malloc(12911); dc[10] = 12920;
  free_ptrs[54] = my_malloc(2575);  free_ptrs[55] = my_malloc(2272);  free_ptrs[56] = my_malloc(2096);
  free_ptrs[51] = my_malloc(2467);  free_ptrs[52] = my_malloc(2082);  free_ptrs[53] = my_malloc(2590);
  free_ptrs[69] = my_malloc(2552);  free_ptrs[70] = my_malloc(2069);  free_ptrs[71] = my_malloc(2105);
  free_ptrs[33] = my_malloc(2396);  free_ptrs[34] = my_malloc(2107);  free_ptrs[35] = my_malloc(2331);
  ptrs[1] = my_malloc(12218); dc[1] = 12232;
  free_ptrs[63] = my_malloc(2684);  free_ptrs[64] = my_malloc(2077);  free_ptrs[65] = my_malloc(2514);
  ptrs[9] = my_malloc(12934); dc[9] = 12944;
  ptrs[22] = my_malloc(12812); dc[22] = 12824;
  ptrs[20] = my_malloc(12017); dc[20] = 12032;
  free_ptrs[78] = my_malloc(2541);  free_ptrs[79] = my_malloc(2134);  free_ptrs[80] = my_malloc(2058);
  free_ptrs[42] = my_malloc(2242);  free_ptrs[43] = my_malloc(2693);  free_ptrs[44] = my_malloc(2205);
  ptrs[17] = my_malloc(12158); dc[17] = 12168;
  free_ptrs[45] = my_malloc(2256);  free_ptrs[46] = my_malloc(2401);  free_ptrs[47] = my_malloc(2403);
  free_ptrs[75] = my_malloc(2661);  free_ptrs[76] = my_malloc(2633);  free_ptrs[77] = my_malloc(2248);
  ptrs[8] = my_malloc(12294); dc[8] = 12304;
  free_ptrs[15] = my_malloc(2561);  free_ptrs[16] = my_malloc(2319);  free_ptrs[17] = my_malloc(2488);
  free_ptrs[24] = my_malloc(2372);  free_ptrs[25] = my_malloc(2146);  free_ptrs[26] = my_malloc(2109);
  free_ptrs[6] = my_malloc(2549);  free_ptrs[7] = my_malloc(2317);  free_ptrs[8] = my_malloc(2064);
  ptrs[2] = my_malloc(12352); dc[2] = 12360;
  free_ptrs[30] = my_malloc(2142);  free_ptrs[31] = my_malloc(2079);  free_ptrs[32] = my_malloc(2223);
  free_ptrs[81] = my_malloc(2269);  free_ptrs[82] = my_malloc(2428);  free_ptrs[83] = my_malloc(2459);
  free_ptrs[72] = my_malloc(2611);  free_ptrs[73] = my_malloc(2302);  free_ptrs[74] = my_malloc(2569);
  free_ptrs[84] = my_malloc(2128);  free_ptrs[85] = my_malloc(2459);  free_ptrs[86] = my_malloc(2670);
  ptrs[28] = my_malloc(12986); dc[28] = 13000;
  free_ptrs[39] = my_malloc(2432);  free_ptrs[40] = my_malloc(2592);  free_ptrs[41] = my_malloc(2155);
  ptrs[19] = my_malloc(12453); dc[19] = 12464;
  ptrs[27] = my_malloc(12587); dc[27] = 12600;
  ptrs[7] = my_malloc(12487); dc[7] = 12496;
  free_ptrs[18] = my_malloc(2179);  free_ptrs[19] = my_malloc(2314);  free_ptrs[20] = my_malloc(2241);
  free_ptrs[3] = my_malloc(2245);  free_ptrs[4] = my_malloc(2220);  free_ptrs[5] = my_malloc(2451);
  free_ptrs[9] = my_malloc(2579);  free_ptrs[10] = my_malloc(2495);  free_ptrs[11] = my_malloc(2690);
  free_ptrs[21] = my_malloc(2146);  free_ptrs[22] = my_malloc(2267);  free_ptrs[23] = my_malloc(2273);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[27]);
  ptrs[0] = my_malloc(12446); dc[0] = 12456;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[35]);
  ptrs[24] = my_malloc(12921); dc[24] = 12936;
  my_free(free_ptrs[17]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[5]);
  ptrs[3] = my_malloc(12328); dc[3] = 12336;
  my_free(free_ptrs[86]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[72]);
  ptrs[21] = my_malloc(12539); dc[21] = 12552;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[80]);
  ptrs[12] = my_malloc(12651); dc[12] = 12664;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[60]);
  ptrs[18] = my_malloc(12186); dc[18] = 12200;
  my_free(free_ptrs[85]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[81]);
  ptrs[6] = my_malloc(12585); dc[6] = 12600;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[50]);
  ptrs[5] = my_malloc(12685); dc[5] = 12696;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[84]);
  ptrs[15] = my_malloc(12840); dc[15] = 12848;
  my_free(free_ptrs[61]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[29]);
  ptrs[16] = my_malloc(12014); dc[16] = 12024;
  my_free(free_ptrs[46]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[53]);
  ptrs[26] = my_malloc(12888); dc[26] = 12896;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[3]);
  ptrs[13] = my_malloc(12054); dc[13] = 12064;
  my_free(free_ptrs[59]);
  my_free(free_ptrs[11]);
  ptrs[11] = my_malloc(12135); dc[11] = 12144;
  my_free(free_ptrs[48]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 11, 599728);
  printf("Correct\n");
  return 0;
}
