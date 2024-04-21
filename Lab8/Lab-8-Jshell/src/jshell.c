//Peter Hoffman

//Qs
//How should i implement execute_command
//how do i implement pipes, how does the order not matter?

//TODO
//-run single commands

//includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

//struct
typedef struct Command{
  char *stdin;          /* Filename from which to redirect stdin.  NULL if empty.*/ 
  char *stdout;         /* Filename to which to redirect stdout.  NULL if empty.*/ 
  bool append_stdout;   /* Boolean for appending.*/ 
  bool wait;            /* Boolean for whether I should wait.*/ 
  int n_commands;       /* The number of commands that I have to execute*/ 
  int *argcs;           /* argcs[i] is argc for the i-th command*/ 
  char ***argvs;        /* argcv[i] is the argv array for the i-th command*/ 
  Dllist comlist;       /* I use this to incrementally read the commands.*/ 
} Command;

//Globals
bool ready = false;
bool print = false;
bool no_command = false;

void null_set(Command* c){
    //Initializes element struct
    c->stdin = NULL;
    c->stdout = NULL;
    c->append_stdout = false;
    c->wait = true;
    c->n_commands = 0;
    c->argcs = NULL;
    c->argvs = NULL;
    if(!dll_empty){
        free_dllist(c->comlist);
    }
    c->comlist = new_dllist();
}

void print_command(Command* c){
    Dllist tmp;
    printf("Stdin: \t%s\n", c->stdin);
    printf("Stdout: %s\t(Append=%d)\n", c->stdout, c->append_stdout);
    printf("Wait: \t%d\n", c->wait);
    printf("Num commands: \t%d\n", c->n_commands);
    //print array of argvs and argc for each command
    for(int i = 0; i < c->n_commands; i++){
        printf("Command %d:\n", i+1);
        printf("argc: \t%d\n", c->argcs[i]);
        printf("argv[]:\n");
        for(int j = 0; j < c->argcs[i]; j++){
            printf("\t%d: %s\n", j, c->argvs[i][j]);
        }
    }
}

//execute command function
void execute_command(Command* c){
    //needs to actually execute commands here---
    JRB pids;
    JRB tmp;
    int new_fd;
    pids = make_jrb();
    int pid;

    for(int i = 0; i < c->n_commands; i++){

        int pipes[128][2];
        fflush(stdout);
        fflush(stderr);
        fflush(stdin);
        pid = fork();
        if (pid == 0) {
            if(c->stdin && i == 0){
                close(STDIN_FILENO);
                // Opening WITHOUT append
                new_fd = open(c->stdin, O_WRONLY | O_TRUNC | O_CREAT);

                dup2(new_fd, STDIN_FILENO);
            }
            else if (i != 0){
                close(STDERR_FILENO);
                dup2(pipes[i-1][0], STDIN_FILENO); // Pipe the last programs STDOUT into this programs STDIN
            }
            if(c->stdout && i == c->n_commands - 1){
                close(STDOUT_FILENO);
                if(c->append_stdout){
                new_fd = open(c->stdout, O_WRONLY | O_APPEND | O_CREAT);
                if (new_fd < 0) {
                    perror(c->stdout);
                    exit(2);
                }
                    // fd2 = open("f2.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
                    // if (fd2 < 0) {
                    // perror("catf1f2: f2.txt");
                    // exit(2);
                    // }
                }
                else{
                new_fd = open(c->stdout, O_WRONLY | O_TRUNC | O_CREAT);
                if (new_fd < 0) {
                    perror(c->stdout);
                    exit(2);
                }
                }
                dup2(new_fd, STDOUT_FILENO);
            }
            else if (i != c->n_commands - 1){
                close(STDOUT_FILENO);
                dup2(pipes[i][1], STDOUT_FILENO); // Pipe the last programs STDOUT into this programs STDIN
            }
            execvp(c->argvs[i][0], c->argvs[i]);
            perror(c->argvs[i][0]);
            exit(1); 
                // execve("/bin/cat", newargv, envp);
                // perror("execve(bin/cat, newargv, envp)");
                // exit(1); 
        }
        else{
            if(c->wait){
                jrb_insert_int(pids, pid, new_jval_i(pid));
                //add pid to tree
            }
        }
    }
    //this doesnt work
    if(c->wait){
        while(!jrb_empty(pids)){
            int tpid;
            int status;
            tpid = (int)wait(&status); // Wait for specific child process to terminate
            if(tpid == -1){
                break;
            }
            tmp = jrb_find_int(pids, tpid);
            if(tmp != NULL){
                jrb_delete_node(tmp);
            }
        }
    }
    //------------------------------------------
    null_set(c);
}
//main
int main(int argc, char* argv[]){

    //Grabs command line args and sets flags
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "r") == 0 || strcmp(argv[i], "R") == 0){
                ready = true;
            }
            else if(strcmp(argv[i], "p") == 0 || strcmp(argv[i], "P") == 0){
                print = true;
            }
            else if(strcmp(argv[i], "n") == 0 || strcmp(argv[i], "N") == 0){
                no_command = true;
            }
        }
    }

    IS is;
    is = new_inputstruct(NULL);
    char* temp;

    Command* c = malloc(sizeof(Command));
    null_set(c);

    if(ready){
        printf("READY\n");
    } 

    while(get_line(is) != -1){
        temp = is->fields[0];
        if(temp[0] == '#'){
            //printf("ignoring\n");
            continue;
        }
        if(is->NF == 0){
            //printf("ignoring\n");
            continue;
        }
        else if(strcmp(temp, "END") == 0){
            //delete comlist

            if(print){
                print_command(c);
            }
            //pass struct to execute command
            if(!no_command){
                execute_command(c);
            }

            //printf("read END\n");
            if(ready){
                printf("READY\n");
            }            
        }
        else if(strcmp(temp, "NOWAIT") == 0){
            //Flag nowait
            c->wait = false;
            //printf("read NOWAIT\n");
        }
        else if(strcmp(temp, "<") == 0){
            //Set redirect
            c->stdin = strdup(is->fields[1]);
            //printf("read <\n");
            //printf("stdin is: %s\n", is->fields[1]);
        }
        else if(strcmp(temp, ">") == 0){
            //set redirect
            c->stdout = strdup(is->fields[1]);
            //printf("read >\n");
            //printf("stdout is: %s\n", is->fields[1]);
        }
        else if(strcmp(temp, ">>") == 0){
            //set redirect
            c->append_stdout = true;
            //printf("read >>\n");
            //printf("stdout append is: %s\n", is->fields[1]);
        }
        // else if(strcmp(temp, "PRINTC") == 0){
        //     //Print command
        //     print_command(c);
        // }
        else{
            //increments num of commands
            c->argvs = (char***)realloc(c->argvs, (c->n_commands + 1) * sizeof(char**));
            // Allocate memory for the new command
            c->argvs[c->n_commands] = (char**)malloc((is->NF + 1) * sizeof(char *));
            // Copy arguments for the new command
            for (int i = 0; i < is->NF; i++) {
                c->argvs[c->n_commands][i] = strdup(is->fields[i]);
            }
            c->argvs[c->n_commands][is->NF] = NULL; 
            c->argcs = (int*)realloc(c->argcs, (c->n_commands + 1) * sizeof(int));
            c->argcs[c->n_commands] = is->NF;

            dll_append(c->comlist, new_jval_s(strdup(is->text1)));
            c->n_commands++;
        }
    }
    return 0;
}