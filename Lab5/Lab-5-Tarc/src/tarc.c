// Peter Hoffman
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

char* dir_name(char* pathname);
char* get_dir(char* path);
bool is_this_dir(char *filename);
long file_size(char *filename);
long file_inode(char *filename);
int file_mode(char *filename);
long file_mod_time(char *filename);
char *file_bytes(char *filename);
char *prefix(char *basedir, char *filename);
void* traverse(char* dir);


Dllist inodes;
Dllist dirs;
Dllist printed;
Dllist tmp, tmp2;

//char* dpath = "";
char* parentdir = NULL;
bool isprinted = false;


char* dir_name(char* pathname){
  //find index of final /
  char* dirn;
  int pathsize = strlen(pathname);
  int index = 0;
  for (int i = 0; i < pathsize; i++){
    if(pathname[i] == '/'){
      index = i + 1;
    }
  }
  //copy from final / to end
  if(index != 0){
    dirn = (char*)malloc((pathsize-index)+1);
    memcpy(dirn, pathname+index, pathsize-index);
    dirn[pathsize - index] = '\0';
    return dirn;
  }
  else{
    return pathname;
  }
}

char* get_dir(char* path){
  char* dir_name;
  char* maindir = strdup(parentdir);

  char* dir_position = strstr(path, maindir);
  if (dir_position == NULL) {
      // Directory not found in the full path
      return NULL;
  }

  // Calculate the length of the subdirectory path
  int dir_namesize = (int)strlen(dir_position);

  // Allocate memory for the subdirectory path
  dir_name = (char*)malloc(dir_namesize + 1);
  if (dir_name == NULL) {
      // Memory allocation failed
      return NULL;
  }
  // Copy the subdirectory path into the allocated memory
  strcpy(dir_name, dir_position);

  return dir_name;
}

bool is_this_dir(char *filename)
{
  //struct dirent *de;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0)
  {
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  if (S_ISDIR(buf.st_mode))
  {
    return true;
  }
  return false;
}

long file_size(char *filename)
{
  long size;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0)
  {
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  size = (long)buf.st_size;
  return size;
}

long file_inode(char *filename)
{
  long inode;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0)
  {
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  inode = buf.st_ino;
  return inode;
}

int file_mode(char *filename)
{
  int mode;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0)
  {
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  mode = (int)buf.st_mode;
  return mode;
}

long file_mod_time(char *filename)
{
  long mod_time;
  struct stat buf;
  int exists;
  exists = stat(filename, &buf);
  if (exists < 0)
  {
    fprintf(stderr, "Couldn't stat %s\n", filename);
    exit(1);
  }
  // is this correct for seconds?
  mod_time = (long)buf.st_mtime;
  return mod_time;
}

char *file_bytes(char *filename)
{
  // should cat file
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

char *prefix(char *basedir, char *filename)
{
  // malloc length of both + extra char
  char *path;
  path = (char *)malloc((strlen(basedir) + strlen(filename) + 150) * sizeof(char));
  strcpy(path, basedir);
  // strcpy base dir into ptr
  strcat(path, "/");
  // if it doesnt end add slash
  // strcat filename
  strcat(path, filename);
  path[strlen(path)] = '\0';
  // return ptr
  return path;
}

void* traverse(char* dir){
  DIR *d;
  struct dirent *de;
  struct stat fbuf;
  int exists;
  char* file;
  char* dirname;
  char* displayname;
  bool seen = false;

  d = opendir(dir);
  if (d == NULL)
  {
    perror(dir);
    exit(1);
  }

  for (de = readdir(d); de != NULL; de = readdir(d))
  {
    if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
    
    // need to build name with prefix
    file = prefix(dir, de->d_name);
    dirname = get_dir(file);
    seen = false;

    exists = stat(file, &fbuf);
    if (exists < 0)
    {
      fprintf(stderr, "Couldn't stat %s\n", file);
    }
    else
    {
      int fnamesize = (int)strlen(dirname);
      char* fname = dirname;
      long finode = file_inode(file);

      fwrite(&fnamesize, sizeof(fnamesize), 1, stdout);
      fwrite(fname, sizeof(char), fnamesize, stdout);
      fwrite(&finode, sizeof(finode), 1, stdout);

      dll_traverse(tmp, inodes){
        //if seen, set seen to true
        if(file_inode(file) == tmp->val.l){
          seen = true;
        }
      }
      if (!seen) {
        dll_append(inodes, new_jval_l(file_inode(file)));
      }

      if(seen == false){
        int fmode = file_mode(file);
        long fmodt = file_mod_time(file);

        fwrite(&fmode, sizeof(fmode), 1, stdout);
        fwrite(&fmodt, sizeof(fmodt), 1, stdout);

        if (is_this_dir(file) == true )
        {
          //if its a directory, store directory to traverse 
          //traverse(file);
          
          dll_append(dirs, new_jval_s(strdup(file)));
        }
        else
        {//is a file, use file logic to display things
          long fsize = file_size(file);
          char* output = file_bytes(file);

          fwrite(&fsize, sizeof(fsize), 1, stdout);
          fwrite(output, sizeof(char), file_size(file), stdout);

        }
      }
    }
  }
  closedir(d);

  dll_rtraverse(tmp, dirs){
    isprinted = false;
    dll_traverse(tmp2, printed){
      if(strcmp(tmp->val.s, tmp2->val.s) == 0){
        isprinted = true;
      }
    }
    if(!isprinted){
      dll_append(printed, new_jval_s(strdup(tmp->val.s)));
      traverse(tmp->val.s);
    }
  }
}

int main(int argc, char *argv[])
{

  inodes = new_dllist();
  dirs = new_dllist();
  printed = new_dllist();
  
  //need function to pull dir name only
  char* pathname = strdup(argv[1]);
  // char* parentdir = NULL;
  parentdir = dir_name(argv[1]);

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

  traverse(pathname);

  return 0;
}