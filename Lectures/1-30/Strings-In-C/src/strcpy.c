/* Initialize three strings using strcpy() and print them. */

#include <stdio.h>
#include <string.h>

int main()
{
  char give[5];
  char him[5];
  char six[5];

  strcpy(give, "Give");
  strcpy(him, "Him");
  strcpy(six, "Six!");

  printf("%s %s %s\n", give, him, six);
  return 0;
}
