//Peter Hoffman

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "bonding.h"
#include "dllist.h"

struct global_info {
  pthread_mutex_t *lock;
  pthread_cond_t *cond;
  Dllist waiting_oxygen;
  Dllist waiting_hydrogen;
  int h1;
  int h2;
  int o;
};

void *initialize_v(char *verbosity)
{
  struct global_info *g;

  g = (struct global_info *) malloc(sizeof(struct global_info));
  g->lock = new_mutex();
  g->cond = new_cond();
  g->waiting_hydrogen = new_dllist();
  g->waiting_oxygen = new_dllist();
  g->h1 = -1;
  g->h2 = -1;
  g->o = -1;
  return (void *) g;
}

void *hydrogen(void *arg)
{
  struct bonding_arg *a;
  struct global_info *g;
  char *rv;

  a = (struct bonding_arg *) arg;
  g = (struct global_info *) a->v;

  pthread_mutex_lock(g->lock);

  //if there is one hydrogen and one oxygen in waiting lists
  //new hydrogen then completes the bond
  if((dll_first(g->waiting_hydrogen) != NULL) && (dll_first(g->waiting_oxygen) != NULL)){
    //sets g->h1 to current atom
    g->h1 = a->id;

    //gets next hydrogen from list, sets g->h2
    Dllist tmp1 = dll_first(g->waiting_hydrogen);
    int tmp_h = tmp1->val.i;
    g->h2 = tmp_h;

    //gets next hydrogen from list, sets g->h2
    Dllist tmp2 = dll_first(g->waiting_oxygen);
    int tmp_o = tmp2->val.i;
    g->o = tmp_o;

    //remove hydrogen and oxygen from lists
    dll_delete_node(dll_first(g->waiting_hydrogen));
    dll_delete_node(dll_first(g->waiting_oxygen));

    pthread_cond_signal(g->cond);
  }
  //cannot form bond, add atom to list
  else{
    dll_append(g->waiting_hydrogen, new_jval_i(a->id));
    //wait until signaled
    pthread_cond_wait(g->cond, g->lock);
  }

  // Check if bonding is possible
  if (g->h1 != -1 && g->h2 != -1 && g->o != -1) {
    // Bonding is possible, call Bond()
    rv = Bond(g->h1, g->h2, g->o);
    pthread_mutex_unlock(g->lock);
    return (void *) rv;
  }

  pthread_mutex_unlock(g->lock);
  return NULL;
}

void *oxygen(void *arg)
{
  struct bonding_arg *a;
  struct global_info *g;
  char *rv;

  a = (struct bonding_arg *) arg;
  g = (struct global_info *) a->v;

  pthread_mutex_lock(g->lock);

  //if there is two hydrogens in waiting list
  //new oxygen then completes the bond
  if((dll_first(g->waiting_hydrogen->flink) != NULL)){
    //sets g->o to current atom
    g->o = a->id;

    //gets next hydrogen from list, sets g->h1
    Dllist tmp1 = dll_first(g->waiting_hydrogen);
    int tmp_h1 = tmp1->val.i;
    g->h1 = tmp_h1;

    //gets second hydrogen from list, sets g->h2
    Dllist tmp2 = dll_first(g->waiting_hydrogen->flink);
    int tmp_h2 = tmp2->val.i;
    g->h2 = tmp_h2;

    //remove hydrogen 1 and 2 from lists
    dll_delete_node(dll_first(g->waiting_hydrogen->flink));
    dll_delete_node(dll_first(g->waiting_hydrogen));

    pthread_cond_signal(g->cond);
  }
  //cannot form bond, add atom to list
  else{
    dll_append(g->waiting_oxygen, new_jval_i(a->id));
    //wait until signaled
    pthread_cond_wait(g->cond, g->lock);
  }


  // Check if bonding is possible
  if (g->h1 != -1 && g->h2 != -1 && g->o != -1) {
    // Bonding is possible, call Bond()
    rv = Bond(g->h1, g->h2, g->o);
    pthread_mutex_unlock(g->lock);
    return (void *) rv;
  }

  pthread_mutex_unlock(g->lock);
  return NULL;
}
