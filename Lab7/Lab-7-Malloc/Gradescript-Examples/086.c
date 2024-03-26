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

  ptrs[3] = my_malloc(12078); dc[3] = 12088;
  free_ptrs[6] = my_malloc(2274);  free_ptrs[7] = my_malloc(2609);  free_ptrs[8] = my_malloc(2607);
  ptrs[25] = my_malloc(12905); dc[25] = 12920;
  ptrs[23] = my_malloc(12570); dc[23] = 12584;
  ptrs[1] = my_malloc(12393); dc[1] = 12408;
  free_ptrs[54] = my_malloc(2298);  free_ptrs[55] = my_malloc(2412);  free_ptrs[56] = my_malloc(2576);
  free_ptrs[0] = my_malloc(2488);  free_ptrs[1] = my_malloc(2152);  free_ptrs[2] = my_malloc(2529);
  ptrs[5] = my_malloc(12899); dc[5] = 12912;
  ptrs[7] = my_malloc(12926); dc[7] = 12936;
  ptrs[6] = my_malloc(12420); dc[6] = 12432;
  free_ptrs[9] = my_malloc(2102);  free_ptrs[10] = my_malloc(2073);  free_ptrs[11] = my_malloc(2671);
  ptrs[19] = my_malloc(12252); dc[19] = 12264;
  free_ptrs[63] = my_malloc(2302);  free_ptrs[64] = my_malloc(2452);  free_ptrs[65] = my_malloc(2348);
  ptrs[0] = my_malloc(12120); dc[0] = 12128;
  ptrs[10] = my_malloc(12721); dc[10] = 12736;
  free_ptrs[30] = my_malloc(2630);  free_ptrs[31] = my_malloc(2384);  free_ptrs[32] = my_malloc(2557);
  ptrs[15] = my_malloc(12294); dc[15] = 12304;
  free_ptrs[45] = my_malloc(2098);  free_ptrs[46] = my_malloc(2124);  free_ptrs[47] = my_malloc(2403);
  free_ptrs[12] = my_malloc(2614);  free_ptrs[13] = my_malloc(2048);  free_ptrs[14] = my_malloc(2639);
  ptrs[14] = my_malloc(12521); dc[14] = 12536;
  ptrs[21] = my_malloc(12313); dc[21] = 12328;
  free_ptrs[18] = my_malloc(2123);  free_ptrs[19] = my_malloc(2446);  free_ptrs[20] = my_malloc(2273);
  free_ptrs[51] = my_malloc(2328);  free_ptrs[52] = my_malloc(2326);  free_ptrs[53] = my_malloc(2661);
  free_ptrs[33] = my_malloc(2233);  free_ptrs[34] = my_malloc(2603);  free_ptrs[35] = my_malloc(2372);
  free_ptrs[36] = my_malloc(2218);  free_ptrs[37] = my_malloc(2407);  free_ptrs[38] = my_malloc(2073);
  free_ptrs[57] = my_malloc(2628);  free_ptrs[58] = my_malloc(2161);  free_ptrs[59] = my_malloc(2247);
  free_ptrs[42] = my_malloc(2624);  free_ptrs[43] = my_malloc(2681);  free_ptrs[44] = my_malloc(2202);
  free_ptrs[78] = my_malloc(2546);  free_ptrs[79] = my_malloc(2063);  free_ptrs[80] = my_malloc(2630);
  free_ptrs[3] = my_malloc(2672);  free_ptrs[4] = my_malloc(2222);  free_ptrs[5] = my_malloc(2223);
  free_ptrs[39] = my_malloc(2693);  free_ptrs[40] = my_malloc(2478);  free_ptrs[41] = my_malloc(2623);
  free_ptrs[66] = my_malloc(2365);  free_ptrs[67] = my_malloc(2477);  free_ptrs[68] = my_malloc(2594);
  ptrs[16] = my_malloc(12704); dc[16] = 12712;
  free_ptrs[72] = my_malloc(2646);  free_ptrs[73] = my_malloc(2474);  free_ptrs[74] = my_malloc(2494);
  free_ptrs[21] = my_malloc(2063);  free_ptrs[22] = my_malloc(2256);  free_ptrs[23] = my_malloc(2401);
  free_ptrs[48] = my_malloc(2282);  free_ptrs[49] = my_malloc(2669);  free_ptrs[50] = my_malloc(2511);
  ptrs[26] = my_malloc(12122); dc[26] = 12136;
  free_ptrs[69] = my_malloc(2305);  free_ptrs[70] = my_malloc(2515);  free_ptrs[71] = my_malloc(2481);
  free_ptrs[60] = my_malloc(2430);  free_ptrs[61] = my_malloc(2097);  free_ptrs[62] = my_malloc(2389);
  ptrs[9] = my_malloc(12373); dc[9] = 12384;
  free_ptrs[75] = my_malloc(2565);  free_ptrs[76] = my_malloc(2681);  free_ptrs[77] = my_malloc(2275);
  ptrs[17] = my_malloc(12572); dc[17] = 12584;
  free_ptrs[24] = my_malloc(2120);  free_ptrs[25] = my_malloc(2691);  free_ptrs[26] = my_malloc(2608);
  free_ptrs[27] = my_malloc(2148);  free_ptrs[28] = my_malloc(2149);  free_ptrs[29] = my_malloc(2675);
  free_ptrs[15] = my_malloc(2349);  free_ptrs[16] = my_malloc(2068);  free_ptrs[17] = my_malloc(2580);
  my_free(free_ptrs[18]);
  ptrs[13] = my_malloc(12468); dc[13] = 12480;
  ptrs[8] = my_malloc(12641); dc[8] = 12656;
  my_free(free_ptrs[67]);
  my_free(free_ptrs[42]);
  ptrs[24] = my_malloc(12259); dc[24] = 12272;
  my_free(free_ptrs[19]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[26]);
  ptrs[18] = my_malloc(12677); dc[18] = 12688;
  my_free(free_ptrs[52]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[43]);
  ptrs[11] = my_malloc(12213); dc[11] = 12224;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[15]);
  ptrs[20] = my_malloc(12132); dc[20] = 12144;
  my_free(free_ptrs[31]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[56]);
  ptrs[2] = my_malloc(12466); dc[2] = 12480;
  my_free(free_ptrs[5]);
  my_free(free_ptrs[17]);
  ptrs[4] = my_malloc(12092); dc[4] = 12104;
  my_free(free_ptrs[46]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[16]);
  ptrs[22] = my_malloc(12078); dc[22] = 12088;
  my_free(free_ptrs[61]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[58]);
  ptrs[12] = my_malloc(12765); dc[12] = 12776;
  my_free(free_ptrs[71]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 11, 557488);
  printf("Correct\n");
  return 0;
}
