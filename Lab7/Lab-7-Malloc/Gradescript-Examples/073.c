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

  ptrs[7] = my_malloc(12998); dc[7] = 13008;
  free_ptrs[6] = my_malloc(2250);  free_ptrs[7] = my_malloc(2640);  free_ptrs[8] = my_malloc(2556);
  free_ptrs[30] = my_malloc(2648);  free_ptrs[31] = my_malloc(2079);  free_ptrs[32] = my_malloc(2548);
  free_ptrs[36] = my_malloc(2126);  free_ptrs[37] = my_malloc(2148);  free_ptrs[38] = my_malloc(2338);
  free_ptrs[51] = my_malloc(2099);  free_ptrs[52] = my_malloc(2636);  free_ptrs[53] = my_malloc(2517);
  free_ptrs[75] = my_malloc(2258);  free_ptrs[76] = my_malloc(2372);  free_ptrs[77] = my_malloc(2446);
  ptrs[0] = my_malloc(12741); dc[0] = 12752;
  free_ptrs[3] = my_malloc(2282);  free_ptrs[4] = my_malloc(2148);  free_ptrs[5] = my_malloc(2117);
  ptrs[5] = my_malloc(12924); dc[5] = 12936;
  ptrs[17] = my_malloc(12677); dc[17] = 12688;
  free_ptrs[0] = my_malloc(2405);  free_ptrs[1] = my_malloc(2141);  free_ptrs[2] = my_malloc(2294);
  ptrs[8] = my_malloc(12245); dc[8] = 12256;
  free_ptrs[9] = my_malloc(2195);  free_ptrs[10] = my_malloc(2216);  free_ptrs[11] = my_malloc(2424);
  free_ptrs[57] = my_malloc(2220);  free_ptrs[58] = my_malloc(2106);  free_ptrs[59] = my_malloc(2111);
  free_ptrs[81] = my_malloc(2191);  free_ptrs[82] = my_malloc(2418);  free_ptrs[83] = my_malloc(2499);
  free_ptrs[60] = my_malloc(2421);  free_ptrs[61] = my_malloc(2331);  free_ptrs[62] = my_malloc(2491);
  ptrs[26] = my_malloc(12503); dc[26] = 12512;
  ptrs[10] = my_malloc(12302); dc[10] = 12312;
  free_ptrs[33] = my_malloc(2653);  free_ptrs[34] = my_malloc(2099);  free_ptrs[35] = my_malloc(2618);
  ptrs[1] = my_malloc(12241); dc[1] = 12256;
  free_ptrs[78] = my_malloc(2352);  free_ptrs[79] = my_malloc(2278);  free_ptrs[80] = my_malloc(2457);
  ptrs[11] = my_malloc(12110); dc[11] = 12120;
  free_ptrs[48] = my_malloc(2384);  free_ptrs[49] = my_malloc(2663);  free_ptrs[50] = my_malloc(2201);
  free_ptrs[45] = my_malloc(2688);  free_ptrs[46] = my_malloc(2183);  free_ptrs[47] = my_malloc(2316);
  ptrs[4] = my_malloc(12224); dc[4] = 12232;
  free_ptrs[42] = my_malloc(2562);  free_ptrs[43] = my_malloc(2399);  free_ptrs[44] = my_malloc(2690);
  free_ptrs[12] = my_malloc(2510);  free_ptrs[13] = my_malloc(2066);  free_ptrs[14] = my_malloc(2461);
  free_ptrs[69] = my_malloc(2188);  free_ptrs[70] = my_malloc(2613);  free_ptrs[71] = my_malloc(2436);
  free_ptrs[27] = my_malloc(2261);  free_ptrs[28] = my_malloc(2221);  free_ptrs[29] = my_malloc(2242);
  ptrs[27] = my_malloc(12986); dc[27] = 13000;
  free_ptrs[24] = my_malloc(2503);  free_ptrs[25] = my_malloc(2187);  free_ptrs[26] = my_malloc(2439);
  free_ptrs[39] = my_malloc(2406);  free_ptrs[40] = my_malloc(2253);  free_ptrs[41] = my_malloc(2099);
  ptrs[2] = my_malloc(12343); dc[2] = 12352;
  free_ptrs[66] = my_malloc(2680);  free_ptrs[67] = my_malloc(2609);  free_ptrs[68] = my_malloc(2223);
  free_ptrs[21] = my_malloc(2211);  free_ptrs[22] = my_malloc(2609);  free_ptrs[23] = my_malloc(2500);
  free_ptrs[54] = my_malloc(2546);  free_ptrs[55] = my_malloc(2276);  free_ptrs[56] = my_malloc(2485);
  free_ptrs[72] = my_malloc(2248);  free_ptrs[73] = my_malloc(2628);  free_ptrs[74] = my_malloc(2185);
  free_ptrs[18] = my_malloc(2058);  free_ptrs[19] = my_malloc(2564);  free_ptrs[20] = my_malloc(2473);
  ptrs[20] = my_malloc(12696); dc[20] = 12704;
  free_ptrs[63] = my_malloc(2385);  free_ptrs[64] = my_malloc(2387);  free_ptrs[65] = my_malloc(2394);
  free_ptrs[15] = my_malloc(2534);  free_ptrs[16] = my_malloc(2260);  free_ptrs[17] = my_malloc(2362);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[40]);
  ptrs[15] = my_malloc(12223); dc[15] = 12232;
  my_free(free_ptrs[53]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[73]);
  ptrs[14] = my_malloc(12166); dc[14] = 12176;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[32]);
  ptrs[12] = my_malloc(12706); dc[12] = 12720;
  ptrs[25] = my_malloc(12705); dc[25] = 12720;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[72]);
  ptrs[19] = my_malloc(12380); dc[19] = 12392;
  my_free(free_ptrs[82]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[43]);
  ptrs[13] = my_malloc(12117); dc[13] = 12128;
  my_free(free_ptrs[34]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[17]);
  ptrs[24] = my_malloc(12168); dc[24] = 12176;
  my_free(free_ptrs[9]);
  ptrs[6] = my_malloc(12008); dc[6] = 12016;
  my_free(free_ptrs[41]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[39]);
  ptrs[23] = my_malloc(12603); dc[23] = 12616;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[55]);
  ptrs[3] = my_malloc(12063); dc[3] = 12072;
  my_free(free_ptrs[0]);
  my_free(free_ptrs[68]);
  ptrs[16] = my_malloc(12261); dc[16] = 12272;
  ptrs[18] = my_malloc(12401); dc[18] = 12416;
  my_free(free_ptrs[51]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[46]);
  ptrs[9] = my_malloc(12613); dc[9] = 12624;
  ptrs[22] = my_malloc(12563); dc[22] = 12576;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[57]);
  ptrs[21] = my_malloc(12890); dc[21] = 12904;
  my_free(free_ptrs[63]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[31]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 11, 578544);
  printf("Correct\n");
  return 0;
}
