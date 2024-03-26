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

  free_ptrs[24] = my_malloc(2505);  free_ptrs[25] = my_malloc(2610);  free_ptrs[26] = my_malloc(2583);
  ptrs[0] = my_malloc(12799); dc[0] = 12808;
  ptrs[20] = my_malloc(12338); dc[20] = 12352;
  free_ptrs[78] = my_malloc(2461);  free_ptrs[79] = my_malloc(2221);  free_ptrs[80] = my_malloc(2194);
  free_ptrs[51] = my_malloc(2297);  free_ptrs[52] = my_malloc(2347);  free_ptrs[53] = my_malloc(2109);
  ptrs[10] = my_malloc(12520); dc[10] = 12528;
  free_ptrs[15] = my_malloc(2276);  free_ptrs[16] = my_malloc(2377);  free_ptrs[17] = my_malloc(2613);
  free_ptrs[48] = my_malloc(2391);  free_ptrs[49] = my_malloc(2506);  free_ptrs[50] = my_malloc(2097);
  ptrs[28] = my_malloc(12067); dc[28] = 12080;
  free_ptrs[12] = my_malloc(2323);  free_ptrs[13] = my_malloc(2472);  free_ptrs[14] = my_malloc(2053);
  ptrs[1] = my_malloc(12195); dc[1] = 12208;
  ptrs[13] = my_malloc(12991); dc[13] = 13000;
  free_ptrs[69] = my_malloc(2352);  free_ptrs[70] = my_malloc(2478);  free_ptrs[71] = my_malloc(2444);
  free_ptrs[0] = my_malloc(2632);  free_ptrs[1] = my_malloc(2271);  free_ptrs[2] = my_malloc(2051);
  free_ptrs[75] = my_malloc(2170);  free_ptrs[76] = my_malloc(2681);  free_ptrs[77] = my_malloc(2436);
  ptrs[15] = my_malloc(12105); dc[15] = 12120;
  ptrs[19] = my_malloc(12526); dc[19] = 12536;
  free_ptrs[57] = my_malloc(2401);  free_ptrs[58] = my_malloc(2265);  free_ptrs[59] = my_malloc(2443);
  free_ptrs[42] = my_malloc(2696);  free_ptrs[43] = my_malloc(2280);  free_ptrs[44] = my_malloc(2545);
  ptrs[23] = my_malloc(12861); dc[23] = 12872;
  free_ptrs[81] = my_malloc(2359);  free_ptrs[82] = my_malloc(2456);  free_ptrs[83] = my_malloc(2406);
  free_ptrs[63] = my_malloc(2412);  free_ptrs[64] = my_malloc(2585);  free_ptrs[65] = my_malloc(2190);
  free_ptrs[36] = my_malloc(2166);  free_ptrs[37] = my_malloc(2070);  free_ptrs[38] = my_malloc(2129);
  free_ptrs[30] = my_malloc(2258);  free_ptrs[31] = my_malloc(2480);  free_ptrs[32] = my_malloc(2166);
  free_ptrs[18] = my_malloc(2157);  free_ptrs[19] = my_malloc(2164);  free_ptrs[20] = my_malloc(2604);
  ptrs[3] = my_malloc(12593); dc[3] = 12608;
  ptrs[21] = my_malloc(12540); dc[21] = 12552;
  free_ptrs[27] = my_malloc(2268);  free_ptrs[28] = my_malloc(2455);  free_ptrs[29] = my_malloc(2218);
  free_ptrs[66] = my_malloc(2157);  free_ptrs[67] = my_malloc(2657);  free_ptrs[68] = my_malloc(2285);
  free_ptrs[60] = my_malloc(2053);  free_ptrs[61] = my_malloc(2056);  free_ptrs[62] = my_malloc(2175);
  free_ptrs[87] = my_malloc(2315);  free_ptrs[88] = my_malloc(2213);  free_ptrs[89] = my_malloc(2297);
  free_ptrs[21] = my_malloc(2686);  free_ptrs[22] = my_malloc(2260);  free_ptrs[23] = my_malloc(2137);
  free_ptrs[45] = my_malloc(2484);  free_ptrs[46] = my_malloc(2380);  free_ptrs[47] = my_malloc(2608);
  free_ptrs[39] = my_malloc(2437);  free_ptrs[40] = my_malloc(2460);  free_ptrs[41] = my_malloc(2669);
  ptrs[2] = my_malloc(12713); dc[2] = 12728;
  free_ptrs[9] = my_malloc(2566);  free_ptrs[10] = my_malloc(2507);  free_ptrs[11] = my_malloc(2184);
  ptrs[24] = my_malloc(12322); dc[24] = 12336;
  free_ptrs[84] = my_malloc(2114);  free_ptrs[85] = my_malloc(2081);  free_ptrs[86] = my_malloc(2211);
  free_ptrs[6] = my_malloc(2080);  free_ptrs[7] = my_malloc(2289);  free_ptrs[8] = my_malloc(2294);
  free_ptrs[33] = my_malloc(2248);  free_ptrs[34] = my_malloc(2678);  free_ptrs[35] = my_malloc(2506);
  free_ptrs[54] = my_malloc(2061);  free_ptrs[55] = my_malloc(2391);  free_ptrs[56] = my_malloc(2563);
  ptrs[17] = my_malloc(12991); dc[17] = 13000;
  free_ptrs[72] = my_malloc(2419);  free_ptrs[73] = my_malloc(2470);  free_ptrs[74] = my_malloc(2642);
  free_ptrs[3] = my_malloc(2323);  free_ptrs[4] = my_malloc(2154);  free_ptrs[5] = my_malloc(2347);
  my_free(free_ptrs[61]);
  ptrs[8] = my_malloc(12343); dc[8] = 12352;
  my_free(free_ptrs[77]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[4]);
  ptrs[18] = my_malloc(12619); dc[18] = 12632;
  my_free(free_ptrs[13]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[34]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[28]);
  ptrs[27] = my_malloc(12188); dc[27] = 12200;
  ptrs[25] = my_malloc(12715); dc[25] = 12728;
  my_free(free_ptrs[41]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[88]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[51]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[59]);
  my_free(free_ptrs[84]);
  ptrs[9] = my_malloc(12255); dc[9] = 12264;
  my_free(free_ptrs[64]);
  ptrs[22] = my_malloc(12061); dc[22] = 12072;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[18]);
  my_free(free_ptrs[87]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[30]);
  my_free(free_ptrs[48]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[63]);
  my_free(free_ptrs[39]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[11]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[53]);
  ptrs[5] = my_malloc(12094); dc[5] = 12104;
  my_free(free_ptrs[85]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[7]);
  ptrs[14] = my_malloc(12120); dc[14] = 12128;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[66]);
  ptrs[26] = my_malloc(12625); dc[26] = 12640;
  my_free(free_ptrs[16]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[68]);
  ptrs[11] = my_malloc(12808); dc[11] = 12816;
  my_free(free_ptrs[75]);
  ptrs[12] = my_malloc(12244); dc[12] = 12256;
  my_free(free_ptrs[83]);
  my_free(free_ptrs[81]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[57]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[54]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[15]);
  ptrs[29] = my_malloc(12557); dc[29] = 12568;
  my_free(free_ptrs[65]);
  my_free(free_ptrs[6]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[50]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[36]);
  my_free(free_ptrs[74]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[89]);
  my_free(free_ptrs[80]);
  ptrs[4] = my_malloc(12306); dc[4] = 12320;
  my_free(free_ptrs[86]);
  my_free(free_ptrs[12]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[17]);
  ptrs[7] = my_malloc(12328); dc[7] = 12336;
  my_free(free_ptrs[38]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[2]);
  my_free(free_ptrs[44]);
  ptrs[16] = my_malloc(12767); dc[16] = 12776;
  my_free(free_ptrs[45]);
  my_free(free_ptrs[20]);
  ptrs[6] = my_malloc(12514); dc[6] = 12528;

  coalesce_free_list();

  double_check_memory(ptrs, dc, 30, 11, 620208);
  printf("Correct\n");
  return 0;
}
