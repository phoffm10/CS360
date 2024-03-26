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

  ptrs[24] = my_malloc(12890); dc[24] = 12904;
  free_ptrs[42] = my_malloc(2307);  free_ptrs[43] = my_malloc(2361);  free_ptrs[44] = my_malloc(2346);
  free_ptrs[60] = my_malloc(2058);  free_ptrs[61] = my_malloc(2170);  free_ptrs[62] = my_malloc(2517);
  free_ptrs[66] = my_malloc(2611);  free_ptrs[67] = my_malloc(2436);  free_ptrs[68] = my_malloc(2573);
  free_ptrs[0] = my_malloc(2194);  free_ptrs[1] = my_malloc(2204);  free_ptrs[2] = my_malloc(2163);
  ptrs[15] = my_malloc(12149); dc[15] = 12160;
  free_ptrs[9] = my_malloc(2644);  free_ptrs[10] = my_malloc(2319);  free_ptrs[11] = my_malloc(2497);
  ptrs[6] = my_malloc(12115); dc[6] = 12128;
  free_ptrs[15] = my_malloc(2455);  free_ptrs[16] = my_malloc(2424);  free_ptrs[17] = my_malloc(2117);
  ptrs[18] = my_malloc(12428); dc[18] = 12440;
  free_ptrs[48] = my_malloc(2304);  free_ptrs[49] = my_malloc(2545);  free_ptrs[50] = my_malloc(2180);
  free_ptrs[33] = my_malloc(2305);  free_ptrs[34] = my_malloc(2409);  free_ptrs[35] = my_malloc(2439);
  ptrs[11] = my_malloc(12100); dc[11] = 12112;
  free_ptrs[3] = my_malloc(2652);  free_ptrs[4] = my_malloc(2613);  free_ptrs[5] = my_malloc(2542);
  free_ptrs[54] = my_malloc(2475);  free_ptrs[55] = my_malloc(2476);  free_ptrs[56] = my_malloc(2335);
  free_ptrs[81] = my_malloc(2318);  free_ptrs[82] = my_malloc(2280);  free_ptrs[83] = my_malloc(2137);
  free_ptrs[72] = my_malloc(2657);  free_ptrs[73] = my_malloc(2659);  free_ptrs[74] = my_malloc(2496);
  ptrs[3] = my_malloc(12989); dc[3] = 13000;
  free_ptrs[63] = my_malloc(2263);  free_ptrs[64] = my_malloc(2218);  free_ptrs[65] = my_malloc(2339);
  free_ptrs[75] = my_malloc(2260);  free_ptrs[76] = my_malloc(2490);  free_ptrs[77] = my_malloc(2468);
  ptrs[27] = my_malloc(12937); dc[27] = 12952;
  ptrs[1] = my_malloc(12952); dc[1] = 12960;
  free_ptrs[12] = my_malloc(2210);  free_ptrs[13] = my_malloc(2566);  free_ptrs[14] = my_malloc(2368);
  free_ptrs[21] = my_malloc(2650);  free_ptrs[22] = my_malloc(2197);  free_ptrs[23] = my_malloc(2632);
  ptrs[14] = my_malloc(12024); dc[14] = 12032;
  free_ptrs[6] = my_malloc(2126);  free_ptrs[7] = my_malloc(2586);  free_ptrs[8] = my_malloc(2154);
  free_ptrs[45] = my_malloc(2400);  free_ptrs[46] = my_malloc(2191);  free_ptrs[47] = my_malloc(2457);
  free_ptrs[36] = my_malloc(2422);  free_ptrs[37] = my_malloc(2626);  free_ptrs[38] = my_malloc(2605);
  free_ptrs[69] = my_malloc(2380);  free_ptrs[70] = my_malloc(2662);  free_ptrs[71] = my_malloc(2144);
  free_ptrs[78] = my_malloc(2209);  free_ptrs[79] = my_malloc(2292);  free_ptrs[80] = my_malloc(2625);
  free_ptrs[51] = my_malloc(2240);  free_ptrs[52] = my_malloc(2520);  free_ptrs[53] = my_malloc(2226);
  ptrs[13] = my_malloc(12387); dc[13] = 12400;
  free_ptrs[39] = my_malloc(2310);  free_ptrs[40] = my_malloc(2332);  free_ptrs[41] = my_malloc(2368);
  free_ptrs[57] = my_malloc(2076);  free_ptrs[58] = my_malloc(2544);  free_ptrs[59] = my_malloc(2359);
  ptrs[9] = my_malloc(12780); dc[9] = 12792;
  free_ptrs[30] = my_malloc(2634);  free_ptrs[31] = my_malloc(2602);  free_ptrs[32] = my_malloc(2232);
  free_ptrs[84] = my_malloc(2403);  free_ptrs[85] = my_malloc(2673);  free_ptrs[86] = my_malloc(2194);
  free_ptrs[18] = my_malloc(2490);  free_ptrs[19] = my_malloc(2388);  free_ptrs[20] = my_malloc(2432);
  free_ptrs[24] = my_malloc(2231);  free_ptrs[25] = my_malloc(2227);  free_ptrs[26] = my_malloc(2482);
  free_ptrs[27] = my_malloc(2130);  free_ptrs[28] = my_malloc(2547);  free_ptrs[29] = my_malloc(2308);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[59]);
  ptrs[4] = my_malloc(12251); dc[4] = 12264;
  ptrs[12] = my_malloc(12964); dc[12] = 12976;
  my_free(free_ptrs[55]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[27]);
  ptrs[26] = my_malloc(12249); dc[26] = 12264;
  my_free(free_ptrs[3]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[0]);
  ptrs[28] = my_malloc(12987); dc[28] = 13000;
  my_free(free_ptrs[8]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[28]);
  ptrs[7] = my_malloc(12061); dc[7] = 12072;
  my_free(free_ptrs[72]);
  ptrs[16] = my_malloc(12631); dc[16] = 12640;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[7]);
  ptrs[17] = my_malloc(12427); dc[17] = 12440;
  my_free(free_ptrs[36]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[58]);
  ptrs[20] = my_malloc(12539); dc[20] = 12552;
  my_free(free_ptrs[61]);
  ptrs[10] = my_malloc(12536); dc[10] = 12544;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[22]);
  ptrs[0] = my_malloc(12535); dc[0] = 12544;
  my_free(free_ptrs[29]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[70]);
  ptrs[8] = my_malloc(12496); dc[8] = 12504;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[69]);
  ptrs[5] = my_malloc(12810); dc[5] = 12824;
  my_free(free_ptrs[45]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[24]);
  ptrs[22] = my_malloc(12541); dc[22] = 12552;
  ptrs[2] = my_malloc(12977); dc[2] = 12992;
  my_free(free_ptrs[52]);
  my_free(free_ptrs[74]);
  ptrs[21] = my_malloc(12416); dc[21] = 12424;
  my_free(free_ptrs[44]);
  my_free(free_ptrs[16]);
  ptrs[25] = my_malloc(12184); dc[25] = 12192;
  my_free(free_ptrs[35]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[10]);
  ptrs[19] = my_malloc(12947); dc[19] = 12960;
  my_free(free_ptrs[65]);
  ptrs[23] = my_malloc(12409); dc[23] = 12424;
  my_free(free_ptrs[85]);
  my_free(free_ptrs[78]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 10, 601616);
  printf("Correct\n");
  return 0;
}
