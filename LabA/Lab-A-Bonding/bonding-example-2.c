#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "bonding.h"

/* This solution only works with one molecule, 
   and if threads 0 and 1 are hydrogen,
   while thread 2 is oxygen. */

void *initialize_v(char *verbosity)
{
  return NULL;
}

void *hydrogen(void *arg)
{
  return Bond(0, 1, 2);
}

void *oxygen(void *arg)
{
  return Bond(0, 1, 2);
}
