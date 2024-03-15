// Peter Hoffman
//CS360 Lab 5
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

//Forward Declarations
char* dir_name(char* pathname);
char* get_dir(char* path);
bool is_this_dir(char *filename);
long file_size(char *filename);
long file_inode(char *filename);
int file_mode(char *filename);
long file_mod_time(char *filename);
char *file_bytes(char *filename);
char *prefix(char *basedir, char *filename);
void first_dir(char* arg);
void free_mem();
void* traverse(char* dir);

//Global Variables
Dllist inodes;
Dllist dirs;
Dllist printed;
Dllist tmp, tmp2;

char* parentdir = NULL;
char* file;
char* dirname;
char* pathname;
bool isprinted = false;

//Returns directory at end of path
char* dir_name(char* pathname){
  //Find index of final /
  char* dirn;
  int pathsize = strlen(pathname);
  int index = 0;
  for (int i = 0; i < pathsize; i++){
    if(pathname[i] == '/'){
      index = i + 1;
    }
  }
  //Copy from final / to end, copy string to dirn
  if(index != 0){
    dirn = (char*)malloc((pathsize-index)+1);
    memcpy(dirn, pathname+index, pathsize-index);
    dirn[pathsize - index] = '\0';
    return dirn;
  }
  else{
    //Case if no / found
    return pathname;
  }
}

char* get_dir(char* path){
  char* dir_name;

  //Finds string within a string
  char* dir_position = strstr(path, parentdir);
  if (dir_position == NULL){
      // If string not found
      return NULL;
  }

  //Calculate the length of the substring
  int dir_namesize = (int)strlen(dir_position);

  //Allocate memory for the substring
  dir_name = (char*)malloc(dir_namesize + 1);

  //Copy the substring
  strcpy(dir_name, dir_position);

  return dir_name;
}

bool is_this_dir(char *filename){
  //Calls stat and returns true if directory
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0){
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  if (S_ISDIR(buf.st_mode)){
    return true;
  }
  return false;
}

long file_size(char *filename){
  //Calls stat and returns filesize
  long size;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0){
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  size = (long)buf.st_size;
  return size;
}

long file_inode(char *filename){
  //Calls stat and returns inode
  long inode;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0){
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  inode = buf.st_ino;
  return inode;
}

int file_mode(char *filename){
  //Calls stat and returns mode
  int mode;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0){
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  mode = (int)buf.st_mode;
  return mode;
}

long file_mod_time(char *filename){
  //Calls stat returns mod time
  long mod_time;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0){
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  mod_time = (long)buf.st_mtime;
  return mod_time;
}

char *file_bytes(char *filename){
  //Prints files bytes
  FILE *fp;
  fp = fopen(filename, "rb");
  long bufsize;
  char *c;
  int i;

  bufsize = file_size(filename);
  c = (char *)malloc((bufsize + 1) * sizeof(char));
  fread(c, 1, bufsize, fp);
  c[bufsize] = '\0';
  fclose(fp);

  return c;
}

char *prefix(char *basedir, char *filename){
  //Allocate mem for length of both + extra char and null
  char *path;
  path = (char *)malloc((strlen(basedir) + strlen(filename) + 2) * sizeof(char));
  strcpy(path, basedir);
  //Cat / onto base directory
  strcat(path, "/");
  //Cat filename onto path
  strcat(path, filename);
  path[strlen(path)] = '\0';
  //Return filename
  return path;
}

void first_dir(char* arg){
  //Prints parent directory information
  pathname = strdup(arg);
  parentdir = dir_name(arg);

  int fnamesize = (int)strlen(parentdir);
  char* fname = parentdir;
  long finode = file_inode(pathname);
  int fmode = file_mode(pathname);
  long fmodt = file_mod_time(pathname);

  fwrite(&fnamesize, sizeof(fnamesize), 1, stdout);
  fwrite(fname, sizeof(char), fnamesize, stdout);
  fwrite(&finode, sizeof(finode), 1, stdout);
  fwrite(&fmode, sizeof(fmode), 1, stdout);
  fwrite(&fmodt, sizeof(fmodt), 1, stdout);
}

void free_mem(){
  //Frees memory allocated in traverse
  free(pathname);
  dll_traverse(tmp, dirs){
    if(tmp->val.s != NULL){
      free(tmp->val.s);
    }
  }
  dll_traverse(tmp, printed){
    if(tmp->val.s != NULL){
      free(tmp->val.s);
    }
  }
  free_dllist(inodes);
  free_dllist(dirs);
  free_dllist(printed);
  free(parentdir);

}

void* traverse(char* dir){
  //Open passed directory
  DIR *d;
  struct dirent *de;
  struct stat fbuf;
  int exists;
  bool seen = false;

  d = opendir(dir);
  if (d == NULL){
    perror(dir);
    exit(1);
  }
  //Traverse passed directory
  for (de = readdir(d); de != NULL; de = readdir(d)){
    if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
    
    //Builds full filename and display name
    file = prefix(dir, de->d_name);
    dirname = get_dir(file);
    seen = false;

    //Check if stat succesful
    exists = stat(file, &fbuf);
    if (exists < 0){
      fprintf(stderr, "Couldn't stat %s\n", file);
    }
    else{
      //Inofrmation printed for every file
      int fnamesize = (int)strlen(dirname);
      char* fname = dirname;
      long finode = file_inode(file);

      fwrite(&fnamesize, sizeof(fnamesize), 1, stdout);
      fwrite(fname, sizeof(char), fnamesize, stdout);
      fwrite(&finode, sizeof(finode), 1, stdout);

      dll_traverse(tmp, inodes){
        //Traverse inode list to see if file alredy seen
        if(file_inode(file) == tmp->val.l){
          seen = true;
        }
      }
      if (!seen){
        //Append inode if file not seen
        dll_append(inodes, new_jval_l(file_inode(file)));
      }

      if(seen == false){
        //Information to print if file not already seen
        int fmode = file_mode(file);
        long fmodt = file_mod_time(file);

        fwrite(&fmode, sizeof(fmode), 1, stdout);
        fwrite(&fmodt, sizeof(fmodt), 1, stdout);

        if (is_this_dir(file) == true ){
          //If its a directory, store directory to traverse later
          dll_append(dirs, new_jval_s(strdup(file)));
          free(file);
          free(dirname);
        }
        else{
          //If its a file, print file size and bytes
          long fsize = file_size(file);
          char* output = file_bytes(file);

          fwrite(&fsize, sizeof(fsize), 1, stdout);
          fwrite(output, sizeof(char), file_size(file), stdout);
          free(output);
          free(file);
          free(dirname);
        }
      }
    }
  }
  closedir(d);
  //Traverses stored directories and adds them to printed list
  dll_rtraverse(tmp, dirs){
    isprinted = false;
    dll_traverse(tmp2, printed){
      if(strcmp(tmp->val.s, tmp2->val.s) == 0){
        isprinted = true;
      }
    }
    //If directory not already printed, traverse
    if(!isprinted){
      dll_append(printed, new_jval_s(strdup(tmp->val.s)));
      traverse(tmp->val.s);
    }
    free(de);
  }
}

int main(int argc, char *argv[]){
  //Initializes dllists
  inodes = new_dllist();
  dirs = new_dllist();
  printed = new_dllist();
  
  //Prints first dir information
  first_dir(argv[1]);
  //Traverses the first dir files recursively
  traverse(pathname);
  //Frees memory
  free_mem();

  return 0;
}