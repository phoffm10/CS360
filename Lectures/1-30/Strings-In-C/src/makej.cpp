/* Create a string with a given number of j's by using string concatenation. */

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
  int i, n;
  string s;

  if (argc != 2) { fprintf(stderr, "usage: makej number\n"); exit(1); }
  n = atoi(argv[1]);

  for (i = 0; i < n; i++) s += "j";    // Here is the string concatenation.
  cout << s << endl;
  return 0;
}
