//Peter Hoffman
//Lab 9 Threaded chat server

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include "sockettome.h"
#include "dllist.h"
#include "jrb.h"

//Struct for rooms
typedef struct room{
  char* name;
  Dllist clients;
  Dllist msg_queue;
  pthread_cond_t *cond;
  pthread_mutex_t *lock;
}room;

//Struct for client
typedef struct client{
  char* name;
  FILE* sock_read;
  FILE* sock_write;
}client;

//Forward declarations
void *create_client(void* fd);
void client_write(FILE* fd, char* string);
void room_set(JRB rooms, char* name);
void remove_client(room* r, char* client_name);
void *room_handler(void* r);

//Global
JRB rooms;

//Function to handle clients
void *create_client(void* fd){
  JRB tmp;
  Dllist dtmp;
  char s[1000];
  char msg[1000];
  client *c = (client *)malloc(sizeof(client));
  //Populates client struct
  c->sock_read = fdopen(*(int *)fd, "r");
  c->sock_write = fdopen(*(int *)fd, "w");
  
  //Prints open chat rooms and clients in each
  client_write(c->sock_write, "Chat Rooms:\n\n");
  jrb_traverse(tmp, rooms){
    room* r = (room *)tmp->val.v;
    client_write(c->sock_write, r->name);
    client_write(c->sock_write, ":");
    if(!dll_empty(r->clients)){
      dll_traverse(dtmp, r->clients){
        client* other_c = (client *)dtmp->val.v;
        client_write(c->sock_write, " ");        
        client_write(c->sock_write, other_c->name);
      }
    }
    client_write(c->sock_write, "\n");
  }
  client_write(c->sock_write, "\n");

  //Prompts client for name
  client_write(c->sock_write, "Enter your chat name (no spaces):\n");
  if (fgets(s, 1000, c->sock_read) == NULL) {
    pthread_exit(NULL);
  } else {
    s[strcspn(s, "\n")] = 0;
    c->name = strdup(s);
  }

  //Gets chat room from client
  client_write(c->sock_write, "Enter chat room:\n");
  if (fgets(s, 1000, c->sock_read) == NULL){
    pthread_exit(NULL);
  } else {
    s[strcspn(s, "\n")] = 0;
    room* r = jrb_find_str(rooms, s)->val.v;
    if (r == NULL) {
      client_write(c->sock_write, "Room does not exist, exiting\n");
      exit(1);
    }
    //Adds client to room list
    pthread_mutex_lock(r->lock);
    dll_append(r->clients, new_jval_v((void *)c));
    pthread_mutex_unlock(r->lock);

    //Sends hello message to everyone
    sprintf(s, "%s has joined\n", c->name);
    dll_traverse(dtmp, r->clients) {
      client *other_c = (client *) dtmp->val.v;
      client_write(other_c->sock_write, s);
    }

    //Continues sending messages until EOF from client
    while(fgets(msg, 1000, c->sock_read) != NULL){
      sprintf(s, "%s: %s", c->name, msg);
      pthread_mutex_lock(r->lock);
      dll_append(r->msg_queue, new_jval_s(strdup(s)));
      pthread_cond_signal(r->cond);
      pthread_mutex_unlock(r->lock);
    }    
    remove_client(r, c->name);
  }
}

//Writes to passed file descriptor
void client_write(FILE* fd, char* string){
  fputs(string, fd);
  fflush(fd);
}

//Removes client thread and frees memory
void remove_client(room* r, char* client_name){
  char s[1000];
  //Locks mutex and removes client from room
  pthread_mutex_lock(r->lock);
  Dllist dtmp;
  char* left_client_name = NULL;
  dll_traverse(dtmp, r->clients){
    client* curr_c = (client *)dtmp->val.v;
    if(strcmp(client_name, curr_c->name) == 0){
      left_client_name = strdup(client_name);
      fclose(curr_c->sock_read);
      fclose(curr_c->sock_write);
      free(curr_c->name);
      free(curr_c);
      dll_delete_node(dtmp);
      break;
    }
  }
  pthread_mutex_unlock(r->lock);
  //Prints message for other clients that someone left
  if(left_client_name != NULL) {
    sprintf(s, "%s has left\n", left_client_name);
    free(left_client_name);
    dll_traverse(dtmp, r->clients) {
      client *other_c = (client *)dtmp->val.v;
      client_write(other_c->sock_write, s);
    }
  }
  //Kills thread
  pthread_exit(NULL);
}

void room_set(JRB rooms, char* name){
  pthread_t rthread;
  room *r = (room *)malloc(sizeof(room));
  //Initialize room values
  r->name = strdup(name);
  r->clients = new_dllist();
  r->msg_queue = new_dllist();
  r->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  if (r->cond == NULL){ 
    perror("malloc pthread_cond_t");
    exit(1);
  }
  pthread_cond_init(r->cond, NULL);
  r->lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  if (r->lock == NULL){
    perror("malloc pthread_mutex_t");
    exit(1);
  }
  pthread_mutex_init(r->lock, NULL);
  //Insert room struct into tree and creates thread
  jrb_insert_str(rooms, name, new_jval_v((void *)r));
  pthread_create(&rthread, NULL, room_handler, (void*)r);
  pthread_detach(rthread);
}

void *room_handler(void* r){
  room* curr_r = (room*)r;
  Dllist dtmp;
  while (true) {
    pthread_mutex_lock(curr_r->lock);
    //Checks if message queue is not empty
    while (dll_empty(curr_r->msg_queue)) {
      pthread_cond_wait(curr_r->cond, curr_r->lock);
    }
    //Prints messsage to all clients
    dll_traverse(dtmp, curr_r->clients) {
      client *other_c = (client *) dtmp->val.v;
      client_write(other_c->sock_write, dll_first(curr_r->msg_queue)->val.s);
    }
    //Frees string and unlocks mutex
    free(dll_first(curr_r->msg_queue)->val.s);
    dll_delete_node(dll_first(curr_r->msg_queue));
    pthread_mutex_unlock(curr_r->lock);
  }
}

int main(int argc, char **argv){
  char *un, c, s[1000];
  int port, sock, fd;
  FILE *fsock;
  pthread_t thread;
  JRB tmp;

  //Parses command line
  if (argc < 3) {
    fprintf(stderr, "usage: ./chat_server port Chat-Room-Names ...\n");
    exit(1);
  }

  port = atoi(argv[2]);
  if (port < 8000) {
    fprintf(stderr, "usage: chat_server port\n");
    fprintf(stderr, "       port must be > 8000\n");
    exit(1);
  }

  rooms = make_jrb();
  for(int i = 0; i < (argc - 3); i++){
    room_set(rooms, argv[i + 3]);
  }

  sock = serve_socket(port);
  
  //Spins forever accepting connections
  while(1){
  fd = accept_connection(sock);

  pthread_create(&thread, NULL, create_client, (void*)&fd);
  pthread_detach(thread);

  }
  exit(0);
}