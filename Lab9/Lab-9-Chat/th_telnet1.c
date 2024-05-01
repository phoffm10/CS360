/*
 * CS360: th_telnet.c
 * Jim Plank
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "socketfun.h"

void *inout(void *v)
{
  int *fds;
  int i;
  char s[1000];

  fds = (int *) v;
  while(1) {
    i = read(fds[0], s, 1000);
    if (i == 0) { exit(0); return NULL; }
    write(fds[1], s, i);
  }
}

main(int argc, char **argv)
{
  pthread_t tid, tid2;
  void *retval;
  int stdintosock[2];
  int socktostdout[2];
  int fd;

  if (argc != 3) {
    fprintf(stderr, "usage: jtel host port\n");
    exit(1);
  }

  fd = request_connection(argv[1], atoi(argv[2]));
  stdintosock[0] = 0;
  stdintosock[1] = fd;
  socktostdout[0] = fd;
  socktostdout[1] = 1;

  pthread_create(&tid, NULL, inout, stdintosock);
  pthread_create(&tid2, NULL, inout, socktostdout);
  pthread_exit(NULL);

}
