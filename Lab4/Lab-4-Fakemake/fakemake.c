// Peter Hoffman
// CS360 Lab 4

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

void print_dll(Dllist list);

char* compiling_command(char *cfile, Dllist flags){
    
    Dllist tmp;
    char* cmd_base = "gcc -c";
    int length = strlen(cmd_base) + strlen(cfile) + 1;  // +1 for null terminator
    dll_traverse(tmp, flags) {
        length += strlen(tmp->val.s) + 1;  // +1 for space separator
    }
    char* cmd = (char*)malloc(length * 10);
    
    strcpy(cmd, cmd_base);
    dll_traverse(tmp, flags){
        strcat(cmd, " ");
        strcat(cmd, tmp->val.s);
    }
    strcat(cmd, " ");
    strcat(cmd, cfile);
    return cmd;
}

char* exec_command(Dllist ofiles, Dllist flags, Dllist libraries, char *exec){
    
    Dllist tmp;
    char* cmd_base = "gcc -o ";
    int length = strlen(cmd_base) + strlen(exec) + 1;  // +1 for null terminator
    dll_traverse(tmp, flags) {
        length += strlen(tmp->val.s) + 1;  // +1 for space separator
    }
    dll_traverse(tmp, ofiles) {
        length += strlen(tmp->val.s) + 1;
    }
    dll_traverse(tmp, libraries) {
        length += strlen(tmp->val.s) + 1;
    }
    char* cmd = (char*)malloc(length);
    
    strcpy(cmd, cmd_base);
    strcat(cmd, exec);
    dll_traverse(tmp, flags){
        strcat(cmd, " ");
        strcat(cmd, tmp->val.s);
    }
    dll_traverse(tmp, ofiles){
        strcat(cmd, " ");
        strcat(cmd, tmp->val.s);
    }
    dll_traverse(tmp, libraries){
        strcat(cmd, " ");
        strcat(cmd, tmp->val.s);
    }
    return cmd;
}


bool first_arg_newer(char *cfile, char *ofile){
    struct stat cfile_stat = {0};
    stat(cfile, &cfile_stat);
    long cfile_mod_time = cfile_stat.st_mtime;

    // Do same thing for o file
    struct stat ofile_stat = {0};
    stat(ofile, &ofile_stat);
    long ofile_mod_time = ofile_stat.st_mtime;

    // Is the cfile more recent?
    return cfile_mod_time > ofile_mod_time;
}

