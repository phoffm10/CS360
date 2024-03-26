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

  free_ptrs[30] = my_malloc(2422);  free_ptrs[31] = my_malloc(2152);  free_ptrs[32] = my_malloc(2429);
  ptrs[13] = my_malloc(12594); dc[13] = 12608;
  free_ptrs[18] = my_malloc(2153);  free_ptrs[19] = my_malloc(2212);  free_ptrs[20] = my_malloc(2393);
  free_ptrs[0] = my_malloc(2388);  free_ptrs[1] = my_malloc(2392);  free_ptrs[2] = my_malloc(2165);
  ptrs[14] = my_malloc(12567); dc[14] = 12576;
  ptrs[17] = my_malloc(12906); dc[17] = 12920;
  ptrs[1] = my_malloc(12439); dc[1] = 12448;
  free_ptrs[15] = my_malloc(2453);  free_ptrs[16] = my_malloc(2192);  free_ptrs[17] = my_malloc(2624);
  free_ptrs[39] = my_malloc(2319);  free_ptrs[40] = my_malloc(2676);  free_ptrs[41] = my_malloc(2265);
  free_ptrs[45] = my_malloc(2174);  free_ptrs[46] = my_malloc(2188);  free_ptrs[47] = my_malloc(2257);
  ptrs[7] = my_malloc(12596); dc[7] = 12608;
  ptrs[8] = my_malloc(12543); dc[8] = 12552;
  ptrs[25] = my_malloc(12895); dc[25] = 12904;
  free_ptrs[21] = my_malloc(2475);  free_ptrs[22] = my_malloc(2678);  free_ptrs[23] = my_malloc(2673);
  free_ptrs[72] = my_malloc(2362);  free_ptrs[73] = my_malloc(2630);  free_ptrs[74] = my_malloc(2530);
  free_ptrs[66] = my_malloc(2133);  free_ptrs[67] = my_malloc(2315);  free_ptrs[68] = my_malloc(2380);
  ptrs[16] = my_malloc(12550); dc[16] = 12560;
  ptrs[0] = my_malloc(12062); dc[0] = 12072;
  free_ptrs[27] = my_malloc(2078);  free_ptrs[28] = my_malloc(2223);  free_ptrs[29] = my_malloc(2337);
  free_ptrs[24] = my_malloc(2318);  free_ptrs[25] = my_malloc(2599);  free_ptrs[26] = my_malloc(2234);
  free_ptrs[51] = my_malloc(2048);  free_ptrs[52] = my_malloc(2222);  free_ptrs[53] = my_malloc(2351);
  ptrs[20] = my_malloc(12490); dc[20] = 12504;
  ptrs[4] = my_malloc(12010); dc[4] = 12024;
  free_ptrs[60] = my_malloc(2352);  free_ptrs[61] = my_malloc(2053);  free_ptrs[62] = my_malloc(2677);
  ptrs[11] = my_malloc(12515); dc[11] = 12528;
  ptrs[22] = my_malloc(12932); dc[22] = 12944;
  free_ptrs[54] = my_malloc(2088);  free_ptrs[55] = my_malloc(2058);  free_ptrs[56] = my_malloc(2626);
  free_ptrs[9] = my_malloc(2600);  free_ptrs[10] = my_malloc(2539);  free_ptrs[11] = my_malloc(2593);
  free_ptrs[57] = my_malloc(2498);  free_ptrs[58] = my_malloc(2523);  free_ptrs[59] = my_malloc(2643);
  free_ptrs[48] = my_malloc(2314);  free_ptrs[49] = my_malloc(2073);  free_ptrs[50] = my_malloc(2249);
  free_ptrs[12] = my_malloc(2106);  free_ptrs[13] = my_malloc(2604);  free_ptrs[14] = my_malloc(2399);
  ptrs[10] = my_malloc(12503); dc[10] = 12512;
  free_ptrs[36] = my_malloc(2514);  free_ptrs[37] = my_malloc(2635);  free_ptrs[38] = my_malloc(2223);
  free_ptrs[69] = my_malloc(2121);  free_ptrs[70] = my_malloc(2645);  free_ptrs[71] = my_malloc(2603);
  free_ptrs[63] = my_malloc(2264);  free_ptrs[64] = my_malloc(2390);  free_ptrs[65] = my_malloc(2402);
  free_ptrs[42] = my_malloc(2358);  free_ptrs[43] = my_malloc(2519);  free_ptrs[44] = my_malloc(2514);
  free_ptrs[33] = my_malloc(2657);  free_ptrs[34] = my_malloc(2097);  free_ptrs[35] = my_malloc(2430);
  free_ptrs[78] = my_malloc(2662);  free_ptrs[79] = my_malloc(2313);  free_ptrs[80] = my_malloc(2102);
  free_ptrs[75] = my_malloc(2459);  free_ptrs[76] = my_malloc(2091);  free_ptrs[77] = my_malloc(2343);
  free_ptrs[3] = my_malloc(2386);  free_ptrs[4] = my_malloc(2152);  free_ptrs[5] = my_malloc(2679);
  free_ptrs[6] = my_malloc(2680);  free_ptrs[7] = my_malloc(2341);  free_ptrs[8] = my_malloc(2139);
  ptrs[15] = my_malloc(12412); dc[15] = 12424;
  ptrs[5] = my_malloc(12729); dc[5] = 12744;
  ptrs[3] = my_malloc(12548); dc[3] = 12560;
  my_free(free_ptrs[17]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[40]);
  ptrs[19] = my_malloc(12458); dc[19] = 12472;
  my_free(free_ptrs[25]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[53]);
  ptrs[23] = my_malloc(12312); dc[23] = 12320;
  my_free(free_ptrs[22]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[8]);
  ptrs[9] = my_malloc(12379); dc[9] = 12392;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[54]);
  ptrs[21] = my_malloc(12663); dc[21] = 12672;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[49]);
  ptrs[26] = my_malloc(12000); dc[26] = 12008;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[1]);
  ptrs[24] = my_malloc(12105); dc[24] = 12120;
  my_free(free_ptrs[5]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[6]);
  ptrs[2] = my_malloc(12096); dc[2] = 12104;
  my_free(free_ptrs[43]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[59]);
  ptrs[6] = my_malloc(12914); dc[6] = 12928;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[77]);
  ptrs[12] = my_malloc(12875); dc[12] = 12888;
  my_free(free_ptrs[67]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[57]);
  ptrs[18] = my_malloc(12811); dc[18] = 12824;
  my_free(free_ptrs[27]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[37]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 8, 559400);
  printf("Correct\n");
  return 0;
}
