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

  free_ptrs[45] = my_malloc(2487);  free_ptrs[46] = my_malloc(2549);  free_ptrs[47] = my_malloc(2260);
  ptrs[21] = my_malloc(12560); dc[21] = 12568;
  free_ptrs[6] = my_malloc(2477);  free_ptrs[7] = my_malloc(2252);  free_ptrs[8] = my_malloc(2620);
  free_ptrs[3] = my_malloc(2371);  free_ptrs[4] = my_malloc(2469);  free_ptrs[5] = my_malloc(2250);
  free_ptrs[57] = my_malloc(2429);  free_ptrs[58] = my_malloc(2192);  free_ptrs[59] = my_malloc(2162);
  free_ptrs[36] = my_malloc(2157);  free_ptrs[37] = my_malloc(2582);  free_ptrs[38] = my_malloc(2524);
  free_ptrs[9] = my_malloc(2635);  free_ptrs[10] = my_malloc(2392);  free_ptrs[11] = my_malloc(2620);
  free_ptrs[21] = my_malloc(2576);  free_ptrs[22] = my_malloc(2083);  free_ptrs[23] = my_malloc(2424);
  free_ptrs[39] = my_malloc(2054);  free_ptrs[40] = my_malloc(2109);  free_ptrs[41] = my_malloc(2578);
  free_ptrs[69] = my_malloc(2296);  free_ptrs[70] = my_malloc(2388);  free_ptrs[71] = my_malloc(2056);
  ptrs[20] = my_malloc(12083); dc[20] = 12096;
  ptrs[13] = my_malloc(12675); dc[13] = 12688;
  free_ptrs[63] = my_malloc(2109);  free_ptrs[64] = my_malloc(2343);  free_ptrs[65] = my_malloc(2487);
  free_ptrs[51] = my_malloc(2659);  free_ptrs[52] = my_malloc(2363);  free_ptrs[53] = my_malloc(2122);
  free_ptrs[0] = my_malloc(2193);  free_ptrs[1] = my_malloc(2609);  free_ptrs[2] = my_malloc(2498);
  free_ptrs[78] = my_malloc(2135);  free_ptrs[79] = my_malloc(2488);  free_ptrs[80] = my_malloc(2523);
  free_ptrs[18] = my_malloc(2668);  free_ptrs[19] = my_malloc(2285);  free_ptrs[20] = my_malloc(2176);
  ptrs[25] = my_malloc(12264); dc[25] = 12272;
  free_ptrs[75] = my_malloc(2288);  free_ptrs[76] = my_malloc(2468);  free_ptrs[77] = my_malloc(2360);
  free_ptrs[48] = my_malloc(2163);  free_ptrs[49] = my_malloc(2158);  free_ptrs[50] = my_malloc(2454);
  ptrs[3] = my_malloc(12637); dc[3] = 12648;
  ptrs[22] = my_malloc(12821); dc[22] = 12832;
  free_ptrs[12] = my_malloc(2441);  free_ptrs[13] = my_malloc(2697);  free_ptrs[14] = my_malloc(2178);
  free_ptrs[72] = my_malloc(2667);  free_ptrs[73] = my_malloc(2251);  free_ptrs[74] = my_malloc(2369);
  free_ptrs[42] = my_malloc(2253);  free_ptrs[43] = my_malloc(2274);  free_ptrs[44] = my_malloc(2407);
  free_ptrs[15] = my_malloc(2634);  free_ptrs[16] = my_malloc(2281);  free_ptrs[17] = my_malloc(2097);
  ptrs[12] = my_malloc(12676); dc[12] = 12688;
  free_ptrs[24] = my_malloc(2077);  free_ptrs[25] = my_malloc(2694);  free_ptrs[26] = my_malloc(2611);
  free_ptrs[30] = my_malloc(2063);  free_ptrs[31] = my_malloc(2225);  free_ptrs[32] = my_malloc(2352);
  ptrs[24] = my_malloc(12474); dc[24] = 12488;
  ptrs[18] = my_malloc(12412); dc[18] = 12424;
  free_ptrs[66] = my_malloc(2206);  free_ptrs[67] = my_malloc(2072);  free_ptrs[68] = my_malloc(2363);
  free_ptrs[60] = my_malloc(2375);  free_ptrs[61] = my_malloc(2576);  free_ptrs[62] = my_malloc(2356);
  free_ptrs[54] = my_malloc(2059);  free_ptrs[55] = my_malloc(2679);  free_ptrs[56] = my_malloc(2077);
  free_ptrs[33] = my_malloc(2050);  free_ptrs[34] = my_malloc(2426);  free_ptrs[35] = my_malloc(2499);
  ptrs[7] = my_malloc(12461); dc[7] = 12472;
  free_ptrs[27] = my_malloc(2393);  free_ptrs[28] = my_malloc(2218);  free_ptrs[29] = my_malloc(2232);
  ptrs[0] = my_malloc(12647); dc[0] = 12656;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[18]);
  ptrs[4] = my_malloc(12499); dc[4] = 12512;
  my_free(free_ptrs[11]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[3]);
  ptrs[15] = my_malloc(12557); dc[15] = 12568;
  ptrs[26] = my_malloc(12225); dc[26] = 12240;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[74]);
  ptrs[10] = my_malloc(12688); dc[10] = 12696;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[25]);
  ptrs[23] = my_malloc(12825); dc[23] = 12840;
  my_free(free_ptrs[9]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[43]);
  ptrs[5] = my_malloc(12818); dc[5] = 12832;
  ptrs[19] = my_malloc(12763); dc[19] = 12776;
  my_free(free_ptrs[67]);
  ptrs[16] = my_malloc(12623); dc[16] = 12632;
  my_free(free_ptrs[41]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[78]);
  ptrs[17] = my_malloc(12051); dc[17] = 12064;
  ptrs[9] = my_malloc(12620); dc[9] = 12632;
  my_free(free_ptrs[70]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[57]);
  ptrs[8] = my_malloc(12688); dc[8] = 12696;
  my_free(free_ptrs[27]);
  ptrs[2] = my_malloc(12585); dc[2] = 12600;
  my_free(free_ptrs[69]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[29]);
  ptrs[11] = my_malloc(12980); dc[11] = 12992;
  my_free(free_ptrs[64]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[21]);
  ptrs[1] = my_malloc(12232); dc[1] = 12240;
  my_free(free_ptrs[58]);
  ptrs[6] = my_malloc(12867); dc[6] = 12880;
  my_free(free_ptrs[60]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[24]);
  ptrs[14] = my_malloc(12064); dc[14] = 12072;
  my_free(free_ptrs[66]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[23]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 8, 560288);
  printf("Correct\n");
  return 0;
}