bool file_exists(char *filename){
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

bool contains(Dllist list, char *filename){
    Dllist tmp;
    dll_traverse(tmp, list){
        if(strcmp(filename, tmp->val.s) == 0){
            return 1;
        }
    }
    return 0;
}

void print_dll(Dllist list){
    Dllist tmp;
    dll_traverse(tmp, list)
    {
        printf("%s ", tmp->val.s);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    IS is;
    int i;
    char *temp;
    char *exec = NULL;
    bool new_exec = false;

    // storing lists
    Dllist cfiles;
    Dllist ofiles;
    Dllist hfiles;
    Dllist flags;
    Dllist libraries;
    Dllist to_compile;
    Dllist tmp, tmp2, tmp3;

    cfiles = new_dllist();
    ofiles = new_dllist();
    hfiles = new_dllist();
    flags = new_dllist();
    libraries = new_dllist();
    to_compile = new_dllist();

    char *fmakefile = argc > 1? argv[1] : "fmakefile";
    if (file_exists(fmakefile)) {
        is = new_inputstruct(fmakefile);
    } else {
        fprintf(stderr, "Input file doesn't exist\n");
        return 1;
    }

    while (get_line(is) >= 0){

        if (is->NF == 0) continue;

        temp = is->fields[0];
        if (strcmp(temp, "C") == 0)
        {
            for (i = 1; i < is->NF; i++)
            {
                dll_append(cfiles, new_jval_s(strdup(is->fields[i])));
                printf("%s", (is->fields[i])-1);
            }
        }
        else if (strcmp(temp, "H") == 0)
        {
            for (i = 1; i < is->NF; i++)
            {
                dll_append(hfiles, new_jval_s(strdup(is->fields[i])));
            }
        }
        else if (strcmp(temp, "E") == 0)
        {
            if(exec != NULL){
                fprintf(stderr, "fmakefile (%d) cannot have more than one E line\n", is->line);
                exit(1);
            }
            exec = strdup(is->fields[1]);            
        }
        else if (strcmp(temp, "F") == 0)
        {
            for (i = 1; i < is->NF; i++)
            {
                dll_append(flags, new_jval_s(strdup(is->fields[i])));
            }
        }
        else if (strcmp(temp, "L") == 0)
        {
            for (i = 1; i < is->NF; i++)
            {
                dll_append(libraries, new_jval_s(strdup(is->fields[i])));
            }
        }
    }

    //Creates .o files (not compiling) for ofiles dllist
    dll_traverse(tmp, cfiles){
        temp = strdup(tmp->val.s);
        temp[strlen(temp)-2] = '\0';
        strcat(temp, ".o");
        dll_append(ofiles, new_jval_s(strdup(temp)));
        free(temp);
    }

    if(exec == NULL){
        fprintf(stderr, "No executable specified\n");
        exit(1);
    }

    //check if h files exist
    dll_traverse(tmp, hfiles){
        if (file_exists(tmp->val.s)){
            continue;
        }
        else{
            fprintf(stderr,"fmakefile: %s: No such file or directory\n", tmp->val.s);
            exit(1);
        }
    }

    //if the .o files doesnt exist, compile c file
    dll_traverse(tmp, ofiles){
        if (file_exists(tmp->val.s)){
            continue;
        }
        else{
            //compile c files with missing .o files
            dll_traverse(tmp2, cfiles){
                //returns 0 for c files that corresponds to o file
                if(strncmp(tmp2->val.s, tmp->val.s, strlen(tmp->val.s)-1) == 0){
                    new_exec = true;
                    if(contains(to_compile, tmp2->val.s) == 0){
                        dll_append(to_compile, new_jval_s(tmp2->val.s));
                    }
                }
            }
        }
    }

    //if c file more recent than o, recompile c
    dll_traverse(tmp, cfiles){
        //compile c files with missing .o files
        dll_traverse(tmp2, ofiles){
            //returns 0 for c files that corresponds to o file
            if(strncmp(tmp2->val.s, tmp->val.s, strlen(tmp->val.s)-1) == 0){
                if(first_arg_newer(tmp->val.s, tmp2->val.s)){
                    new_exec = true;

                    if(contains(to_compile, tmp->val.s) == 0){
                        dll_append(to_compile, new_jval_s(tmp->val.s));
                    }
                }
            }
        }
    }
    
    //if h files are more recent than .o files
    dll_traverse(tmp, ofiles){
        dll_traverse(tmp2, hfiles){
            if(first_arg_newer(tmp2->val.s, tmp->val.s)){
                //compile corresponding c file
                dll_traverse(tmp3, cfiles){
                    if(strncmp(tmp3->val.s, tmp->val.s, strlen(tmp->val.s)-1) == 0){
                        new_exec = true;
                        if(contains(to_compile, tmp3->val.s) == 0){
                            dll_append(to_compile, new_jval_s(tmp3->val.s));
                        }
                    }
                }
            }
        }
    }

    dll_traverse(tmp, cfiles){
        dll_traverse(tmp2, to_compile){
            if(strcmp(tmp->val.s, tmp2->val.s) == 0){
                if (file_exists(tmp->val.s)){
                    char *cmd = compiling_command(tmp->val.s, flags);
                    printf("%s\n", cmd);
                    if(system(cmd) != 0){
                        fprintf(stderr, "Command failed.  Exiting\n");
                        exit(1);
                    }
                    free(cmd);
                }
                else{
                    fprintf(stderr,"fmakefile: %s: No such file or directory\n", tmp->val.s);
                    exit(1);
                }
            }
        }
    }

    //if executable doesnt exist
    if(file_exists(exec) == 0){
        new_exec = true;
    }

    //if executable is less recent than o files
    dll_traverse(tmp, ofiles){
        if(first_arg_newer(tmp->val.s, exec)){
            new_exec = true;
        }
    }

    //checking if executable should run
    if(new_exec == true){
        char *cmd = exec_command(ofiles, flags, libraries, exec);
        printf("%s\n", cmd);
        if(system(cmd) != 0){
            fprintf(stderr, "Command failed.  Fakemake exiting\n");
            exit(1);
        }
        free(cmd);
    }
    else{
        printf("%s up to date\n", exec);
    }

    //freeing memory 
    free(exec);
    jettison_inputstruct(is);
    dll_traverse(tmp, cfiles) {
        if(tmp->val.s != NULL){
            free(tmp->val.s);
        }
    }
    dll_traverse(tmp, ofiles) {
        if(tmp->val.s != NULL){
            free(tmp->val.s);
        }
    }
    dll_traverse(tmp, hfiles) {
        if(tmp->val.s != NULL){
            free(tmp->val.s);
        }
    }
    dll_traverse(tmp, flags) {
        if(tmp->val.s != NULL){
            free(tmp->val.s);
        }
    }
    dll_traverse(tmp, libraries) {
        if(tmp->val.s != NULL){
            free(tmp->val.s);
        }
    }
    
    free_dllist(cfiles);
    free_dllist(ofiles);
    free_dllist(hfiles);
    free_dllist(flags);
    free_dllist(libraries);
    free_dllist(to_compile);

    return 0;
}