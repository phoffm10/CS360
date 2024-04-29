//Peter Hoffman
//LabA Bonding

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "bonding.h"
#include "dllist.h"

//Structs
struct global_info {
  pthread_mutex_t *lock;
  Dllist waiting_oxygen;
  Dllist waiting_hydrogen;
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
  //Sets all args to passed ids of atoms
  h1->h1 = h2->h1 = o->h1 = h1->id;
  h1->h2 = h2->h2 = o->h2 = h2->id;
  h1->o = h2->o = o->o = o->id;
}

void free_atom(atom *atom){
  //Frees atom struct
  pthread_cond_destroy(atom->cond);
  free(atom);
}

void *initialize_v(char *verbosity){
  //Initializes global struct vals and dllists
  struct global_info *g;

  g = (struct global_info *) malloc(sizeof(struct global_info));
  g->lock = new_mutex();
  g->waiting_hydrogen = new_dllist();
  g->waiting_oxygen = new_dllist();
  return (void *) g;
}

void *hydrogen(void *arg){
  //Sets global and passed args
  struct bonding_arg *a;
  struct global_info *g;
  char *rv;

  a = (struct bonding_arg *) arg;
  g = (struct global_info *) a->v;

  //Locks mutex
  pthread_mutex_lock(g->lock);

  //Mallocs new atom, sets id and increments globals
  atom *tmp_h = (atom *)malloc(sizeof(atom));
  tmp_h->id = a->id;
  tmp_h->cond = new_cond();
  ready_hydrogen++;

  //Checks if bond can be made from global counters
  if(ready_hydrogen >= 2 && ready_oxygen >= 1){

    //Gets next hydrogen from list
    atom *h2 = dll_first(g->waiting_hydrogen)->val.v;

    //Gets next oxygen from list
    atom *o = dll_first(g->waiting_oxygen)->val.v;

    //Set args for all three atoms
    set_atom_args(tmp_h, h2, o);

    //Removes hydrogen and oxygen from lists and decrements globals
    dll_delete_node(dll_first(g->waiting_hydrogen));
    ready_hydrogen -= 2;
    dll_delete_node(dll_first(g->waiting_oxygen));
    ready_oxygen--;

    //Signals to other atoms to wake
    pthread_cond_signal(h2->cond);
    pthread_cond_signal(o->cond);
  }
  //If cannot form bond, add atom to list
  else{
    dll_append(g->waiting_hydrogen, new_jval_v(tmp_h));
    //Wait until signaled
    pthread_cond_wait(tmp_h->cond, g->lock);
  }

  //Unlocks mutex, calls bond on all atoms
  pthread_mutex_unlock(g->lock);
  rv = Bond(tmp_h->h1, tmp_h->h2, tmp_h->o);
  free_atom(tmp_h);
  return (void *) rv;
}

void *oxygen(void *arg){
  //Sets global and passed args
  struct bonding_arg *a;
  struct global_info *g;
  char *rv;

  a = (struct bonding_arg *) arg;
  g = (struct global_info *) a->v;

  //Locks mutex
  pthread_mutex_lock(g->lock);

  //Mallocs new atom, sets id and increments globals
  atom *tmp_o = (atom *)malloc(sizeof(atom));
  tmp_o->id = a->id;
  tmp_o->cond = new_cond();
  ready_oxygen++;

  //Checks if bond can be made from global counters
  if(ready_hydrogen >= 2 && ready_oxygen >= 1){
    
    //Gets next hydrogen atom
    atom *h1 = dll_first(g->waiting_hydrogen)->val.v;

    //Gets second hydrogen from list
    atom *h2 = dll_first(g->waiting_hydrogen)->flink->val.v;

    //Set args for all atoms
    set_atom_args(h1, h2, tmp_o);

    //Remove hydrogen 1 and 2 from lists and decrement globals
    dll_delete_node(dll_first(g->waiting_hydrogen)->flink);
    dll_delete_node(dll_first(g->waiting_hydrogen));
    ready_hydrogen -= 2;
    ready_oxygen--;

    //Signal existing threads
    pthread_cond_signal(h1->cond);
    pthread_cond_signal(h2->cond);
  }
  //If cannot form bond, add atom to list of waiting atoms
  else{
    dll_append(g->waiting_oxygen, new_jval_v(tmp_o));
    //Wait until signaled
    pthread_cond_wait(tmp_o->cond, g->lock);
  }

  //Unlocks the mutex and runs bond on all three atoms
  pthread_mutex_unlock(g->lock);
  rv = Bond(tmp_o->h1, tmp_o->h2, tmp_o->o);
  free_atom(tmp_o);
  return (void *) rv;
}
