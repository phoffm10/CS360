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

void client_write(FILE* fd, char* string);

//rb tree to hold all the rooms
JRB rooms;


//function to create chat room
//function to client
void *create_client(void* fd){
  char s[1000];
  //malloc struct
  client *c = (client *)malloc(sizeof(client));
  //populate struct
  c->sock_read = fdopen(*(int *)fd, "r");
  c->sock_write = fdopen(*(int *)fd, "w");
  
  client_write(c->sock_write, "Chat Rooms:\n\n");

  JRB tmp;
  jrb_traverse(tmp, rooms){
    //need to show current clients in each room as well
    room* r = (room *)tmp->val.v;
    client_write(c->sock_write, r->name);
    client_write(c->sock_write, ": ");
    if(!dll_empty(r->clients)){
      Dllist dtmp;
      dll_traverse(dtmp, r->clients){
        client_write(c->sock_write, dtmp->val.s);
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
    c->name = strdup(s);
  }

  client_write(c->sock_write, "Enter chat room:\n");
  if (fgets(s, 1000, c->sock_read) == NULL) {
    printf("Error -- socket closed\n");
    exit(1);
  } else {
    //add name to room
    bool found = false;
    // tmp = NULL;
    // tmp = jrb_find_str(rooms, s);
    jrb_traverse(tmp, rooms){      
      if(strcmp(tmp->key.s, s) == 0){
        bool found = true;
        //room* r = (room *)tmp->val.v;
        break;
      }
    }
    if(found == false){
      client_write(c->sock_write, "Room does not exist, exiting\n");
      exit(1);
    }
    //This doesnt work----------------
    tmp = jrb_find_str(rooms, s);
    room* r = (room *)tmp->val.v;
    pthread_mutex_lock(r->lock);
    dll_append(r->clients, new_jval_s(strdup(c->name)));
    pthread_mutex_unlock(r->lock);
    //This needs to write to everyone
    client_write(c->sock_write, c->name);
    client_write(c->sock_write, " has joined\n");
  /*
    lock mutex
    add to client list
    send hello message
  */
  }

}

void client_write(FILE* fd, char* string){
  char s[1000];
  sprintf(s, string);
  write(fileno(fd), s, strlen(s));
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