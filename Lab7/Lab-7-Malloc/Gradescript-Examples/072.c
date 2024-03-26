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
  int *ptrs[29];
  int *free_ptrs[87];
  int dc[29];

  free_ptrs[27] = my_malloc(2378);  free_ptrs[28] = my_malloc(2229);  free_ptrs[29] = my_malloc(2514);
  free_ptrs[36] = my_malloc(2547);  free_ptrs[37] = my_malloc(2097);  free_ptrs[38] = my_malloc(2343);
  ptrs[18] = my_malloc(12968); dc[18] = 12976;
  free_ptrs[30] = my_malloc(2666);  free_ptrs[31] = my_malloc(2367);  free_ptrs[32] = my_malloc(2361);
  free_ptrs[75] = my_malloc(2081);  free_ptrs[76] = my_malloc(2259);  free_ptrs[77] = my_malloc(2684);
  ptrs[14] = my_malloc(12189); dc[14] = 12200;
  ptrs[3] = my_malloc(12798); dc[3] = 12808;
  free_ptrs[39] = my_malloc(2074);  free_ptrs[40] = my_malloc(2254);  free_ptrs[41] = my_malloc(2197);
  free_ptrs[81] = my_malloc(2569);  free_ptrs[82] = my_malloc(2570);  free_ptrs[83] = my_malloc(2461);
  free_ptrs[69] = my_malloc(2674);  free_ptrs[70] = my_malloc(2153);  free_ptrs[71] = my_malloc(2657);
  free_ptrs[63] = my_malloc(2088);  free_ptrs[64] = my_malloc(2061);  free_ptrs[65] = my_malloc(2374);
  free_ptrs[21] = my_malloc(2420);  free_ptrs[22] = my_malloc(2081);  free_ptrs[23] = my_malloc(2301);
  free_ptrs[45] = my_malloc(2110);  free_ptrs[46] = my_malloc(2233);  free_ptrs[47] = my_malloc(2447);
  free_ptrs[6] = my_malloc(2081);  free_ptrs[7] = my_malloc(2143);  free_ptrs[8] = my_malloc(2266);
  free_ptrs[12] = my_malloc(2597);  free_ptrs[13] = my_malloc(2530);  free_ptrs[14] = my_malloc(2291);
  free_ptrs[78] = my_malloc(2665);  free_ptrs[79] = my_malloc(2130);  free_ptrs[80] = my_malloc(2382);
  ptrs[25] = my_malloc(12024); dc[25] = 12032;
  free_ptrs[48] = my_malloc(2208);  free_ptrs[49] = my_malloc(2430);  free_ptrs[50] = my_malloc(2319);
  ptrs[15] = my_malloc(12958); dc[15] = 12968;
  free_ptrs[66] = my_malloc(2176);  free_ptrs[67] = my_malloc(2580);  free_ptrs[68] = my_malloc(2308);
  free_ptrs[9] = my_malloc(2501);  free_ptrs[10] = my_malloc(2355);  free_ptrs[11] = my_malloc(2406);
  ptrs[1] = my_malloc(12264); dc[1] = 12272;
  free_ptrs[54] = my_malloc(2625);  free_ptrs[55] = my_malloc(2696);  free_ptrs[56] = my_malloc(2158);
  ptrs[5] = my_malloc(12515); dc[5] = 12528;
  ptrs[21] = my_malloc(12241); dc[21] = 12256;
  ptrs[10] = my_malloc(12341); dc[10] = 12352;
  ptrs[27] = my_malloc(12385); dc[27] = 12400;
  free_ptrs[60] = my_malloc(2150);  free_ptrs[61] = my_malloc(2060);  free_ptrs[62] = my_malloc(2173);
  free_ptrs[15] = my_malloc(2607);  free_ptrs[16] = my_malloc(2403);  free_ptrs[17] = my_malloc(2062);
  free_ptrs[0] = my_malloc(2610);  free_ptrs[1] = my_malloc(2451);  free_ptrs[2] = my_malloc(2644);
  free_ptrs[42] = my_malloc(2554);  free_ptrs[43] = my_malloc(2687);  free_ptrs[44] = my_malloc(2059);
  free_ptrs[18] = my_malloc(2299);  free_ptrs[19] = my_malloc(2632);  free_ptrs[20] = my_malloc(2393);
  ptrs[2] = my_malloc(12982); dc[2] = 12992;
  free_ptrs[3] = my_malloc(2051);  free_ptrs[4] = my_malloc(2664);  free_ptrs[5] = my_malloc(2395);
  free_ptrs[72] = my_malloc(2647);  free_ptrs[73] = my_malloc(2068);  free_ptrs[74] = my_malloc(2121);
  free_ptrs[51] = my_malloc(2157);  free_ptrs[52] = my_malloc(2302);  free_ptrs[53] = my_malloc(2428);
  free_ptrs[57] = my_malloc(2303);  free_ptrs[58] = my_malloc(2616);  free_ptrs[59] = my_malloc(2624);
  free_ptrs[24] = my_malloc(2650);  free_ptrs[25] = my_malloc(2082);  free_ptrs[26] = my_malloc(2409);
  ptrs[26] = my_malloc(12766); dc[26] = 12776;
  free_ptrs[84] = my_malloc(2218);  free_ptrs[85] = my_malloc(2501);  free_ptrs[86] = my_malloc(2548);
  free_ptrs[33] = my_malloc(2452);  free_ptrs[34] = my_malloc(2477);  free_ptrs[35] = my_malloc(2287);
  ptrs[4] = my_malloc(12359); dc[4] = 12368;
  my_free(free_ptrs[50]);
  ptrs[13] = my_malloc(12180); dc[13] = 12192;
  ptrs[7] = my_malloc(12157); dc[7] = 12168;
  my_free(free_ptrs[26]);
  my_free(free_ptrs[74]);
  ptrs[11] = my_malloc(12437); dc[11] = 12448;
  my_free(free_ptrs[59]);
  my_free(free_ptrs[43]);
  my_free(free_ptrs[60]);
  my_free(free_ptrs[72]);
  my_free(free_ptrs[44]);
  my_free(free_ptrs[27]);
  my_free(free_ptrs[63]);
  ptrs[22] = my_malloc(12666); dc[22] = 12680;
  ptrs[9] = my_malloc(12292); dc[9] = 12304;
  my_free(free_ptrs[10]);
  my_free(free_ptrs[6]);
  ptrs[0] = my_malloc(12388); dc[0] = 12400;
  ptrs[12] = my_malloc(12761); dc[12] = 12776;
  ptrs[23] = my_malloc(12474); dc[23] = 12488;
  my_free(free_ptrs[34]);
  my_free(free_ptrs[41]);
  my_free(free_ptrs[84]);
  my_free(free_ptrs[32]);
  my_free(free_ptrs[22]);
  my_free(free_ptrs[79]);
  my_free(free_ptrs[73]);
  my_free(free_ptrs[25]);
  my_free(free_ptrs[8]);
  my_free(free_ptrs[65]);
  my_free(free_ptrs[56]);
  my_free(free_ptrs[2]);
  ptrs[6] = my_malloc(12079); dc[6] = 12088;
  my_free(free_ptrs[18]);
  my_free(free_ptrs[37]);
  my_free(free_ptrs[15]);
  my_free(free_ptrs[42]);
  my_free(free_ptrs[69]);
  my_free(free_ptrs[0]);
  my_free(free_ptrs[29]);
  my_free(free_ptrs[20]);
  my_free(free_ptrs[80]);
  my_free(free_ptrs[58]);
  my_free(free_ptrs[67]);
  my_free(free_ptrs[35]);
  my_free(free_ptrs[33]);
  my_free(free_ptrs[23]);
  my_free(free_ptrs[66]);
  my_free(free_ptrs[16]);
  my_free(free_ptrs[48]);
  ptrs[20] = my_malloc(12375); dc[20] = 12384;
  my_free(free_ptrs[11]);
  my_free(free_ptrs[38]);
  my_free(free_ptrs[45]);
  my_free(free_ptrs[47]);
  my_free(free_ptrs[78]);
  my_free(free_ptrs[55]);
  my_free(free_ptrs[4]);
  my_free(free_ptrs[5]);
  my_free(free_ptrs[13]);
  my_free(free_ptrs[52]);
  my_free(free_ptrs[30]);
  ptrs[16] = my_malloc(12508); dc[16] = 12520;
  my_free(free_ptrs[12]);
  my_free(free_ptrs[53]);
  my_free(free_ptrs[82]);
  my_free(free_ptrs[46]);
  my_free(free_ptrs[83]);
  my_free(free_ptrs[40]);
  my_free(free_ptrs[64]);
  my_free(free_ptrs[71]);
  my_free(free_ptrs[17]);
  my_free(free_ptrs[76]);
  my_free(free_ptrs[21]);
  my_free(free_ptrs[51]);
  ptrs[19] = my_malloc(12307); dc[19] = 12320;
  my_free(free_ptrs[68]);
  my_free(free_ptrs[77]);
  my_free(free_ptrs[1]);
  my_free(free_ptrs[31]);
  my_free(free_ptrs[70]);
  my_free(free_ptrs[49]);
  my_free(free_ptrs[36]);
  ptrs[17] = my_malloc(12844); dc[17] = 12856;
  ptrs[24] = my_malloc(12767); dc[24] = 12776;
  my_free(free_ptrs[39]);
  my_free(free_ptrs[85]);
  my_free(free_ptrs[62]);
  my_free(free_ptrs[9]);
  my_free(free_ptrs[7]);
  my_free(free_ptrs[61]);
  my_free(free_ptrs[57]);
  ptrs[8] = my_malloc(12196); dc[8] = 12208;
  my_free(free_ptrs[75]);
  my_free(free_ptrs[14]);
  my_free(free_ptrs[3]);
  my_free(free_ptrs[19]);
  my_free(free_ptrs[86]);
  my_free(free_ptrs[28]);
  my_free(free_ptrs[24]);
  my_free(free_ptrs[54]);
  ptrs[28] = my_malloc(12528); dc[28] = 12536;
  my_free(free_ptrs[81]);

  coalesce_free_list();

  double_check_memory(ptrs, dc, 29, 9, 599640);
  printf("Correct\n");
  return 0;
}
