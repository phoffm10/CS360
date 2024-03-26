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

  ptrs[6] = my_malloc(12491); dc[6] = 12504;
  free_ptrs[63] = my_malloc(2097);  free_ptrs[64] = my_malloc(2051);  free_ptrs[65] = my_malloc(2286);
  free_ptrs[9] = my_malloc(2306);  free_ptrs[10] = my_malloc(2306);  free_ptrs[11] = my_malloc(2235);
  free_ptrs[57] = my_malloc(2342);  free_ptrs[58] = my_malloc(2444);  free_ptrs[59] = my_malloc(2404);
  free_ptrs[12] = my_malloc(2325);  free_ptrs[13] = my_malloc(2520);  free_ptrs[14] = my_malloc(2662);
  free_ptrs[48] = my_malloc(2372);  free_ptrs[49] = my_malloc(2054);  free_ptrs[50] = my_malloc(2657);
  ptrs[4] = my_malloc(12875); dc[4] = 12888;
  free_ptrs[21] = my_malloc(2467);  free_ptrs[22] = my_malloc(2212);  free_ptrs[23] = my_malloc(2293);
  free_ptrs[15] = my_malloc(2129);  free_ptrs[16] = my_malloc(2277);  free_ptrs[17] = my_malloc(2086);
  ptrs[9] = my_malloc(12700); dc[9] = 12712;
  ptrs[1] = my_malloc(12416); dc[1] = 12424;
  free_ptrs[72] = my_malloc(2227);  free_ptrs[73] = my_malloc(2513);  free_ptrs[74] = my_malloc(2297);
  free_ptrs[51] = my_malloc(2599);  free_ptrs[52] = my_malloc(2182);  free_ptrs[53] = my_malloc(2290);
  free_ptrs[6] = my_malloc(2474);  free_ptrs[7] = my_malloc(2048);  free_ptrs[8] = my_malloc(2634);
  free_ptrs[33] = my_malloc(2350);  free_ptrs[34] = my_malloc(2077);  free_ptrs[35] = my_malloc(2227);
  free_ptrs[42] = my_malloc(2276);  free_ptrs[43] = my_malloc(2357);  free_ptrs[44] = my_malloc(2383);
  free_ptrs[30] = my_malloc(2593);  free_ptrs[31] = my_malloc(2492);  free_ptrs[32] = my_malloc(2094);
  free_ptrs[69] = my_malloc(2256);  free_ptrs[70] = my_malloc(2542);  free_ptrs[71] = my_malloc(2326);
  free_ptrs[39] = my_malloc(2251);  free_ptrs[40] = my_malloc(2444);  free_ptrs[41] = my_malloc(2386);
  free_ptrs[0] = my_malloc(2271);  free_ptrs[1] = my_malloc(2346);  free_ptrs[2] = my_malloc(2250);
  free_ptrs[36] = my_malloc(2196);  free_ptrs[37] = my_malloc(2474);  free_ptrs[38] = my_malloc(2596);
  ptrs[10] = my_malloc(12112); dc[10] = 12120;
  free_ptrs[27] = my_malloc(2512);  free_ptrs[28] = my_malloc(2182);  free_ptrs[29] = my_malloc(2655);
  ptrs[16] = my_malloc(12303); dc[16] = 12312;
  free_ptrs[54] = my_malloc(2561);  free_ptrs[55] = my_malloc(2277);  free_ptrs[56] = my_malloc(2086);
  ptrs[3] = my_malloc(12813); dc[3] = 12824;
  ptrs[13] = my_malloc(12531); dc[13] = 12544;
  ptrs[17] = my_malloc(12739); dc[17] = 12752;
  ptrs[5] = my_malloc(12138); dc[5] = 12152;
  free_ptrs[78] = my_malloc(2188);  free_ptrs[79] = my_malloc(2365);  free_ptrs[80] = my_malloc(2306);
  free_ptrs[24] = my_malloc(2320);  free_ptrs[25] = my_malloc(2421);  free_ptrs[26] = my_malloc(2487);
  ptrs[8] = my_malloc(12592); dc[8] = 12600;
  free_ptrs[66] = my_malloc(2072);  free_ptrs[67] = my_malloc(2163);  free_ptrs[68] = my_malloc(2172);
  ptrs[19] = my_malloc(12179); dc[19] = 12192;
  free_ptrs[3] = my_malloc(2187);  free_ptrs[4] = my_malloc(2126);  free_ptrs[5] = my_malloc(2133);
  free_ptrs[45] = my_malloc(2155);  free_ptrs[46] = my_malloc(2330);  free_ptrs[47] = my_malloc(2213);
  free_ptrs[75] = my_malloc(2060);  free_ptrs[76] = my_malloc(2634);  free_ptrs[77] = my_malloc(2684);
  free_ptrs[18] = my_malloc(2653);  free_ptrs[19] = my_malloc(2658);  free_ptrs[20] = my_malloc(2418);
  free_ptrs[81] = my_malloc(2250);  free_ptrs[82] = my_malloc(2418);  free_ptrs[83] = my_malloc(2368);
  free_ptrs[60] = my_malloc(2400);  free_ptrs[61] = my_malloc(2208);  free_ptrs[62] = my_malloc(2370);
  ptrs[21] = my_malloc(12312); dc[21] = 12320;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[23]);
  ptrs[26] = my_malloc(12737); dc[26] = 12752;
  my_free(free_ptrs[19]);
  my_free(free_ptrs[74]);
  ptrs[25] = my_malloc(12224); dc[25] = 12232;
  ptrs[22] = my_malloc(12181); dc[22] = 12192;
  my_free(free_ptrs[8]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[72]);
  ptrs[7] = my_malloc(12437); dc[7] = 12448;
  my_free(free_ptrs[36]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[38]);
  ptrs[14] = my_malloc(12544); dc[14] = 12552;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[3]);
  ptrs[0] = my_malloc(12767); dc[0] = 12776;
  my_free(free_ptrs[63]);
  ptrs[24] = my_malloc(12506); dc[24] = 12520;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[9]);
  ptrs[18] = my_malloc(12244); dc[18] = 12256;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[81]);
  ptrs[15] = my_malloc(12029); dc[15] = 12040;
  my_free(free_ptrs[11]);
  ptrs[23] = my_malloc(12441); dc[23] = 12456;
  my_free(free_ptrs[61]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[39]);
  ptrs[2] = my_malloc(12457); dc[2] = 12472;
  my_free(free_ptrs[54]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[48]);
  ptrs[27] = my_malloc(12041); dc[27] = 12056;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[67]);
  ptrs[12] = my_malloc(12820); dc[12] = 12832;
  my_free(free_ptrs[28]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[47]);
  ptrs[20] = my_malloc(12811); dc[20] = 12824;
  my_free(free_ptrs[68]);
  ptrs[11] = my_malloc(12540); dc[11] = 12552;

  coalesce_free_list();

  double_check_memory(ptrs, dc, 28, 8, 578680);
  printf("Correct\n");
  return 0;
}
