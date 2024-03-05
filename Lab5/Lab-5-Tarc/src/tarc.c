//Peter Hoffman
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

/*
TODO
//functions
$DONE$filename - is this a dir
$DONE$filename - returns filesize (for files only)
filename - gives inodes
filename - returns mode
filename - retuens modified time
filename - returns file contents

logic//
takes array of inodes, check if inode is processed

main tarc builder

*/
bool is_this_dir(char* filename);
int filesize(char* filename);



bool is_this_dir(char* filename){
    struct stat buf;
    int exists;
    exists = stat(filename, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", filename);
      exit(1);
    } 
    if (S_ISDIR(buf.st_mode)){
        return true;
    }
    return false;
}

int filesize(char* filename){
    int size;
    struct stat buf;
    int exists;
    exists = stat(filename, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", filename);
      exit(1);
    }
    size = buf.st_size;
    return size;
}

int main(){
    char* file = "d1/f1.txt";
    if(is_this_dir(file) == true){
        printf("%s is a directory\n", file);
    }
    else{
        printf("%s is not directory\n", file);
        printf("%s size is: %d\n", file, filesize(file));
    }
    return 0;
}