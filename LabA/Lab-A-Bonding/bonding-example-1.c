#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "bonding.h"

/* This solution only works with one molecule. */

struct global_info {
  pthread_mutex_t *lock;
  int h1;
  int h2;
  int o;
};

/* Initialize_v() sets h1/h2/o to -1 and initializes the lock. */

void *initialize_v(char *verbosity)
{
  struct global_info *g;

  g = (struct global_info *) malloc(sizeof(struct global_info));
  g->lock = new_mutex();
  g->h1 = -1;
  g->h2 = -1;
  g->o = -1;
  return (void *) g;
}

/* The hydrogen thread tries to set h1 or h2 to itself.  If both
   are already taken, then it simply returns NULL.  Otherwise,
   it sleeps to make sure that the molecule is ready, and it
   calls <b>Bond()</b>.
 */

void *hydrogen(void *arg)
{
  struct bonding_arg *a;
  struct global_info *g;
  char *rv;

  a = (struct bonding_arg *) arg;
  g = (struct global_info *) a->v;

  pthread_mutex_lock(g->lock);
  if (g->h1 == -1) {
    g->h1 = a->id;
  } else if (g->h2 == -1) {
    g->h2 = a->id;
  } else {
    pthread_mutex_unlock(g->lock);
    return NULL;
  }

  pthread_mutex_unlock(g->lock);

  sleep(1);   /* You aren't allowed to make this call.  I'm just doing this so that we can be
                 sure that the molecule is ready. You will need to use wait()/signal() do 
                 to this correctly. */

  rv = Bond(g->h1, g->h2, g->o);
  return (void *) rv;
}

/* Similarly, the oxygen thread tries to set g->o to itself.  It
   g->o has already been set, then it returns NULL.  Otherwise, it
   sleeps to give the hydrogen threads time to run, and then it
   calls Bond() and returns the result. */

void *oxygen(void *arg)
{
  struct bonding_arg *a;
  struct global_info *g;
  char *rv;

  a = (struct bonding_arg *) arg;
  g = (struct global_info *) a->v;

  pthread_mutex_lock(g->lock);
  if (g->o == -1) {
    g->o = a->id;
  } else {
    pthread_mutex_unlock(g->lock);
    return NULL;
  }

  pthread_mutex_unlock(g->lock);

  sleep(1);   /* See the sleep() call above. */

  rv = Bond(g->h1, g->h2, g->o);
  return (void *) rv;
}
