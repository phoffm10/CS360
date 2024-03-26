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

  ptrs[30] = my_malloc(12039); dc[30] = 12048;
  free_ptrs[81] = my_malloc(2114);  free_ptrs[82] = my_malloc(2450);  free_ptrs[83] = my_malloc(2509);
  free_ptrs[66] = my_malloc(2604);  free_ptrs[67] = my_malloc(2223);  free_ptrs[68] = my_malloc(2546);
  ptrs[6] = my_malloc(12796); dc[6] = 12808;
  ptrs[3] = my_malloc(12902); dc[3] = 12912;
  free_ptrs[63] = my_malloc(2232);  free_ptrs[64] = my_malloc(2103);  free_ptrs[65] = my_malloc(2181);
  free_ptrs[21] = my_malloc(2401);  free_ptrs[22] = my_malloc(2249);  free_ptrs[23] = my_malloc(2668);
  ptrs[9] = my_malloc(12941); dc[9] = 12952;
  free_ptrs[72] = my_malloc(2081);  free_ptrs[73] = my_malloc(2567);  free_ptrs[74] = my_malloc(2173);
  free_ptrs[54] = my_malloc(2138);  free_ptrs[55] = my_malloc(2673);  free_ptrs[56] = my_malloc(2369);
  free_ptrs[75] = my_malloc(2673);  free_ptrs[76] = my_malloc(2640);  free_ptrs[77] = my_malloc(2655);
  free_ptrs[3] = my_malloc(2693);  free_ptrs[4] = my_malloc(2236);  free_ptrs[5] = my_malloc(2447);
  free_ptrs[33] = my_malloc(2492);  free_ptrs[34] = my_malloc(2692);  free_ptrs[35] = my_malloc(2522);
  free_ptrs[57] = my_malloc(2276);  free_ptrs[58] = my_malloc(2534);  free_ptrs[59] = my_malloc(2209);
  ptrs[24] = my_malloc(12875); dc[24] = 12888;
  ptrs[18] = my_malloc(12845); dc[18] = 12856;
  free_ptrs[87] = my_malloc(2130);  free_ptrs[88] = my_malloc(2641);  free_ptrs[89] = my_malloc(2332);
  free_ptrs[24] = my_malloc(2541);  free_ptrs[25] = my_malloc(2690);  free_ptrs[26] = my_malloc(2218);
  free_ptrs[27] = my_malloc(2183);  free_ptrs[28] = my_malloc(2210);  free_ptrs[29] = my_malloc(2340);
  free_ptrs[0] = my_malloc(2220);  free_ptrs[1] = my_malloc(2426);  free_ptrs[2] = my_malloc(2531);
  free_ptrs[48] = my_malloc(2367);  free_ptrs[49] = my_malloc(2674);  free_ptrs[50] = my_malloc(2649);
  free_ptrs[60] = my_malloc(2510);  free_ptrs[61] = my_malloc(2103);  free_ptrs[62] = my_malloc(2346);
  free_ptrs[9] = my_malloc(2640);  free_ptrs[10] = my_malloc(2390);  free_ptrs[11] = my_malloc(2381);
  ptrs[26] = my_malloc(12962); dc[26] = 12976;
  free_ptrs[18] = my_malloc(2431);  free_ptrs[19] = my_malloc(2683);  free_ptrs[20] = my_malloc(2622);
  ptrs[4] = my_malloc(12716); dc[4] = 12728;
  free_ptrs[36] = my_malloc(2146);  free_ptrs[37] = my_malloc(2151);  free_ptrs[38] = my_malloc(2444);
  ptrs[12] = my_malloc(12621); dc[12] = 12632;
  free_ptrs[12] = my_malloc(2315);  free_ptrs[13] = my_malloc(2449);  free_ptrs[14] = my_malloc(2245);
  free_ptrs[39] = my_malloc(2343);  free_ptrs[40] = my_malloc(2207);  free_ptrs[41] = my_malloc(2175);
  ptrs[13] = my_malloc(12612); dc[13] = 12624;
  free_ptrs[78] = my_malloc(2152);  free_ptrs[79] = my_malloc(2315);  free_ptrs[80] = my_malloc(2496);
  free_ptrs[6] = my_malloc(2075);  free_ptrs[7] = my_malloc(2128);  free_ptrs[8] = my_malloc(2512);
  free_ptrs[45] = my_malloc(2084);  free_ptrs[46] = my_malloc(2090);  free_ptrs[47] = my_malloc(2076);
  free_ptrs[90] = my_malloc(2497);  free_ptrs[91] = my_malloc(2188);  free_ptrs[92] = my_malloc(2095);
  free_ptrs[51] = my_malloc(2631);  free_ptrs[52] = my_malloc(2217);  free_ptrs[53] = my_malloc(2314);
  free_ptrs[69] = my_malloc(2651);  free_ptrs[70] = my_malloc(2357);  free_ptrs[71] = my_malloc(2517);
  free_ptrs[42] = my_malloc(2299);  free_ptrs[43] = my_malloc(2204);  free_ptrs[44] = my_malloc(2146);
  free_ptrs[30] = my_malloc(2687);  free_ptrs[31] = my_malloc(2578);  free_ptrs[32] = my_malloc(2515);
  free_ptrs[15] = my_malloc(2174);  free_ptrs[16] = my_malloc(2535);  free_ptrs[17] = my_malloc(2096);
  ptrs[19] = my_malloc(12836); dc[19] = 12848;
  ptrs[5] = my_malloc(12227); dc[5] = 12240;
  free_ptrs[84] = my_malloc(2575);  free_ptrs[85] = my_malloc(2453);  free_ptrs[86] = my_malloc(2093);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[8]);
  ptrs[14] = my_malloc(12393); dc[14] = 12408;
  my_free(free_ptrs[45]);
  my_free(free_ptrs[75]);
  ptrs[10] = my_malloc(12297); dc[10] = 12312;
  my_free(free_ptrs[92]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[4]);
  ptrs[11] = my_malloc(12653); dc[11] = 12664;
  my_free(free_ptrs[47]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[55]);
  ptrs[27] = my_malloc(12394); dc[27] = 12408;
  my_free(free_ptrs[32]);
  ptrs[22] = my_malloc(12718); dc[22] = 12728;
  my_free(free_ptrs[33]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[91]);
  my_free(free_ptrs[90]);
  my_free(free_ptrs[50]);
  ptrs[25] = my_malloc(12945); dc[25] = 12960;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[66]);
  ptrs[21] = my_malloc(12209); dc[21] = 12224;
  my_free(free_ptrs[65]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[86]);
  ptrs[16] = my_malloc(12376); dc[16] = 12384;
  my_free(free_ptrs[78]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[44]);
  ptrs[2] = my_malloc(12946); dc[2] = 12960;
  my_free(free_ptrs[83]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[71]);
  ptrs[29] = my_malloc(12283); dc[29] = 12296;
  ptrs[1] = my_malloc(12209); dc[1] = 12224;
  my_free(free_ptrs[1]);
  ptrs[23] = my_malloc(12954); dc[23] = 12968;
  ptrs[20] = my_malloc(12404); dc[20] = 12416;
  my_free(free_ptrs[58]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[31]);
  ptrs[17] = my_malloc(12884); dc[17] = 12896;
  ptrs[15] = my_malloc(12174); dc[15] = 12184;
  ptrs[7] = my_malloc(12950); dc[7] = 12960;
  my_free(free_ptrs[84]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[38]);
  ptrs[8] = my_malloc(12089); dc[8] = 12104;
  ptrs[0] = my_malloc(12000); dc[0] = 12008;
  ptrs[28] = my_malloc(12140); dc[28] = 12152;
  my_free(free_ptrs[43]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[23]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 31, 9, 643720);
  printf("Correct\n");
  return 0;
}
