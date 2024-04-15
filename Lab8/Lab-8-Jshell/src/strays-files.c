#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{ 
  int i;
  int c;
  FILE *f, *fo;
  char buf[1000];

  for (i = 3; i < 64; i++) {
    if (close(i) == 0) fprintf(stderr, "FD %d was open\n", i);
  }
  if (argc != 3) {
    fprintf(stderr, "usage: strays-files inputfile outputfile\n");
    exit(1);
  }
  f = fopen(argv[1], "r");
  if (f == NULL) { perror(argv[1]); exit(1); }
  fo = fopen(argv[2], "w");
  if (fo == NULL) { perror(argv[2]); exit(1); }
  do {
    c = fread(buf, 1, 1000, f);
    if (c > 0) fwrite(buf, 1, c, fo);
  } while (c > 0);
  fclose(f);
  fclose(fo);
}
