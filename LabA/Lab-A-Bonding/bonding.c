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

typedef struct atom{
  int id;
  int h1;
  int h2;
  int o;
  pthread_cond_t *cond;
}atom;

//Globals
int ready_hydrogen = 0;
int ready_oxygen = 0;

void set_atom_args(atom *h1, atom *h2, atom *o){
  h1->h1 = h2->h1 = o->h1 = h1->id;
  h1->h2 = h2->h2 = o->h2 = h2->id;
  h1->o = h2->o = o->o = o->id;
}

void free_atom(atom *atom){
  pthread_cond_destroy(atom->cond);
  free(atom);
}
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

  atom *tmp_h = (atom *)malloc(sizeof(atom));
  tmp_h->id = a->id;
  tmp_h->cond = new_cond();
  ready_hydrogen++;
  //if there is one hydrogen and one oxygen in waiting lists
  //new hydrogen then completes the bond
  if(ready_hydrogen >= 2 && ready_oxygen >= 1){

    //gets next hydrogen from list
    atom *h2 = dll_first(g->waiting_hydrogen)->val.v;

    //gets next oxygen from list
    atom *o = dll_first(g->waiting_oxygen)->val.v;

    //set args
    set_atom_args(tmp_h, h2, o);

    //remove hydrogen and oxygen from lists
    dll_delete_node(dll_first(g->waiting_hydrogen));
    ready_hydrogen -= 2;
    dll_delete_node(dll_first(g->waiting_oxygen));
    ready_oxygen--;

    pthread_cond_signal(h2->cond);
    pthread_cond_signal(o->cond);
  }
  //cannot form bond, add atom to list
  else{
    dll_append(g->waiting_hydrogen, new_jval_v(tmp_h));
    //wait until signaled
    pthread_cond_wait(tmp_h->cond, g->lock);
  }

  //where do i put this
  // Check if bonding is possible
  // Bonding is possible, call Bond()
  pthread_mutex_unlock(g->lock);
  rv = Bond(tmp_h->h1, tmp_h->h2, tmp_h->o);
  return (void *) rv;
  //free atom struct

}

void *oxygen(void *arg)
{
  struct bonding_arg *a;
  struct global_info *g;
  char *rv;

  a = (struct bonding_arg *) arg;
  g = (struct global_info *) a->v;

  pthread_mutex_lock(g->lock);

  atom *tmp_o = (atom *)malloc(sizeof(atom));
  tmp_o->id = a->id;
  tmp_o->cond = new_cond();
  ready_oxygen++;
  //if there is two hydrogens in waiting list
  //new oxygen then completes the bond
  if(ready_hydrogen >= 2 && ready_oxygen >= 1){
    
    //gets next hydrogen atom
    atom *h1 = dll_first(g->waiting_hydrogen)->val.v;

    //gets next oxygen from list
    atom *h2 = dll_first(g->waiting_hydrogen)->flink->val.v;

    //set args
    set_atom_args(h1, h2, tmp_o);

    //remove hydrogen 1 and 2 from lists
    dll_delete_node(dll_first(g->waiting_hydrogen)->flink);
    dll_delete_node(dll_first(g->waiting_hydrogen));
    ready_hydrogen -= 2;
    ready_oxygen--;

    pthread_cond_signal(h1->cond);
    pthread_cond_signal(h2->cond);
  }
  //cannot form bond, add atom to list
  else{
    dll_append(g->waiting_oxygen, new_jval_v(tmp_o));
    //wait until signaled
    pthread_cond_wait(tmp_o->cond, g->lock);
  }
  // Check if bonding is possible
  // Bonding is possible, call Bond()
  pthread_mutex_unlock(g->lock);
  rv = Bond(tmp_o->h1, tmp_o->h2, tmp_o->o);
  return (void *) rv;
}
