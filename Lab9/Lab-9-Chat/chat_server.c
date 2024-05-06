//Peter Hoffman

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include "sockettome.h"
#include "dllist.h"
#include "jrb.h"

//struct for rooms
//lock when adding cient or msg to queue
//message wakes up thread
typedef struct room{
  char* name;
  Dllist clients;
  Dllist msg_queue;
  pthread_cond_t *cond;
  pthread_mutex_t *lock;
}room;

//struct for client
typedef struct client{
  char* name;
  FILE* sock_read;
  FILE* sock_write;
}client;

//forward declarations
void *create_client(void* fd);
void client_write(FILE* fd, char* string);
void room_set(JRB rooms, char* name);

//Globals
JRB rooms;

//how to I add ctrl-d functionality?
//function to create chat room
void *create_client(void* fd){
  char s[1000];
  //malloc struct
  client *c = (client *)malloc(sizeof(client));
  //populate struct
  c->sock_read = fdopen(*(int *)fd, "r");
  c->sock_write = fdopen(*(int *)fd, "w");
  
  client_write(c->sock_write, "Chat Rooms:\n\n");

  JRB tmp;
  Dllist dtmp;
  jrb_traverse(tmp, rooms){
    room* r = (room *)tmp->val.v;
    client_write(c->sock_write, r->name);
    client_write(c->sock_write, ": ");
    if(!dll_empty(r->clients)){
      dll_traverse(dtmp, r->clients){
        client* other_c = (client *)dtmp->val.v;
        client_write(c->sock_write, other_c->name);
        client_write(c->sock_write, " ");
      }
    }
    client_write(c->sock_write, "\n");
  }
  client_write(c->sock_write, "\n");

  //prompt for name
  client_write(c->sock_write, "Enter your chat name (no spaces):\n");
  if (fgets(s, 1000, c->sock_read) == NULL) {
    printf("Error -- socket closed\n");
    exit(1);
  } else {
    s[strcspn(s, "\n")] = 0;
    c->name = strdup(s);
  }

  //grabs chat room from client
  client_write(c->sock_write, "Enter chat room:\n");
  if (fgets(s, 1000, c->sock_read) == NULL) {
    printf("Error -- socket closed\n");
    exit(1);
  } else {
    s[strcspn(s, "\n")] = 0;
    room* r = jrb_find_str(rooms, s)->val.v;
    if (r == NULL) {
      client_write(c->sock_write, "Room does not exist, exiting\n");
      exit(1);
    }
    //add client to room list
    pthread_mutex_lock(r->lock);
    dll_append(r->clients, new_jval_v((void *)c));
    pthread_mutex_unlock(r->lock);

    //send hello to everyone
    sprintf(s, "%s has joined\n", c->name);
    dll_traverse(dtmp, r->clients) {
      client *other_c = (client *) dtmp->val.v;
      client_write(other_c->sock_write, s);
    }

    //while(1){
      //this is where i need to implement messaging
      //build some message function
      //add messages to the queue
      //how/when should i process messages?
    //}
  }
}

void client_write(FILE* fd, char* string){
  // char s[1000];
  // sprintf(s, string);
  // write(fileno(fd), s, strlen(s));
  // fflush(fd);
  fputs(string, fd);
  fflush(fd);
}

void room_set(JRB rooms, char* name){
  room *r = (room *)malloc(sizeof(room));
  //initialize room values
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
  //insert room struct into tree
  jrb_insert_str(rooms, name, new_jval_v((void *)r));
}


int main(int argc, char **argv){
  char *un, c, s[1000];
  int port, sock, fd;
  FILE *fsock;
  pthread_t thread;
  JRB tmp;

  /* Parse the command line and error check. */

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



  /* Serve the socket and accept the connection. */
//
  sock = serve_socket(port);

  jrb_traverse(tmp, rooms){
    room* r = (room *)tmp->val.v;
    // dll_append(r->clients, new_jval_s(strdup("John")));
    // dll_append(r->clients, new_jval_s(strdup("Peter")));
    // dll_append(r->clients, new_jval_s(strdup("David")));
    printf("Name: %s\n", tmp->key);
  }
  
  while(1){

  printf("Waiting...\n");
  fd = accept_connection(sock);

  pthread_create(&thread, NULL, create_client, (void*)&fd);
  pthread_detach(thread);

  }
  exit(0);
}