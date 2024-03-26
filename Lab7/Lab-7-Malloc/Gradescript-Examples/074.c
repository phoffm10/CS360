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

  free_ptrs[57] = my_malloc(2332);  free_ptrs[58] = my_malloc(2184);  free_ptrs[59] = my_malloc(2119);
  free_ptrs[27] = my_malloc(2468);  free_ptrs[28] = my_malloc(2573);  free_ptrs[29] = my_malloc(2484);
  free_ptrs[6] = my_malloc(2594);  free_ptrs[7] = my_malloc(2112);  free_ptrs[8] = my_malloc(2602);
  free_ptrs[54] = my_malloc(2427);  free_ptrs[55] = my_malloc(2054);  free_ptrs[56] = my_malloc(2273);
  ptrs[28] = my_malloc(12797); dc[28] = 12808;
  free_ptrs[18] = my_malloc(2370);  free_ptrs[19] = my_malloc(2070);  free_ptrs[20] = my_malloc(2278);
  ptrs[26] = my_malloc(12371); dc[26] = 12384;
  free_ptrs[15] = my_malloc(2411);  free_ptrs[16] = my_malloc(2340);  free_ptrs[17] = my_malloc(2543);
  ptrs[9] = my_malloc(12774); dc[9] = 12784;
  free_ptrs[51] = my_malloc(2550);  free_ptrs[52] = my_malloc(2300);  free_ptrs[53] = my_malloc(2388);
  free_ptrs[21] = my_malloc(2378);  free_ptrs[22] = my_malloc(2385);  free_ptrs[23] = my_malloc(2604);
  free_ptrs[72] = my_malloc(2621);  free_ptrs[73] = my_malloc(2243);  free_ptrs[74] = my_malloc(2294);
  ptrs[17] = my_malloc(12741); dc[17] = 12752;
  ptrs[4] = my_malloc(12333); dc[4] = 12344;
  free_ptrs[3] = my_malloc(2196);  free_ptrs[4] = my_malloc(2167);  free_ptrs[5] = my_malloc(2598);
  ptrs[8] = my_malloc(12594); dc[8] = 12608;
  ptrs[1] = my_malloc(12906); dc[1] = 12920;
  free_ptrs[39] = my_malloc(2668);  free_ptrs[40] = my_malloc(2670);  free_ptrs[41] = my_malloc(2328);
  free_ptrs[12] = my_malloc(2450);  free_ptrs[13] = my_malloc(2428);  free_ptrs[14] = my_malloc(2056);
  free_ptrs[60] = my_malloc(2422);  free_ptrs[61] = my_malloc(2382);  free_ptrs[62] = my_malloc(2439);
  free_ptrs[9] = my_malloc(2072);  free_ptrs[10] = my_malloc(2461);  free_ptrs[11] = my_malloc(2131);
  free_ptrs[0] = my_malloc(2558);  free_ptrs[1] = my_malloc(2540);  free_ptrs[2] = my_malloc(2131);
  ptrs[6] = my_malloc(12973); dc[6] = 12984;
  free_ptrs[30] = my_malloc(2112);  free_ptrs[31] = my_malloc(2312);  free_ptrs[32] = my_malloc(2094);
  ptrs[21] = my_malloc(12714); dc[21] = 12728;
  free_ptrs[63] = my_malloc(2211);  free_ptrs[64] = my_malloc(2236);  free_ptrs[65] = my_malloc(2479);
  free_ptrs[24] = my_malloc(2605);  free_ptrs[25] = my_malloc(2293);  free_ptrs[26] = my_malloc(2184);
  free_ptrs[66] = my_malloc(2173);  free_ptrs[67] = my_malloc(2370);  free_ptrs[68] = my_malloc(2157);
  ptrs[20] = my_malloc(12533); dc[20] = 12544;
  ptrs[14] = my_malloc(12330); dc[14] = 12344;
  free_ptrs[33] = my_malloc(2247);  free_ptrs[34] = my_malloc(2687);  free_ptrs[35] = my_malloc(2483);
  free_ptrs[42] = my_malloc(2645);  free_ptrs[43] = my_malloc(2367);  free_ptrs[44] = my_malloc(2494);
  free_ptrs[69] = my_malloc(2258);  free_ptrs[70] = my_malloc(2578);  free_ptrs[71] = my_malloc(2242);
  ptrs[27] = my_malloc(12787); dc[27] = 12800;
  free_ptrs[84] = my_malloc(2313);  free_ptrs[85] = my_malloc(2633);  free_ptrs[86] = my_malloc(2314);
  ptrs[23] = my_malloc(12667); dc[23] = 12680;
  free_ptrs[48] = my_malloc(2568);  free_ptrs[49] = my_malloc(2085);  free_ptrs[50] = my_malloc(2086);
  free_ptrs[81] = my_malloc(2668);  free_ptrs[82] = my_malloc(2140);  free_ptrs[83] = my_malloc(2135);
  free_ptrs[36] = my_malloc(2272);  free_ptrs[37] = my_malloc(2456);  free_ptrs[38] = my_malloc(2207);
  free_ptrs[78] = my_malloc(2085);  free_ptrs[79] = my_malloc(2296);  free_ptrs[80] = my_malloc(2301);
  ptrs[5] = my_malloc(12980); dc[5] = 12992;
  free_ptrs[75] = my_malloc(2192);  free_ptrs[76] = my_malloc(2214);  free_ptrs[77] = my_malloc(2684);
  free_ptrs[45] = my_malloc(2544);  free_ptrs[46] = my_malloc(2359);  free_ptrs[47] = my_malloc(2413);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[48]);
  ptrs[19] = my_malloc(12093); dc[19] = 12104;
  my_free(free_ptrs[77]);
  ptrs[22] = my_malloc(12687); dc[22] = 12696;
  my_free(free_ptrs[3]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[65]);
  ptrs[11] = my_malloc(12446); dc[11] = 12456;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[15]);
  ptrs[12] = my_malloc(12502); dc[12] = 12512;
  my_free(free_ptrs[8]);
  ptrs[24] = my_malloc(12044); dc[24] = 12056;
  my_free(free_ptrs[36]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[80]);
  ptrs[10] = my_malloc(12106); dc[10] = 12120;
  my_free(free_ptrs[9]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[41]);
  ptrs[3] = my_malloc(12871); dc[3] = 12880;
  ptrs[15] = my_malloc(12031); dc[15] = 12040;
  ptrs[7] = my_malloc(12743); dc[7] = 12752;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[19]);
  ptrs[18] = my_malloc(12294); dc[18] = 12304;
  my_free(free_ptrs[17]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[61]);
  ptrs[0] = my_malloc(12593); dc[0] = 12608;
  my_free(free_ptrs[86]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[25]);
  ptrs[13] = my_malloc(12261); dc[13] = 12272;
  my_free(free_ptrs[35]);
  ptrs[25] = my_malloc(12194); dc[25] = 12208;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[5]);
  ptrs[16] = my_malloc(12137); dc[16] = 12152;
  my_free(free_ptrs[60]);
  ptrs[2] = my_malloc(12347); dc[2] = 12360;
  my_free(free_ptrs[68]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[59]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 12, 600760);
  printf("Correct\n");
  return 0;
}
