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
  int *ptrs[31];
  int *free_ptrs[93];
  int dc[31];

  ptrs[0] = my_malloc(12294); dc[0] = 12304;
  free_ptrs[33] = my_malloc(2448);  free_ptrs[34] = my_malloc(2158);  free_ptrs[35] = my_malloc(2678);
  free_ptrs[21] = my_malloc(2429);  free_ptrs[22] = my_malloc(2617);  free_ptrs[23] = my_malloc(2446);
  free_ptrs[60] = my_malloc(2588);  free_ptrs[61] = my_malloc(2187);  free_ptrs[62] = my_malloc(2326);
  ptrs[11] = my_malloc(12955); dc[11] = 12968;
  free_ptrs[3] = my_malloc(2637);  free_ptrs[4] = my_malloc(2084);  free_ptrs[5] = my_malloc(2669);
  free_ptrs[39] = my_malloc(2385);  free_ptrs[40] = my_malloc(2251);  free_ptrs[41] = my_malloc(2251);
  free_ptrs[63] = my_malloc(2092);  free_ptrs[64] = my_malloc(2331);  free_ptrs[65] = my_malloc(2139);
  free_ptrs[0] = my_malloc(2252);  free_ptrs[1] = my_malloc(2564);  free_ptrs[2] = my_malloc(2099);
  free_ptrs[15] = my_malloc(2398);  free_ptrs[16] = my_malloc(2065);  free_ptrs[17] = my_malloc(2604);
  ptrs[15] = my_malloc(12292); dc[15] = 12304;
  free_ptrs[48] = my_malloc(2461);  free_ptrs[49] = my_malloc(2060);  free_ptrs[50] = my_malloc(2191);
  free_ptrs[81] = my_malloc(2116);  free_ptrs[82] = my_malloc(2228);  free_ptrs[83] = my_malloc(2239);
  free_ptrs[27] = my_malloc(2657);  free_ptrs[28] = my_malloc(2452);  free_ptrs[29] = my_malloc(2584);
  free_ptrs[54] = my_malloc(2198);  free_ptrs[55] = my_malloc(2151);  free_ptrs[56] = my_malloc(2363);
  free_ptrs[51] = my_malloc(2469);  free_ptrs[52] = my_malloc(2539);  free_ptrs[53] = my_malloc(2326);
  free_ptrs[57] = my_malloc(2516);  free_ptrs[58] = my_malloc(2280);  free_ptrs[59] = my_malloc(2377);
  free_ptrs[69] = my_malloc(2553);  free_ptrs[70] = my_malloc(2057);  free_ptrs[71] = my_malloc(2447);
  free_ptrs[78] = my_malloc(2474);  free_ptrs[79] = my_malloc(2153);  free_ptrs[80] = my_malloc(2586);
  ptrs[12] = my_malloc(12731); dc[12] = 12744;
  free_ptrs[18] = my_malloc(2583);  free_ptrs[19] = my_malloc(2431);  free_ptrs[20] = my_malloc(2128);
  free_ptrs[87] = my_malloc(2334);  free_ptrs[88] = my_malloc(2591);  free_ptrs[89] = my_malloc(2352);
  ptrs[30] = my_malloc(12853); dc[30] = 12864;
  free_ptrs[90] = my_malloc(2243);  free_ptrs[91] = my_malloc(2060);  free_ptrs[92] = my_malloc(2197);
  free_ptrs[12] = my_malloc(2627);  free_ptrs[13] = my_malloc(2607);  free_ptrs[14] = my_malloc(2631);
  free_ptrs[75] = my_malloc(2457);  free_ptrs[76] = my_malloc(2322);  free_ptrs[77] = my_malloc(2575);
  ptrs[21] = my_malloc(12911); dc[21] = 12920;
  free_ptrs[84] = my_malloc(2453);  free_ptrs[85] = my_malloc(2345);  free_ptrs[86] = my_malloc(2675);
  free_ptrs[42] = my_malloc(2151);  free_ptrs[43] = my_malloc(2134);  free_ptrs[44] = my_malloc(2200);
  ptrs[20] = my_malloc(12762); dc[20] = 12776;
  free_ptrs[72] = my_malloc(2283);  free_ptrs[73] = my_malloc(2193);  free_ptrs[74] = my_malloc(2081);
  free_ptrs[9] = my_malloc(2354);  free_ptrs[10] = my_malloc(2192);  free_ptrs[11] = my_malloc(2109);
  free_ptrs[66] = my_malloc(2370);  free_ptrs[67] = my_malloc(2063);  free_ptrs[68] = my_malloc(2358);
  ptrs[9] = my_malloc(12299); dc[9] = 12312;
  free_ptrs[24] = my_malloc(2189);  free_ptrs[25] = my_malloc(2096);  free_ptrs[26] = my_malloc(2606);
  free_ptrs[30] = my_malloc(2175);  free_ptrs[31] = my_malloc(2348);  free_ptrs[32] = my_malloc(2631);
  ptrs[14] = my_malloc(12087); dc[14] = 12096;
  ptrs[23] = my_malloc(12696); dc[23] = 12704;
  free_ptrs[6] = my_malloc(2275);  free_ptrs[7] = my_malloc(2250);  free_ptrs[8] = my_malloc(2624);
  free_ptrs[45] = my_malloc(2128);  free_ptrs[46] = my_malloc(2310);  free_ptrs[47] = my_malloc(2538);
  ptrs[27] = my_malloc(12544); dc[27] = 12552;
  free_ptrs[36] = my_malloc(2544);  free_ptrs[37] = my_malloc(2317);  free_ptrs[38] = my_malloc(2410);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[66]);
  ptrs[28] = my_malloc(12682); dc[28] = 12696;
  my_free(free_ptrs[53]);
  ptrs[3] = my_malloc(12372); dc[3] = 12384;
  my_free(free_ptrs[62]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[34]);
  ptrs[24] = my_malloc(12721); dc[24] = 12736;
  my_free(free_ptrs[88]);
  my_free(free_ptrs[57]);
  ptrs[17] = my_malloc(12218); dc[17] = 12232;
  my_free(free_ptrs[29]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[10]);
  ptrs[29] = my_malloc(12969); dc[29] = 12984;
  my_free(free_ptrs[61]);
  my_free(free_ptrs[79]);
  ptrs[18] = my_malloc(12627); dc[18] = 12640;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[68]);
  ptrs[8] = my_malloc(12639); dc[8] = 12648;
  my_free(free_ptrs[56]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[82]);
  ptrs[16] = my_malloc(12870); dc[16] = 12880;
  my_free(free_ptrs[73]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[18]);
  ptrs[10] = my_malloc(12727); dc[10] = 12736;
  my_free(free_ptrs[50]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[22]);
  ptrs[4] = my_malloc(12634); dc[4] = 12648;
  my_free(free_ptrs[81]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[15]);
  ptrs[25] = my_malloc(12935); dc[25] = 12944;
  my_free(free_ptrs[84]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[38]);
  ptrs[2] = my_malloc(12576); dc[2] = 12584;
  my_free(free_ptrs[64]);
  ptrs[6] = my_malloc(12290); dc[6] = 12304;
  my_free(free_ptrs[37]);
  my_free(free_ptrs[16]);
  ptrs[26] = my_malloc(12840); dc[26] = 12848;
  my_free(free_ptrs[70]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[92]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[35]);
  ptrs[5] = my_malloc(12057); dc[5] = 12072;
  ptrs[19] = my_malloc(12690); dc[19] = 12704;
  my_free(free_ptrs[6]);
  ptrs[13] = my_malloc(12738); dc[13] = 12752;
  my_free(free_ptrs[80]);
  my_free(free_ptrs[28]);
  ptrs[1] = my_malloc(12255); dc[1] = 12264;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[13]);
  ptrs[22] = my_malloc(12572); dc[22] = 12584;
  my_free(free_ptrs[49]);
  ptrs[7] = my_malloc(12620); dc[7] = 12632;
  my_free(free_ptrs[69]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[55]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 10, 644768);
  printf("Correct\n");
  return 0;
}
