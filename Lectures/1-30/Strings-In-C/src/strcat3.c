/* Trying to use strcat() like C++ string concatenation. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *s;
  int i;
  int n;

  if (argc != 2) { fprintf(stderr, "usage: strcat3 number\n"); exit(1); }

  n = atoi(argv[1]);
  s = (char *) malloc(sizeof(char)*(n+1));
  strcpy(s, "");

  for (i = 0; i < n; i++) strcat(s, "j");  /* Here's the strcat() call, which is really inefficient. */
  
  printf("%s\n", s);
  return 0;
}
