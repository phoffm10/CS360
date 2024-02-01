/* This is the same as strcpy2.c, but I write a procedure to call strcpy(), so that
   even a smart compiler won't figure out that I have a problem. */

#include <stdio.h>
#include <string.h>

typedef unsigned long UL;

void my_strcpy(char *s1, char *s2)
{
  strcpy(s1, s2);
}

int main()
{
  char give[5];
  char him[5];
  char six[5];

  printf("give: 0x%lx  him: 0x%lx  six: 0x%lx\n", (UL) give, (UL) him, (UL) six);

  strcpy(give, "Give");
  strcpy(him, "Him");
  strcpy(six, "Six!");

  printf("%s %s %s\n", give, him, six);

  my_strcpy(him, "T.J. Houshmandzadeh");

  printf("%s %s %s\n", give, him, six);
  return 0;
}
