/* This is like src/strcpy2.c -- now we are calling strcat on a string that is not big enough. */

#include <stdio.h>
#include <string.h>

typedef unsigned long UL;

void my_strcpy(char *s1, char *s2)
{
  strcpy(s1, s2);
}

void my_strcat(char *s1, char *s2)
{
  strcat(s1, s2);
}

int main()
{
  char give[16];
  char him[5];
  char six[5];

  printf("give: 0x%lx  him: 0x%lx  six: 0x%lx\n", (UL) give, (UL) him, (UL) six);

  strcpy(give, "Give");
  strcpy(him, "Him");
  strcpy(six, "Six!");

  printf("%s %s %s\n", give, him, six);

  my_strcpy(him, "T.J. Houshmandzadeh");

  printf("%s %s %s\n", give, him, six);

  my_strcat(give, " Help!");

  printf("%s %s %s\n", give, him, six);
}
