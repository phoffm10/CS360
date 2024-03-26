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
  int *ptrs[30];
  int *free_ptrs[90];
  int dc[30];

  ptrs[19] = my_malloc(12329); dc[19] = 12344;
  free_ptrs[18] = my_malloc(2360);  free_ptrs[19] = my_malloc(2621);  free_ptrs[20] = my_malloc(2693);
  free_ptrs[57] = my_malloc(2696);  free_ptrs[58] = my_malloc(2250);  free_ptrs[59] = my_malloc(2542);
  free_ptrs[87] = my_malloc(2524);  free_ptrs[88] = my_malloc(2386);  free_ptrs[89] = my_malloc(2578);
  free_ptrs[12] = my_malloc(2212);  free_ptrs[13] = my_malloc(2055);  free_ptrs[14] = my_malloc(2158);
  ptrs[15] = my_malloc(12484); dc[15] = 12496;
  free_ptrs[51] = my_malloc(2062);  free_ptrs[52] = my_malloc(2266);  free_ptrs[53] = my_malloc(2294);
  free_ptrs[54] = my_malloc(2336);  free_ptrs[55] = my_malloc(2378);  free_ptrs[56] = my_malloc(2508);
  free_ptrs[66] = my_malloc(2122);  free_ptrs[67] = my_malloc(2638);  free_ptrs[68] = my_malloc(2186);
  free_ptrs[81] = my_malloc(2238);  free_ptrs[82] = my_malloc(2441);  free_ptrs[83] = my_malloc(2659);
  free_ptrs[45] = my_malloc(2109);  free_ptrs[46] = my_malloc(2139);  free_ptrs[47] = my_malloc(2691);
  ptrs[28] = my_malloc(12142); dc[28] = 12152;
  free_ptrs[72] = my_malloc(2410);  free_ptrs[73] = my_malloc(2659);  free_ptrs[74] = my_malloc(2099);
  free_ptrs[75] = my_malloc(2275);  free_ptrs[76] = my_malloc(2240);  free_ptrs[77] = my_malloc(2241);
  free_ptrs[3] = my_malloc(2150);  free_ptrs[4] = my_malloc(2137);  free_ptrs[5] = my_malloc(2208);
  free_ptrs[9] = my_malloc(2693);  free_ptrs[10] = my_malloc(2446);  free_ptrs[11] = my_malloc(2303);
  free_ptrs[84] = my_malloc(2211);  free_ptrs[85] = my_malloc(2098);  free_ptrs[86] = my_malloc(2480);
  free_ptrs[39] = my_malloc(2674);  free_ptrs[40] = my_malloc(2557);  free_ptrs[41] = my_malloc(2100);
  free_ptrs[48] = my_malloc(2462);  free_ptrs[49] = my_malloc(2321);  free_ptrs[50] = my_malloc(2232);
  ptrs[7] = my_malloc(12523); dc[7] = 12536;
  ptrs[10] = my_malloc(12923); dc[10] = 12936;
  ptrs[6] = my_malloc(12325); dc[6] = 12336;
  ptrs[9] = my_malloc(12138); dc[9] = 12152;
  ptrs[12] = my_malloc(12935); dc[12] = 12944;
  free_ptrs[36] = my_malloc(2205);  free_ptrs[37] = my_malloc(2155);  free_ptrs[38] = my_malloc(2194);
  ptrs[0] = my_malloc(12442); dc[0] = 12456;
  ptrs[22] = my_malloc(12448); dc[22] = 12456;
  free_ptrs[69] = my_malloc(2217);  free_ptrs[70] = my_malloc(2691);  free_ptrs[71] = my_malloc(2471);
  free_ptrs[30] = my_malloc(2291);  free_ptrs[31] = my_malloc(2697);  free_ptrs[32] = my_malloc(2453);
  ptrs[2] = my_malloc(12220); dc[2] = 12232;
  free_ptrs[6] = my_malloc(2063);  free_ptrs[7] = my_malloc(2162);  free_ptrs[8] = my_malloc(2279);
  free_ptrs[42] = my_malloc(2075);  free_ptrs[43] = my_malloc(2439);  free_ptrs[44] = my_malloc(2604);
  free_ptrs[21] = my_malloc(2087);  free_ptrs[22] = my_malloc(2111);  free_ptrs[23] = my_malloc(2060);
  free_ptrs[24] = my_malloc(2536);  free_ptrs[25] = my_malloc(2265);  free_ptrs[26] = my_malloc(2598);
  free_ptrs[15] = my_malloc(2463);  free_ptrs[16] = my_malloc(2454);  free_ptrs[17] = my_malloc(2598);
  ptrs[27] = my_malloc(12743); dc[27] = 12752;
  free_ptrs[60] = my_malloc(2248);  free_ptrs[61] = my_malloc(2281);  free_ptrs[62] = my_malloc(2694);
  free_ptrs[27] = my_malloc(2419);  free_ptrs[28] = my_malloc(2450);  free_ptrs[29] = my_malloc(2187);
  free_ptrs[33] = my_malloc(2483);  free_ptrs[34] = my_malloc(2599);  free_ptrs[35] = my_malloc(2513);
  ptrs[17] = my_malloc(12802); dc[17] = 12816;
  free_ptrs[63] = my_malloc(2181);  free_ptrs[64] = my_malloc(2058);  free_ptrs[65] = my_malloc(2551);
  ptrs[20] = my_malloc(12925); dc[20] = 12936;
  ptrs[29] = my_malloc(12552); dc[29] = 12560;
  ptrs[5] = my_malloc(12353); dc[5] = 12368;
  free_ptrs[78] = my_malloc(2154);  free_ptrs[79] = my_malloc(2068);  free_ptrs[80] = my_malloc(2437);
  free_ptrs[0] = my_malloc(2205);  free_ptrs[1] = my_malloc(2422);  free_ptrs[2] = my_malloc(2598);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[83]);
  ptrs[8] = my_malloc(12938); dc[8] = 12952;
  my_free(free_ptrs[70]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[75]);
  ptrs[25] = my_malloc(12094); dc[25] = 12104;
  my_free(free_ptrs[64]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[81]);
  ptrs[16] = my_malloc(12994); dc[16] = 13008;
  ptrs[24] = my_malloc(12845); dc[24] = 12856;
  my_free(free_ptrs[89]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[26]);
  my_free(free_ptrs[60]);
  ptrs[3] = my_malloc(12564); dc[3] = 12576;
  my_free(free_ptrs[55]);
  my_free(free_ptrs[4]);
  ptrs[14] = my_malloc(12275); dc[14] = 12288;
  ptrs[18] = my_malloc(12086); dc[18] = 12096;
  my_free(free_ptrs[41]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[46]);
  ptrs[11] = my_malloc(12619); dc[11] = 12632;
  my_free(free_ptrs[22]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[63]);
  ptrs[13] = my_malloc(12946); dc[13] = 12960;
  my_free(free_ptrs[84]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[48]);
  ptrs[23] = my_malloc(12632); dc[23] = 12640;
  my_free(free_ptrs[9]);
  ptrs[4] = my_malloc(12525); dc[4] = 12536;
  my_free(free_ptrs[23]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[8]);
  ptrs[1] = my_malloc(12590); dc[1] = 12600;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[11]);
  ptrs[26] = my_malloc(12972); dc[26] = 12984;
  my_free(free_ptrs[6]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[68]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[34]);
  ptrs[21] = my_malloc(12087); dc[21] = 12096;
  my_free(free_ptrs[85]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[2]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 9, 622560);
  printf("Correct\n");
  return 0;
}
