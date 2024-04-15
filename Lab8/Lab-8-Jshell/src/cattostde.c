#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{ 
  int i;
  char line[1001];
  FILE *f;

  if (argc == 1) {
    while (fgets(line, 1001, stdin) != NULL) {
      fprintf(stderr, "%s", line);
      fflush(stderr);
    }
    exit(0);
  }

  for (i = 1; i < argc; i++) {
    f = fopen(argv[i], "r");
    if (f == NULL) { perror(argv[i]); exit(1); }
    while (fgets(line, 1001, f) != NULL) {
      fprintf(stderr, "%s", line);
      fflush(stderr);
    }
    fclose(f);
  }
  exit(0);
}
