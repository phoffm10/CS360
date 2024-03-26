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

  ptrs[1] = my_malloc(12659); dc[1] = 12672;
  free_ptrs[48] = my_malloc(2675);  free_ptrs[49] = my_malloc(2503);  free_ptrs[50] = my_malloc(2136);
  ptrs[15] = my_malloc(12985); dc[15] = 13000;
  ptrs[14] = my_malloc(12992); dc[14] = 13000;
  free_ptrs[81] = my_malloc(2218);  free_ptrs[82] = my_malloc(2447);  free_ptrs[83] = my_malloc(2446);
  free_ptrs[63] = my_malloc(2121);  free_ptrs[64] = my_malloc(2480);  free_ptrs[65] = my_malloc(2497);
  free_ptrs[57] = my_malloc(2078);  free_ptrs[58] = my_malloc(2261);  free_ptrs[59] = my_malloc(2609);
  ptrs[13] = my_malloc(12135); dc[13] = 12144;
  ptrs[5] = my_malloc(12774); dc[5] = 12784;
  free_ptrs[21] = my_malloc(2547);  free_ptrs[22] = my_malloc(2132);  free_ptrs[23] = my_malloc(2152);
  ptrs[12] = my_malloc(12100); dc[12] = 12112;
  ptrs[24] = my_malloc(12290); dc[24] = 12304;
  free_ptrs[30] = my_malloc(2065);  free_ptrs[31] = my_malloc(2400);  free_ptrs[32] = my_malloc(2578);
  ptrs[23] = my_malloc(12245); dc[23] = 12256;
  free_ptrs[42] = my_malloc(2137);  free_ptrs[43] = my_malloc(2068);  free_ptrs[44] = my_malloc(2218);
  ptrs[18] = my_malloc(12435); dc[18] = 12448;
  ptrs[20] = my_malloc(12610); dc[20] = 12624;
  ptrs[27] = my_malloc(12292); dc[27] = 12304;
  ptrs[25] = my_malloc(12403); dc[25] = 12416;
  free_ptrs[18] = my_malloc(2610);  free_ptrs[19] = my_malloc(2187);  free_ptrs[20] = my_malloc(2202);
  free_ptrs[78] = my_malloc(2312);  free_ptrs[79] = my_malloc(2475);  free_ptrs[80] = my_malloc(2229);
  free_ptrs[3] = my_malloc(2466);  free_ptrs[4] = my_malloc(2493);  free_ptrs[5] = my_malloc(2378);
  ptrs[9] = my_malloc(12175); dc[9] = 12184;
  free_ptrs[15] = my_malloc(2686);  free_ptrs[16] = my_malloc(2588);  free_ptrs[17] = my_malloc(2137);
  ptrs[22] = my_malloc(12701); dc[22] = 12712;
  free_ptrs[39] = my_malloc(2097);  free_ptrs[40] = my_malloc(2491);  free_ptrs[41] = my_malloc(2294);
  free_ptrs[12] = my_malloc(2614);  free_ptrs[13] = my_malloc(2419);  free_ptrs[14] = my_malloc(2524);
  free_ptrs[9] = my_malloc(2608);  free_ptrs[10] = my_malloc(2482);  free_ptrs[11] = my_malloc(2345);
  free_ptrs[33] = my_malloc(2465);  free_ptrs[34] = my_malloc(2064);  free_ptrs[35] = my_malloc(2206);
  free_ptrs[51] = my_malloc(2238);  free_ptrs[52] = my_malloc(2067);  free_ptrs[53] = my_malloc(2347);
  free_ptrs[84] = my_malloc(2049);  free_ptrs[85] = my_malloc(2598);  free_ptrs[86] = my_malloc(2565);
  free_ptrs[24] = my_malloc(2097);  free_ptrs[25] = my_malloc(2115);  free_ptrs[26] = my_malloc(2064);
  ptrs[2] = my_malloc(12841); dc[2] = 12856;
  free_ptrs[27] = my_malloc(2609);  free_ptrs[28] = my_malloc(2378);  free_ptrs[29] = my_malloc(2509);
  free_ptrs[75] = my_malloc(2678);  free_ptrs[76] = my_malloc(2364);  free_ptrs[77] = my_malloc(2243);
  free_ptrs[66] = my_malloc(2373);  free_ptrs[67] = my_malloc(2545);  free_ptrs[68] = my_malloc(2289);
  free_ptrs[72] = my_malloc(2448);  free_ptrs[73] = my_malloc(2057);  free_ptrs[74] = my_malloc(2312);
  free_ptrs[45] = my_malloc(2257);  free_ptrs[46] = my_malloc(2508);  free_ptrs[47] = my_malloc(2204);
  ptrs[3] = my_malloc(12417); dc[3] = 12432;
  ptrs[4] = my_malloc(12930); dc[4] = 12944;
  free_ptrs[6] = my_malloc(2380);  free_ptrs[7] = my_malloc(2128);  free_ptrs[8] = my_malloc(2137);
  free_ptrs[0] = my_malloc(2657);  free_ptrs[1] = my_malloc(2676);  free_ptrs[2] = my_malloc(2145);
  free_ptrs[60] = my_malloc(2191);  free_ptrs[61] = my_malloc(2255);  free_ptrs[62] = my_malloc(2398);
  free_ptrs[36] = my_malloc(2050);  free_ptrs[37] = my_malloc(2134);  free_ptrs[38] = my_malloc(2428);
  ptrs[16] = my_malloc(12087); dc[16] = 12096;
  ptrs[10] = my_malloc(12096); dc[10] = 12104;
  free_ptrs[69] = my_malloc(2653);  free_ptrs[70] = my_malloc(2668);  free_ptrs[71] = my_malloc(2220);
  free_ptrs[54] = my_malloc(2676);  free_ptrs[55] = my_malloc(2321);  free_ptrs[56] = my_malloc(2145);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[20]);
  ptrs[11] = my_malloc(12248); dc[11] = 12256;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[65]);
  ptrs[19] = my_malloc(12110); dc[19] = 12120;
  my_free(free_ptrs[57]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[23]);
  ptrs[26] = my_malloc(12113); dc[26] = 12128;
  my_free(free_ptrs[80]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[86]);
  ptrs[7] = my_malloc(12352); dc[7] = 12360;
  my_free(free_ptrs[9]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[8]);
  ptrs[0] = my_malloc(12031); dc[0] = 12040;
  my_free(free_ptrs[34]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[5]);
  ptrs[6] = my_malloc(12890); dc[6] = 12904;
  my_free(free_ptrs[36]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[32]);
  ptrs[21] = my_malloc(12788); dc[21] = 12800;
  my_free(free_ptrs[46]);
  ptrs[17] = my_malloc(12303); dc[17] = 12312;
  my_free(free_ptrs[69]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[81]);
  ptrs[8] = my_malloc(12791); dc[8] = 12800;
  my_free(free_ptrs[62]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[74]);
  ptrs[28] = my_malloc(12603); dc[28] = 12616;
  my_free(free_ptrs[48]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[42]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 11, 599296);
  printf("Correct\n");
  return 0;
}
