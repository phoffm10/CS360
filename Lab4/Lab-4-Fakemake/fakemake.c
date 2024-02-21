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

/*
TODO
traverse hfiles and check times and existence
traverse cfiles and check times and existence
set compilation flags if needed -- should i switch to a dllist of structs?
write command building function
*/

//why doesnt fmakefile check work
//perror
//valgrind errors on command functions

//-------NOTES---------
// how do i compile into a single executable?
// gcc -c test.c

// take all object files and headers that are compiles and concatenate to final executable
// best way to determine flags and necessary actions

// using stat()
// int time = stat(f1.c);

//check if file exists
// if (file_exists(av[1])){
//     printf("%s exists\n", av[1]);
// }
// else{
//     printf("%s does not exist\n", av[1]);
// }

// sprintf(cmd, "prints to a string cmd");
// system(cmd)==0;
//-------------------------------------------
char* compiling_command(char *cfile, Dllist flags){
    
    Dllist tmp;
    char* cmd_base = "gcc -c";
    int length = strlen(cmd_base) + strlen(cfile) + 1;  // +1 for null terminator
    dll_traverse(tmp, flags) {
        length += strlen(tmp->val.s) + 1;  // +1 for space separator
    }
    char* cmd = (char*)malloc(length);
    
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
    struct stat cfile_stat;
    stat(cfile, &cfile_stat);
    long cfile_mod_time = cfile_stat.st_mtime;

    // Do same thing for o file
    struct stat ofile_stat;
    stat(ofile, &ofile_stat);
    long ofile_mod_time = ofile_stat.st_mtime;

    // Is the cfile more recent?
    return cfile_mod_time > ofile_mod_time;
}

bool file_exists(char *filename){
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
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
    char *exec;
    bool new_exec = false;

    // storing lists
    Dllist cfiles;
    Dllist ofiles;
    Dllist hfiles;
    Dllist flags;
    Dllist libraries;
    Dllist tmp, tmp2, tmp3;

    cfiles = new_dllist();
    ofiles = new_dllist();
    hfiles = new_dllist();
    flags = new_dllist();
    libraries = new_dllist();

    int trash = argc;
    trash += 1;

    is = new_inputstruct(argv[1]);

    // doesnt work------------------------------
    if (is == NULL)
    {
        is = new_inputstruct("fmakefile");
        printf("foundfile");
        if (is == NULL)
        {
            printf("error\n");
        }
        // search for fmakefile
        // if not found, error out
    }
    //---------------------------------------------

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

    //testing to print out dll contents
    printf("DLL-------------------\n");

    printf("C files: ");
    print_dll(cfiles);

    printf("O files: ");
    print_dll(ofiles);

    printf("H files: ");
    print_dll(hfiles);

    printf("Executable: %s\n", exec);

    printf("Flags: ");
    print_dll(flags);

    printf("Libraries: ");
    print_dll(libraries);

    printf("DLL-------------------\n");

    //checks if c files exist
    dll_traverse(tmp, cfiles){
        if (file_exists(tmp->val.s)){
            continue;
        }
        else{
            fprintf(stderr,"%s doesnt exist\n", tmp->val.s);
            exit(1);
        }
    }
    //check if h files exist
    dll_traverse(tmp, hfiles){
        if (file_exists(tmp->val.s)){
            continue;
        }
        else{
            fprintf(stderr,"%s doesnt exist\n", tmp->val.s);
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
                    printf("%s\n", compiling_command(tmp2->val.s, flags));
                    system(compiling_command(tmp2->val.s, flags));
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
                    printf("%s\n", compiling_command(tmp->val.s, flags));
                    system(compiling_command(tmp->val.s, flags));
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
                        printf("%s\n", compiling_command(tmp3->val.s, flags));
                        system(compiling_command(tmp3->val.s, flags));
                    }
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
        printf("%s\n", exec_command(ofiles, flags, libraries, exec));
        system(exec_command(ofiles, flags, libraries, exec));
    }
    else{
        printf("%s up to date\n", exec);
    }
    
    
    /*
    //testing command creation
    dll_traverse(tmp, cfiles){
        printf("%s\n", compiling_command(tmp->val.s, flags));
        
    }
    //everything must be compiled before running the the exec function
    printf("%s\n", exec_command(ofiles, flags, libraries, exec));
    */

    //freeing memory 
    free(exec);
    jettison_inputstruct(is);
    dll_traverse(tmp, cfiles) {
        free(tmp->val.s);
    }
    dll_traverse(tmp, ofiles) {
        free(tmp->val.s);
    }
    dll_traverse(tmp, hfiles) {
        free(tmp->val.s);
    }
    dll_traverse(tmp, flags) {
        free(tmp->val.s);
    }
    dll_traverse(tmp, libraries) {
        free(tmp->val.s);
    }
    free_dllist(cfiles);
    free_dllist(ofiles);
    free_dllist(hfiles);
    free_dllist(flags);
    free_dllist(libraries);

    return 0;
}