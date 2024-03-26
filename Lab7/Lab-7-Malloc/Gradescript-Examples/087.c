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

  ptrs[12] = my_malloc(12562); dc[12] = 12576;
  ptrs[19] = my_malloc(12964); dc[19] = 12976;
  free_ptrs[45] = my_malloc(2404);  free_ptrs[46] = my_malloc(2432);  free_ptrs[47] = my_malloc(2113);
  free_ptrs[33] = my_malloc(2127);  free_ptrs[34] = my_malloc(2079);  free_ptrs[35] = my_malloc(2521);
  ptrs[1] = my_malloc(12057); dc[1] = 12072;
  free_ptrs[36] = my_malloc(2306);  free_ptrs[37] = my_malloc(2512);  free_ptrs[38] = my_malloc(2198);
  ptrs[11] = my_malloc(12550); dc[11] = 12560;
  free_ptrs[15] = my_malloc(2647);  free_ptrs[16] = my_malloc(2686);  free_ptrs[17] = my_malloc(2080);
  free_ptrs[0] = my_malloc(2188);  free_ptrs[1] = my_malloc(2091);  free_ptrs[2] = my_malloc(2293);
  free_ptrs[69] = my_malloc(2675);  free_ptrs[70] = my_malloc(2322);  free_ptrs[71] = my_malloc(2125);
  free_ptrs[66] = my_malloc(2262);  free_ptrs[67] = my_malloc(2680);  free_ptrs[68] = my_malloc(2159);
  free_ptrs[42] = my_malloc(2691);  free_ptrs[43] = my_malloc(2560);  free_ptrs[44] = my_malloc(2449);
  free_ptrs[39] = my_malloc(2462);  free_ptrs[40] = my_malloc(2264);  free_ptrs[41] = my_malloc(2387);
  ptrs[26] = my_malloc(12991); dc[26] = 13000;
  free_ptrs[51] = my_malloc(2075);  free_ptrs[52] = my_malloc(2513);  free_ptrs[53] = my_malloc(2576);
  free_ptrs[78] = my_malloc(2191);  free_ptrs[79] = my_malloc(2652);  free_ptrs[80] = my_malloc(2436);
  free_ptrs[57] = my_malloc(2335);  free_ptrs[58] = my_malloc(2070);  free_ptrs[59] = my_malloc(2474);
  free_ptrs[21] = my_malloc(2286);  free_ptrs[22] = my_malloc(2477);  free_ptrs[23] = my_malloc(2169);
  free_ptrs[24] = my_malloc(2395);  free_ptrs[25] = my_malloc(2227);  free_ptrs[26] = my_malloc(2375);
  ptrs[25] = my_malloc(12393); dc[25] = 12408;
  free_ptrs[54] = my_malloc(2189);  free_ptrs[55] = my_malloc(2664);  free_ptrs[56] = my_malloc(2076);
  free_ptrs[27] = my_malloc(2165);  free_ptrs[28] = my_malloc(2619);  free_ptrs[29] = my_malloc(2273);
  free_ptrs[30] = my_malloc(2358);  free_ptrs[31] = my_malloc(2280);  free_ptrs[32] = my_malloc(2587);
  free_ptrs[9] = my_malloc(2467);  free_ptrs[10] = my_malloc(2281);  free_ptrs[11] = my_malloc(2528);
  ptrs[15] = my_malloc(12103); dc[15] = 12112;
  ptrs[16] = my_malloc(12581); dc[16] = 12592;
  ptrs[2] = my_malloc(12471); dc[2] = 12480;
  free_ptrs[72] = my_malloc(2557);  free_ptrs[73] = my_malloc(2272);  free_ptrs[74] = my_malloc(2484);
  free_ptrs[12] = my_malloc(2090);  free_ptrs[13] = my_malloc(2232);  free_ptrs[14] = my_malloc(2374);
  free_ptrs[75] = my_malloc(2265);  free_ptrs[76] = my_malloc(2666);  free_ptrs[77] = my_malloc(2096);
  free_ptrs[6] = my_malloc(2334);  free_ptrs[7] = my_malloc(2678);  free_ptrs[8] = my_malloc(2562);
  free_ptrs[60] = my_malloc(2611);  free_ptrs[61] = my_malloc(2595);  free_ptrs[62] = my_malloc(2479);
  ptrs[24] = my_malloc(12136); dc[24] = 12144;
  free_ptrs[63] = my_malloc(2151);  free_ptrs[64] = my_malloc(2631);  free_ptrs[65] = my_malloc(2173);
  free_ptrs[3] = my_malloc(2092);  free_ptrs[4] = my_malloc(2564);  free_ptrs[5] = my_malloc(2272);
  free_ptrs[48] = my_malloc(2273);  free_ptrs[49] = my_malloc(2170);  free_ptrs[50] = my_malloc(2413);
  free_ptrs[18] = my_malloc(2439);  free_ptrs[19] = my_malloc(2340);  free_ptrs[20] = my_malloc(2080);
  ptrs[5] = my_malloc(12604); dc[5] = 12616;
  my_free(free_ptrs[0]);
  ptrs[18] = my_malloc(12569); dc[18] = 12584;
  my_free(free_ptrs[3]);
  my_free(free_ptrs[70]);
  ptrs[21] = my_malloc(12138); dc[21] = 12152;
  my_free(free_ptrs[74]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[37]);
  ptrs[17] = my_malloc(12989); dc[17] = 13000;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[35]);
  ptrs[9] = my_malloc(12533); dc[9] = 12544;
  my_free(free_ptrs[54]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[12]);
  ptrs[8] = my_malloc(12341); dc[8] = 12352;
  ptrs[22] = my_malloc(12203); dc[22] = 12216;
  my_free(free_ptrs[41]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[15]);
  ptrs[13] = my_malloc(12261); dc[13] = 12272;
  ptrs[10] = my_malloc(12526); dc[10] = 12536;
  my_free(free_ptrs[79]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[64]);
  ptrs[20] = my_malloc(12968); dc[20] = 12976;
  my_free(free_ptrs[45]);
  my_free(free_ptrs[26]);
  ptrs[23] = my_malloc(12635); dc[23] = 12648;
  ptrs[6] = my_malloc(12384); dc[6] = 12392;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[72]);
  ptrs[4] = my_malloc(12848); dc[4] = 12856;
  my_free(free_ptrs[31]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[30]);
  ptrs[7] = my_malloc(12022); dc[7] = 12032;
  my_free(free_ptrs[48]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[76]);
  ptrs[3] = my_malloc(12887); dc[3] = 12896;
  ptrs[0] = my_malloc(12973); dc[0] = 12984;
  my_free(free_ptrs[47]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[65]);
  ptrs[14] = my_malloc(12686); dc[14] = 12696;
  my_free(free_ptrs[59]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[77]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 7, 559856);
  printf("Correct\n");
  return 0;
}
