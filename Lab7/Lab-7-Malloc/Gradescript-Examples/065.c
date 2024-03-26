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

  free_ptrs[42] = my_malloc(2266);  free_ptrs[43] = my_malloc(2483);  free_ptrs[44] = my_malloc(2530);
  free_ptrs[18] = my_malloc(2634);  free_ptrs[19] = my_malloc(2451);  free_ptrs[20] = my_malloc(2539);
  free_ptrs[57] = my_malloc(2148);  free_ptrs[58] = my_malloc(2475);  free_ptrs[59] = my_malloc(2445);
  free_ptrs[36] = my_malloc(2605);  free_ptrs[37] = my_malloc(2371);  free_ptrs[38] = my_malloc(2197);
  free_ptrs[63] = my_malloc(2230);  free_ptrs[64] = my_malloc(2556);  free_ptrs[65] = my_malloc(2194);
  ptrs[5] = my_malloc(12175); dc[5] = 12184;
  ptrs[3] = my_malloc(12386); dc[3] = 12400;
  free_ptrs[24] = my_malloc(2382);  free_ptrs[25] = my_malloc(2594);  free_ptrs[26] = my_malloc(2556);
  free_ptrs[12] = my_malloc(2689);  free_ptrs[13] = my_malloc(2603);  free_ptrs[14] = my_malloc(2117);
  free_ptrs[45] = my_malloc(2243);  free_ptrs[46] = my_malloc(2199);  free_ptrs[47] = my_malloc(2470);
  free_ptrs[15] = my_malloc(2674);  free_ptrs[16] = my_malloc(2195);  free_ptrs[17] = my_malloc(2697);
  ptrs[17] = my_malloc(12512); dc[17] = 12520;
  free_ptrs[75] = my_malloc(2222);  free_ptrs[76] = my_malloc(2409);  free_ptrs[77] = my_malloc(2219);
  free_ptrs[6] = my_malloc(2697);  free_ptrs[7] = my_malloc(2227);  free_ptrs[8] = my_malloc(2447);
  ptrs[6] = my_malloc(12067); dc[6] = 12080;
  free_ptrs[30] = my_malloc(2297);  free_ptrs[31] = my_malloc(2391);  free_ptrs[32] = my_malloc(2412);
  ptrs[8] = my_malloc(12296); dc[8] = 12304;
  ptrs[4] = my_malloc(12547); dc[4] = 12560;
  free_ptrs[51] = my_malloc(2204);  free_ptrs[52] = my_malloc(2166);  free_ptrs[53] = my_malloc(2185);
  free_ptrs[3] = my_malloc(2187);  free_ptrs[4] = my_malloc(2105);  free_ptrs[5] = my_malloc(2313);
  ptrs[22] = my_malloc(12670); dc[22] = 12680;
  free_ptrs[66] = my_malloc(2373);  free_ptrs[67] = my_malloc(2599);  free_ptrs[68] = my_malloc(2402);
  free_ptrs[69] = my_malloc(2132);  free_ptrs[70] = my_malloc(2185);  free_ptrs[71] = my_malloc(2268);
  free_ptrs[78] = my_malloc(2302);  free_ptrs[79] = my_malloc(2329);  free_ptrs[80] = my_malloc(2261);
  ptrs[9] = my_malloc(12656); dc[9] = 12664;
  free_ptrs[33] = my_malloc(2282);  free_ptrs[34] = my_malloc(2686);  free_ptrs[35] = my_malloc(2566);
  free_ptrs[9] = my_malloc(2126);  free_ptrs[10] = my_malloc(2060);  free_ptrs[11] = my_malloc(2345);
  ptrs[1] = my_malloc(12356); dc[1] = 12368;
  free_ptrs[48] = my_malloc(2492);  free_ptrs[49] = my_malloc(2191);  free_ptrs[50] = my_malloc(2332);
  ptrs[25] = my_malloc(12004); dc[25] = 12016;
  free_ptrs[39] = my_malloc(2627);  free_ptrs[40] = my_malloc(2577);  free_ptrs[41] = my_malloc(2656);
  free_ptrs[0] = my_malloc(2181);  free_ptrs[1] = my_malloc(2356);  free_ptrs[2] = my_malloc(2534);
  ptrs[12] = my_malloc(12333); dc[12] = 12344;
  free_ptrs[72] = my_malloc(2332);  free_ptrs[73] = my_malloc(2315);  free_ptrs[74] = my_malloc(2069);
  ptrs[26] = my_malloc(12522); dc[26] = 12536;
  free_ptrs[27] = my_malloc(2362);  free_ptrs[28] = my_malloc(2120);  free_ptrs[29] = my_malloc(2352);
  ptrs[2] = my_malloc(12594); dc[2] = 12608;
  free_ptrs[60] = my_malloc(2432);  free_ptrs[61] = my_malloc(2636);  free_ptrs[62] = my_malloc(2074);
  free_ptrs[21] = my_malloc(2357);  free_ptrs[22] = my_malloc(2614);  free_ptrs[23] = my_malloc(2314);
  free_ptrs[54] = my_malloc(2448);  free_ptrs[55] = my_malloc(2635);  free_ptrs[56] = my_malloc(2075);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[78]);
  ptrs[21] = my_malloc(12941); dc[21] = 12952;
  my_free(free_ptrs[20]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[70]);
  ptrs[13] = my_malloc(12784); dc[13] = 12792;
  my_free(free_ptrs[32]);
  ptrs[24] = my_malloc(12459); dc[24] = 12472;
  ptrs[16] = my_malloc(12848); dc[16] = 12856;
  my_free(free_ptrs[69]);
  my_free(free_ptrs[79]);
  ptrs[7] = my_malloc(12145); dc[7] = 12160;
  my_free(free_ptrs[77]);
  my_free(free_ptrs[24]);
  ptrs[11] = my_malloc(12041); dc[11] = 12056;
  my_free(free_ptrs[30]);
  ptrs[10] = my_malloc(12905); dc[10] = 12920;
  my_free(free_ptrs[51]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[29]);
  ptrs[20] = my_malloc(12739); dc[20] = 12752;
  my_free(free_ptrs[22]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[28]);
  ptrs[0] = my_malloc(12272); dc[0] = 12280;
  my_free(free_ptrs[38]);
  my_free(free_ptrs[10]);
  ptrs[23] = my_malloc(12606); dc[23] = 12616;
  my_free(free_ptrs[72]);
  ptrs[19] = my_malloc(12015); dc[19] = 12024;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[61]);
  ptrs[18] = my_malloc(12884); dc[18] = 12896;
  my_free(free_ptrs[15]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[18]);
  ptrs[15] = my_malloc(12842); dc[15] = 12856;
  my_free(free_ptrs[60]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[41]);
  ptrs[14] = my_malloc(12929); dc[14] = 12944;
  my_free(free_ptrs[43]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[45]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 12, 559024);
  printf("Correct\n");
  return 0;
}
