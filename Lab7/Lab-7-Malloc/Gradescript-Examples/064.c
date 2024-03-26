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

  free_ptrs[57] = my_malloc(2441);  free_ptrs[58] = my_malloc(2566);  free_ptrs[59] = my_malloc(2218);
  free_ptrs[42] = my_malloc(2199);  free_ptrs[43] = my_malloc(2604);  free_ptrs[44] = my_malloc(2283);
  free_ptrs[3] = my_malloc(2115);  free_ptrs[4] = my_malloc(2413);  free_ptrs[5] = my_malloc(2264);
  free_ptrs[30] = my_malloc(2571);  free_ptrs[31] = my_malloc(2495);  free_ptrs[32] = my_malloc(2380);
  free_ptrs[15] = my_malloc(2376);  free_ptrs[16] = my_malloc(2227);  free_ptrs[17] = my_malloc(2545);
  ptrs[23] = my_malloc(12541); dc[23] = 12552;
  free_ptrs[21] = my_malloc(2136);  free_ptrs[22] = my_malloc(2393);  free_ptrs[23] = my_malloc(2544);
  ptrs[17] = my_malloc(12095); dc[17] = 12104;
  ptrs[9] = my_malloc(12496); dc[9] = 12504;
  free_ptrs[9] = my_malloc(2413);  free_ptrs[10] = my_malloc(2502);  free_ptrs[11] = my_malloc(2486);
  ptrs[14] = my_malloc(12764); dc[14] = 12776;
  free_ptrs[27] = my_malloc(2343);  free_ptrs[28] = my_malloc(2300);  free_ptrs[29] = my_malloc(2106);
  ptrs[8] = my_malloc(12948); dc[8] = 12960;
  ptrs[25] = my_malloc(12164); dc[25] = 12176;
  ptrs[10] = my_malloc(12100); dc[10] = 12112;
  ptrs[21] = my_malloc(12116); dc[21] = 12128;
  free_ptrs[36] = my_malloc(2517);  free_ptrs[37] = my_malloc(2266);  free_ptrs[38] = my_malloc(2072);
  free_ptrs[75] = my_malloc(2520);  free_ptrs[76] = my_malloc(2424);  free_ptrs[77] = my_malloc(2398);
  free_ptrs[63] = my_malloc(2381);  free_ptrs[64] = my_malloc(2377);  free_ptrs[65] = my_malloc(2369);
  free_ptrs[18] = my_malloc(2316);  free_ptrs[19] = my_malloc(2557);  free_ptrs[20] = my_malloc(2082);
  ptrs[3] = my_malloc(12577); dc[3] = 12592;
  free_ptrs[48] = my_malloc(2499);  free_ptrs[49] = my_malloc(2692);  free_ptrs[50] = my_malloc(2430);
  free_ptrs[45] = my_malloc(2587);  free_ptrs[46] = my_malloc(2539);  free_ptrs[47] = my_malloc(2110);
  free_ptrs[51] = my_malloc(2459);  free_ptrs[52] = my_malloc(2627);  free_ptrs[53] = my_malloc(2270);
  ptrs[11] = my_malloc(12704); dc[11] = 12712;
  free_ptrs[24] = my_malloc(2105);  free_ptrs[25] = my_malloc(2410);  free_ptrs[26] = my_malloc(2137);
  free_ptrs[54] = my_malloc(2557);  free_ptrs[55] = my_malloc(2383);  free_ptrs[56] = my_malloc(2575);
  free_ptrs[6] = my_malloc(2637);  free_ptrs[7] = my_malloc(2158);  free_ptrs[8] = my_malloc(2492);
  free_ptrs[78] = my_malloc(2657);  free_ptrs[79] = my_malloc(2390);  free_ptrs[80] = my_malloc(2455);
  ptrs[4] = my_malloc(12439); dc[4] = 12448;
  free_ptrs[66] = my_malloc(2478);  free_ptrs[67] = my_malloc(2396);  free_ptrs[68] = my_malloc(2185);
  ptrs[1] = my_malloc(12044); dc[1] = 12056;
  free_ptrs[12] = my_malloc(2563);  free_ptrs[13] = my_malloc(2417);  free_ptrs[14] = my_malloc(2382);
  free_ptrs[0] = my_malloc(2483);  free_ptrs[1] = my_malloc(2417);  free_ptrs[2] = my_malloc(2118);
  ptrs[12] = my_malloc(12536); dc[12] = 12544;
  free_ptrs[72] = my_malloc(2423);  free_ptrs[73] = my_malloc(2517);  free_ptrs[74] = my_malloc(2079);
  free_ptrs[60] = my_malloc(2251);  free_ptrs[61] = my_malloc(2138);  free_ptrs[62] = my_malloc(2634);
  free_ptrs[33] = my_malloc(2390);  free_ptrs[34] = my_malloc(2560);  free_ptrs[35] = my_malloc(2417);
  ptrs[13] = my_malloc(12991); dc[13] = 13000;
  free_ptrs[39] = my_malloc(2208);  free_ptrs[40] = my_malloc(2139);  free_ptrs[41] = my_malloc(2242);
  free_ptrs[69] = my_malloc(2412);  free_ptrs[70] = my_malloc(2380);  free_ptrs[71] = my_malloc(2624);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[78]);
  ptrs[16] = my_malloc(12971); dc[16] = 12984;
  my_free(free_ptrs[7]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[25]);
  ptrs[22] = my_malloc(12545); dc[22] = 12560;
  my_free(free_ptrs[21]);
  my_free(free_ptrs[5]);
  ptrs[26] = my_malloc(12653); dc[26] = 12664;
  my_free(free_ptrs[41]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[17]);
  ptrs[6] = my_malloc(12103); dc[6] = 12112;
  my_free(free_ptrs[29]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[47]);
  ptrs[15] = my_malloc(12385); dc[15] = 12400;
  ptrs[24] = my_malloc(12582); dc[24] = 12592;
  my_free(free_ptrs[45]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[61]);
  ptrs[5] = my_malloc(12470); dc[5] = 12480;
  my_free(free_ptrs[20]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[22]);
  ptrs[20] = my_malloc(12903); dc[20] = 12912;
  my_free(free_ptrs[79]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[66]);
  ptrs[19] = my_malloc(12655); dc[19] = 12664;
  ptrs[18] = my_malloc(12344); dc[18] = 12352;
  my_free(free_ptrs[2]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[75]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[18]);
  ptrs[7] = my_malloc(12049); dc[7] = 12064;
  my_free(free_ptrs[1]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[10]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[64]);
  ptrs[0] = my_malloc(12771); dc[0] = 12784;
  my_free(free_ptrs[14]);
  my_free(free_ptrs[57]);
  ptrs[2] = my_malloc(12237); dc[2] = 12248;
  my_free(free_ptrs[4]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[62]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 27, 11, 558664);
  printf("Correct\n");
  return 0;
}
