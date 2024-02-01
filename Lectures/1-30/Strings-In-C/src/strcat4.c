#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *s;
  int i;
  int n;

  if (argc != 2) { fprintf(stderr, "usage: strcat4 number\n"); exit(1); }

  n = atoi(argv[1]);
  s = (char *) malloc(sizeof(char)*(n+1));
  strcpy(s, "");

  for (i = 0; i < n; i++) strcat(s+i, "j");  /* The only changed line */
  
  printf("%s\n", s);
  return 0;
}
