#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{ 
  int i;
  int c;
  FILE *f;
  char buf[1000];

  for (i = 3; i < 64; i++) {
    if (close(i) == 0) fprintf(stderr, "FD %d was open\n", i);
  }
  if (argc == 1) {
    while((c = getchar()) != EOF) putchar(c);
    exit(0);
  }
  for (i = 1; i < argc; i++) {
    f = fopen(argv[i], "r");
    if (f == NULL) { perror(argv[i]); exit(1); }
    do {
      c = fread(buf, 1, 1000, f);
      if (c > 0) fwrite(buf, 1, c, stdout);
    } while (c > 0);
    fclose(f);
  }
}
