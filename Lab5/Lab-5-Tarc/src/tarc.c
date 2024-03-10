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

// how do i print in little endian?
// use fwrite too stdout for little endian

/*
TODO
//functions
$DONE$filename - is this a dir
$DONE$filename - returns filesize (for files only)
$DONE$filename - gives inodes
$DONE$filename - returns mode
$DONE$filename - retuens modified time
$DONE$filename - returns file contents

logic//
takes array of inodes, check if inode is processed

main tarc builder

*/
bool is_this_dir(char *filename);
long file_size(char *filename);
long file_inode(char *filename);
int file_mode(char *filename);
long file_mod_time(char *filename);
char *file_bytes(char *filename);

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
    return dirn;
  }
  else{
    return pathname;
  }
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
  //if (S_ISDIR(buf.st_mode) && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
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
  char* displayname;
  bool seen = false;

  Dllist inodes;
  Dllist tmp;

  inodes = new_dllist();

  d = opendir(dir);
  if (d == NULL)
  {
    perror(dir);
    exit(1);
  }

  char* nopathdir = dir_name(dir);
/*
  long example_inode;
  fwrite(&example_inode, sizeof(example_inode), 1, stdout);

  char *example_file_contents;
  int file_size;

  fwrite(example_file_contents, sizeof(char), file_size, stdout);
*/

  for (de = readdir(d); de != NULL; de = readdir(d))
  {
    if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
    // need to build name with prefix
    file = prefix(dir, de->d_name);
    displayname = prefix(nopathdir, de->d_name);
    //printf("path: %s\n", file);
    seen = false;

    exists = stat(file, &fbuf);
    if (exists < 0)
    {
      fprintf(stderr, "Couldn't stat %s\n", file);
    }
    else
    {
      //int fnamesize = (int)strlen(file);
      int fnamesize = (int)strlen(displayname);
      //char* fname = file;
      char* fname = displayname;
      long finode = file_inode(file);

      fwrite(&fnamesize, sizeof(fnamesize), 1, stdout);
      fwrite(fname, sizeof(char), fnamesize, stdout);
      fwrite(&finode, sizeof(finode), 1, stdout);

      // printf("Namesize: %d\n", (int)strlen(file));
      // printf("Name: %s\n", file);
      // printf("Inode: %ld\n", file_inode(file));

      dll_traverse(tmp, inodes){
        //if seen, set seen to true
        if(file_inode(file) == tmp->val.l){
          printf("\n");
          seen = true;
        }
      }
      if (!seen) {
        dll_append(inodes, new_jval_l(file_inode(file)));
      }
      /*
      printf("------------\n");
      dll_traverse(tmp, inodes){
        printf("%ld", tmp->val.l);
      }
      printf("------------\n");
      */
      if(seen == false){
        int fmode = file_mode(file);
        long fmodt = file_mod_time(file);


        fwrite(&fmode, sizeof(fmode), 1, stdout);
        fwrite(&fmodt, sizeof(fmodt), 1, stdout);
        // printf("Mode: %d\n", file_mode(file));
        // printf("Modification time: %ld\n", file_mod_time(file));
        if (is_this_dir(file) == true )
        {
          //if its a directory, traverse directory
          //if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
          //printf("%s is a directory\n", file);
          printf("\n");
          traverse(file);
        }
        else
        {//is a file, use file logic to display things
          long fsize = file_size(file);
          char* output = file_bytes(file);

          fwrite(&fsize, sizeof(fsize), 1, stdout);
          fwrite(output, sizeof(char), file_size(file), stdout);

          // printf("Size: %ld\n", file_size(file));
          // printf("Bytes: %s\n", file_bytes(file));
          
          // printf("%s is not directory\n", file);
          // printf("%s namesize is: %d\n", file, strlen(file));
          // printf("%s size is: %d\n", file, file_size(file));
          // printf("%s inode # is: %ld\n", file, file_inode(file));
          // printf("%s mode is: %0x\n", file, file_mode(file));
          // printf("%s mod time is: %ld\n", file, file_mod_time(file));
          // printf("%s bytes are: %s\n", file, file_bytes(file));

        }
      }
    }
  }
  closedir(d);
}

int main(int argc, char *argv[])
{
  //char* test = "/home/cs360/lab/lab5/directory";
  //printf("test: %s", dir_name(test));
  
  
  //need function to pull dir name only
  char* pathname = strdup(argv[1]);
  char* parentdir = NULL;
  parentdir = dir_name(argv[1]);
  //printf("pathname :%s\n",pathname);
  //printf("parentdir :%s\n",parentdir);

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



  //printf("Namesize: %d\n", (int)strlen(parentdir));
  // printf("Name: %s\n", argv[1]);
  // printf("Inode: %ld\n", file_inode(argv[1]));
  // printf("Mode: %d\n", file_mode(argv[1]));
  // printf("Modification time: %ld\n", file_mod_time(argv[1]));
  // printf("\n");

  traverse(pathname);

  return 0;
}