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

//-------NOTES---------
// how do i compile into a single executable?
// gcc -c test.c

// take all object files and headers that are compiles and concatenate to final executable
// best way to determine flags and necessary actions

// using stat()
// int time = stat(f1.c);

bool should_recompile(char *cfile) {
    struct stat cfile_stat;
    stat(cfile, &cfile_stat);
    long cfile_mod_time = cfile_stat.st_mtime;

    // Do same thing for o file
    struct stat ofile_stat;
    //stat(ofile, &ofile_stat);
    long ofile_mod_time = ofile_stat.st_mtime;

    // Is the cfile more recent?
    return cfile_mod_time > ofile_mod_time;
}

// sprintf(cmd, "prints to a string cmd");
// system(cmd)==0;
//-------------------------------------------

void print_dll(Dllist list)
{
    Dllist tmp;
    dll_traverse(tmp, list)
    {
        printf("%s ", tmp->val.s);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    IS is;
    int nsize, esize, i;
    char *temp;
    char *exec;
    // bool needs_compile = false;

    // storing lists
    Dllist cfiles;
    Dllist hfiles;
    Dllist flags;
    Dllist libraries;
    Dllist tmp;

    cfiles = new_dllist();
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

        char *temp = is->fields[0];
        if (strcmp(temp, "C") == 0)
        {
            for (i = 1; i < is->NF; i++)
            {
                dll_append(cfiles, new_jval_s(strdup(is->fields[i])));
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
    printf("DLL-------------------\n");

    printf("C files: ");
    print_dll(cfiles);

    printf("H files: ");
    print_dll(hfiles);

    printf("Executable: %s\n", exec);

    printf("Flags: ");
    print_dll(flags);

    printf("Libraries: ");
    print_dll(libraries);

    printf("DLL-------------------\n");

    
    
    free(exec);
    jettison_inputstruct(is);
    dll_traverse(tmp, cfiles) {
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
    free_dllist(hfiles);
    free_dllist(flags);
    free_dllist(libraries);

    return 0;
}