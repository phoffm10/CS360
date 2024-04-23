//Peter Hoffman
//Lab 8 - jshell

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

void err_print_command(Command* c){
    Dllist tmp;
    fprintf(stderr, "Stdin: \t%s\n", c->stdin);
    fprintf(stderr, "Stdout: %s\t(Append=%d)\n", c->stdout, c->append_stdout);
    fprintf(stderr, "Wait: \t%d\n", c->wait);
    fprintf(stderr, "Num commands: \t%d\n", c->n_commands);
    //print array of argvs and argc for each command
    for(int i = 0; i < c->n_commands; i++){
        fprintf(stderr, "Command %d:\n", i+1);
        fprintf(stderr, "argc: \t%d\n", c->argcs[i]);
        fprintf(stderr, "argv[]:\n");
        for(int j = 0; j < c->argcs[i]; j++){
            fprintf(stderr, "\t%d: %s\n", j, c->argvs[i][j]);
        }
    }
}

//execute command function
void execute_command(Command* c){
    JRB pids;
    JRB tmp;
    Dllist dpids, dtmp;
    dpids = new_dllist();
    int new_fd;
    int prev_pipe = 0;
    pids = make_jrb();
    int pipes[c->n_commands - 1][2];
    pid_t pid;

    for(int i = 0; i < c->n_commands; i++){

        if (i < c->n_commands - 1) {
            if (pipe(pipes[i]) == -1) {
                perror("pipe");
                exit(1);
            }
        }
        fflush(stdout);
        fflush(stderr);
        fflush(stdin);
        pid = fork();
        if (pid == 0) {
            if(c->stdin != NULL){
                if(i == 0){
                    new_fd = open(c->stdin, O_RDONLY);
                    if(new_fd == -1){
                        perror("STDIN");
                        exit(1);
                    }
                    if(dup2(new_fd, 0) == -1){
                        perror("STDIN DUP");
                        close(new_fd);
                        exit(1);
                    }
                    close(new_fd);
                }
            }
            if(c->stdout != NULL){
                if(i == (c->n_commands - 1)){
                    if(c->append_stdout == true){
                        new_fd = open(c->stdout, O_WRONLY | O_APPEND | O_CREAT, 0644);
                    }
                    else{
                        new_fd = open(c->stdout, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                    }
                    if(new_fd < 0){
                        perror("STDOUT");
                        exit(1);
                    }
                    if(dup2(new_fd, 1) == -1){
                        perror("STDOUT DUP");
                        close(new_fd);
                        exit(1);
                    }
                    close(new_fd);
                }
            }

            execvp(c->argvs[i][0], c->argvs[i]);
            perror(c->argvs[i][0]);
            exit(1); 
        }
        else if (pid > 0){
        //else{
            if(c->wait == true){
                //printf("pid: %d\n", pid);
                jrb_insert_int(pids, pid, new_jval_i(pid));
                //add pid to tree
            }
            else{
                if(i > 0){
                    close(pipes[i - 1][0]);
                    close(pipes[i - 1][1]);
                }
            }
        }
        else{
            perror("fork");
            exit(1);
        }
    }
    while (c->wait && wait(NULL) != pid);
    // if(c->wait == true){
    //     while(!jrb_empty(pids)){
    //         int tpid;
    //         int status;
    //         tpid = wait(&status);
    //         if(tpid == -1){
    //             // perror("wait");
    //             break;
    //         }
    //         tmp = jrb_find_int(pids, tpid);
    //         if(tmp != NULL){
    //             jrb_delete_node(tmp);
    //         }       
    //     }
    // }
    //null_set(c);
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
            continue;
        }
        if(is->NF == 0){
            continue;
        }
        else if(strcmp(temp, "END") == 0){
            //delete comlist

            if(print){
                print_command(c);
                err_print_command(c);
            }
            //pass struct to execute command
            if(!no_command){
                execute_command(c);
                null_set(c);
            }
            if(ready){
                printf("READY\n");
            }            
        }
        else if(strcmp(temp, "NOWAIT") == 0){
            //Flag nowait
            c->wait = false;
        }
        else if(strcmp(temp, "<") == 0){
            //Set redirect
            c->stdin = strdup(is->fields[1]);
        }
        else if(strcmp(temp, ">") == 0){
            //set redirect
            c->stdout = strdup(is->fields[1]);
        }
        else if(strcmp(temp, ">>") == 0){
            //set redirect
            c->append_stdout = true;
            c->stdout = strdup(is->fields[1]);
        }
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