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
  int *ptrs[28];
  int *free_ptrs[84];
  int dc[28];

  free_ptrs[6] = my_malloc(2094);  free_ptrs[7] = my_malloc(2516);  free_ptrs[8] = my_malloc(2158);
  ptrs[12] = my_malloc(12358); dc[12] = 12368;
  ptrs[1] = my_malloc(12370); dc[1] = 12384;
  free_ptrs[24] = my_malloc(2414);  free_ptrs[25] = my_malloc(2143);  free_ptrs[26] = my_malloc(2553);
  ptrs[27] = my_malloc(12891); dc[27] = 12904;
  free_ptrs[66] = my_malloc(2234);  free_ptrs[67] = my_malloc(2375);  free_ptrs[68] = my_malloc(2108);
  ptrs[10] = my_malloc(12330); dc[10] = 12344;
  ptrs[26] = my_malloc(12859); dc[26] = 12872;
  free_ptrs[63] = my_malloc(2157);  free_ptrs[64] = my_malloc(2647);  free_ptrs[65] = my_malloc(2304);
  free_ptrs[9] = my_malloc(2490);  free_ptrs[10] = my_malloc(2386);  free_ptrs[11] = my_malloc(2377);
  free_ptrs[60] = my_malloc(2444);  free_ptrs[61] = my_malloc(2570);  free_ptrs[62] = my_malloc(2582);
  free_ptrs[69] = my_malloc(2126);  free_ptrs[70] = my_malloc(2420);  free_ptrs[71] = my_malloc(2242);
  free_ptrs[72] = my_malloc(2071);  free_ptrs[73] = my_malloc(2477);  free_ptrs[74] = my_malloc(2531);
  free_ptrs[36] = my_malloc(2616);  free_ptrs[37] = my_malloc(2324);  free_ptrs[38] = my_malloc(2424);
  free_ptrs[18] = my_malloc(2237);  free_ptrs[19] = my_malloc(2538);  free_ptrs[20] = my_malloc(2100);
  ptrs[6] = my_malloc(12997); dc[6] = 13008;
  free_ptrs[57] = my_malloc(2630);  free_ptrs[58] = my_malloc(2048);  free_ptrs[59] = my_malloc(2694);
  free_ptrs[30] = my_malloc(2177);  free_ptrs[31] = my_malloc(2620);  free_ptrs[32] = my_malloc(2454);
  free_ptrs[51] = my_malloc(2051);  free_ptrs[52] = my_malloc(2492);  free_ptrs[53] = my_malloc(2070);
  free_ptrs[81] = my_malloc(2318);  free_ptrs[82] = my_malloc(2118);  free_ptrs[83] = my_malloc(2228);
  free_ptrs[33] = my_malloc(2206);  free_ptrs[34] = my_malloc(2669);  free_ptrs[35] = my_malloc(2505);
  ptrs[22] = my_malloc(12327); dc[22] = 12336;
  free_ptrs[75] = my_malloc(2650);  free_ptrs[76] = my_malloc(2566);  free_ptrs[77] = my_malloc(2408);
  free_ptrs[21] = my_malloc(2697);  free_ptrs[22] = my_malloc(2590);  free_ptrs[23] = my_malloc(2481);
  ptrs[23] = my_malloc(12699); dc[23] = 12712;
  free_ptrs[0] = my_malloc(2681);  free_ptrs[1] = my_malloc(2060);  free_ptrs[2] = my_malloc(2586);
  free_ptrs[27] = my_malloc(2438);  free_ptrs[28] = my_malloc(2520);  free_ptrs[29] = my_malloc(2683);
  ptrs[16] = my_malloc(12457); dc[16] = 12472;
  ptrs[24] = my_malloc(12660); dc[24] = 12672;
  free_ptrs[39] = my_malloc(2053);  free_ptrs[40] = my_malloc(2152);  free_ptrs[41] = my_malloc(2076);
  free_ptrs[54] = my_malloc(2265);  free_ptrs[55] = my_malloc(2227);  free_ptrs[56] = my_malloc(2312);
  free_ptrs[3] = my_malloc(2257);  free_ptrs[4] = my_malloc(2320);  free_ptrs[5] = my_malloc(2339);
  free_ptrs[48] = my_malloc(2318);  free_ptrs[49] = my_malloc(2318);  free_ptrs[50] = my_malloc(2197);
  ptrs[18] = my_malloc(12462); dc[18] = 12472;
  free_ptrs[15] = my_malloc(2655);  free_ptrs[16] = my_malloc(2231);  free_ptrs[17] = my_malloc(2652);
  ptrs[11] = my_malloc(12886); dc[11] = 12896;
  free_ptrs[45] = my_malloc(2091);  free_ptrs[46] = my_malloc(2474);  free_ptrs[47] = my_malloc(2381);
  free_ptrs[78] = my_malloc(2588);  free_ptrs[79] = my_malloc(2243);  free_ptrs[80] = my_malloc(2310);
  free_ptrs[12] = my_malloc(2419);  free_ptrs[13] = my_malloc(2110);  free_ptrs[14] = my_malloc(2524);
  free_ptrs[42] = my_malloc(2438);  free_ptrs[43] = my_malloc(2695);  free_ptrs[44] = my_malloc(2389);
  my_free(free_ptrs[32]);
  ptrs[15] = my_malloc(12911); dc[15] = 12920;
  ptrs[25] = my_malloc(12234); dc[25] = 12248;
  my_free(free_ptrs[21]);
  ptrs[20] = my_malloc(12805); dc[20] = 12816;
  my_free(free_ptrs[56]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[45]);
  ptrs[7] = my_malloc(12767); dc[7] = 12776;
  my_free(free_ptrs[65]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[7]);
  ptrs[0] = my_malloc(12473); dc[0] = 12488;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[23]);
  ptrs[17] = my_malloc(12405); dc[17] = 12416;
  my_free(free_ptrs[49]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[8]);
  ptrs[4] = my_malloc(12957); dc[4] = 12968;
  ptrs[8] = my_malloc(12042); dc[8] = 12056;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[17]);
  ptrs[14] = my_malloc(12850); dc[14] = 12864;
  my_free(free_ptrs[50]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[46]);
  ptrs[13] = my_malloc(12405); dc[13] = 12416;
  my_free(free_ptrs[64]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[12]);
  ptrs[9] = my_malloc(12694); dc[9] = 12704;
  my_free(free_ptrs[38]);
  ptrs[3] = my_malloc(12695); dc[3] = 12704;
  my_free(free_ptrs[77]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[67]);
  ptrs[2] = my_malloc(12827); dc[2] = 12840;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[29]);
  ptrs[21] = my_malloc(12962); dc[21] = 12976;
  my_free(free_ptrs[43]);
  ptrs[5] = my_malloc(12308); dc[5] = 12320;
  my_free(free_ptrs[1]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[28]);
  ptrs[19] = my_malloc(12325); dc[19] = 12336;
  my_free(free_ptrs[40]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[60]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 10, 582664);
  printf("Correct\n");
  return 0;
}
