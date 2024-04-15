//Peter Hoffman

//Qs
//How should i implement execute_command

//TODO
//-finish struct populating
//-finishes r,p,n flags
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
    c->comlist = new_dllist();
}

void print_command(Command* c){
    Dllist tmp;
    printf("stdin: %s\n", c->stdin);
    printf("stdout: %s\n", c->stdout);
    printf("append stdout: %d\n", c->append_stdout);
    printf("wait: %d\n", c->wait);
    printf("num commands: %d\n", c->n_commands);
    //print argc array
    //print array of argvs
    //print comlist
    dll_traverse(tmp, c->comlist){
        printf("command: %s", tmp->val.s);
    }
}

//execute command function
void execute_command(Command* c){

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

    while(get_line(is) != -1){
        temp = is->fields[0];
        if(temp[0] == '#'){
            printf("ignoring\n");
            continue;
        }
        else if(strcmp(temp, "END") == 0){
            Dllist tmp;
            
            //create argcs and argvs from comlist
            dll_traverse(tmp, c->comlist){
                //traverse each string and pull argc and argv
                //populate struct
            }

            //delete comlist


            //pass struct to execute command
            //execute_command(c);
            printf("read END\n");
        }
        else if(strcmp(temp, "NOWAIT") == 0){
            //Flag nowait
            c->wait = false;
            printf("read NOWAIT\n");
        }
        else if(strcmp(temp, "<") == 0){
            //Set redirect
            c->stdin = strdup(is->fields[1]);
            printf("read <\n");
            printf("stdin is: %s\n", is->fields[1]);
        }
        else if(strcmp(temp, ">") == 0){
            //set redirect
            c->stdout = strdup(is->fields[1]);
            printf("read >\n");
            printf("stdout is: %s\n", is->fields[1]);
        }
        else if(strcmp(temp, ">>") == 0){
            //set redirect
            c->append_stdout = true;
            printf("read >>\n");
            printf("stdout append is: %s\n", is->fields[1]);
        }
        else if(strcmp(temp, "PRINTC") == 0){
            //Print command
            print_command(c);
        }
        else{
            //increments num of commands
            c->n_commands++;
            //should store entire command string in comlist
            dll_append(c->comlist, new_jval_s(strdup(is->text1)));
        }
    }
    return 0;
}