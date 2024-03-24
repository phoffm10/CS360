//Peter Hoffman
//Lab 6 CS360

#include <sys/stat.h>
//#include <sys/time.h>
#include <utime.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

/*
4 byte int filename size
filename
8 byte long inode
----if first time seen
4 byte mode
8 byte mod time
----if file
8 bytes long file size
file bytes
*/
typedef struct Element{
    char* key;
    char* name;
    char* bytes;
    int namesize;
    long inode;
    int mode;
    long modtime;
    long filesize;
    int num_children;
    bool processed;
    struct Element *parent;
    struct Element **children;
} Element;

void null_set(Element *e);
bool is_dir(Element *e);
bool is_parent_dir(char* path, char* dir);
void insert_element(Element *e, JRB tree);
bool direct_child(char* parent, char* child);
Element* element_return(char* key, JRB tree);
void add_child(Element *parent, Element *child);
void link_elements(JRB tree, Dllist dirs);
void print(Element *e);
void print_jrb(JRB tree);
void create_dirs(Dllist dirs, JRB tree);
void create_files(JRB tree);
bool hard_link(Element *e, JRB tree);
void create_modtimes(JRB tree);
void create_modes(JRB tree);

void null_set(Element *e){
    e->name = NULL;
    e->parent = NULL;
    e->children = NULL;
    e->bytes = NULL;
    e->namesize = -1;
    e->inode = -1;
    e->mode = -1;
    e->modtime = -1;
    e->filesize = -1;
    e->num_children = 0;
    e->processed = false;
}

bool is_dir(Element *e){
    //return (e->mode & 0x4000) != 0;
    if (S_ISDIR(e->mode)){
        return true;
    }
    return false;
}

bool is_parent_dir(char* path, char* dir){
    //char* dir_name;

    //Finds string within a string
    char* dir_position = strstr(path, dir);
    if (dir_position == NULL){
        // If string not found
        return false;
    }
    return true;

    // //Calculate the length of the substring
    // int dir_namesize = (int)strlen(dir_position);

    // //Allocate memory for the substring
    // dir_name = (char*)malloc(dir_namesize + 1);

    // //Copy the substring
    // strcpy(dir_name, dir_position);

    // return dir_name;
}

void insert_element(Element *e, JRB tree){
    e->key = strdup(e->name);
    jrb_insert_str(tree, e->key, new_jval_v((void *) e));
}

bool direct_child(char* parent, char* child){
    int start = strlen(parent);
    int end = strlen(child);
    int slashes = 0;
    for(int i = start; i < end; i++){
        if (child[i] == '/'){
            slashes++;
        }
    }
    if(slashes == 1){
        //printf("%d\n", slashes);
        return true;
    }
    //printf("%d\n", slashes);
    return false;
}

Element* element_return(char* key, JRB tree){
    JRB tmp = jrb_find_str(tree, key);
    if(tmp == NULL){
        return NULL;
    }
    return tmp->val.v;
}

void add_child(Element *parent, Element *child){
    parent->children = realloc(parent->children, (parent->num_children + 1) * sizeof(Element*));
    if (parent->children == NULL) {
        fprintf(stderr, "realloc failed\n");
        exit(1);
    }
    parent->children[parent->num_children] = child;
    child->parent = parent;
    parent->num_children++;
}

void link_elements(JRB tree, Dllist dirs){
    JRB jtmp;
    Dllist dtmp;
    //contains dir and one /
    dll_traverse(dtmp, dirs){
        Element *d = element_return(dtmp->val.s, tree);
        jrb_traverse(jtmp, tree){
            Element *e = jtmp->val.v;
            if(is_parent_dir(e->key, dtmp->val.s)){
                if(direct_child(dtmp->val.s, e->key)){
                    add_child(d,e);

                    // printf("----------\n");
                    // printf("parent: %s\n", e->parent->name);
                    // for(int i = 0; i < d->num_children; i++){
                    //     printf("child: %s\n", d->children[i]->name);
                    // }
                    // printf("----------\n");
                    
                }
            }
        }
    }
}

void print(Element *e){
    if(e->namesize != -1){
        printf("namesize: %d\n", e->namesize);
    }
    fflush(stdout);
    if(e->name != NULL){
        printf("name: %s\n", e->name);
    }
    fflush(stdout);
    //parent
    if(e->parent != NULL){
        printf("parent: %s\n", e->parent->name);
    }
    //children
    printf("children:\n");
    for(int i = 0; i < e->num_children; i++){
        printf("    %s\n", e->children[i]->name);
    }
    if(e->inode != -1){
        printf("inode: %ld\n", e->inode);
    }
    fflush(stdout);
    if(e->mode != -1){
        printf("mode: %o\n", e->mode);
    }
    fflush(stdout);
    if(e->modtime != -1){
        printf("modtime: %ld\n", e->modtime);
    }
    fflush(stdout);
    if(e->filesize != -1){
        printf("filesize: %ld\n", e->filesize);
    }
    fflush(stdout);
    if(e->bytes != NULL){
        printf("bytes: %s\n", e->bytes);
    }
    fflush(stdout);
    printf("\n");
}

void print_jrb(JRB tree){
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;
        printf("key: %s\n", e->key);
        print(e);
    }
}
//----------------------------------------------------------------------------------------
void create_dirs(Dllist dirs, JRB tree){
    Dllist tmp;
    dll_traverse(tmp, dirs){
        mkdir(tmp->val.s, 0777);
        Element *e = element_return(tmp->val.s, tree);
        e->processed = true;
        //printf("made dir :%s\n", tmp->val.s);
    }
}

void create_files(JRB tree){
    Dllist files;
    files = new_dllist();
    JRB tmp, tmp2;

    //traverse and call fwrite
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;    
        if(e->bytes != NULL){
            FILE *file = fopen(e->name, "wb");
            //e->processed = true;
            if(file != NULL && e->bytes != NULL && e->filesize > 0){
                fwrite(e->bytes, sizeof(char), e->filesize, file);
                e->processed = true;
            //printf("made file :%s\n", e->name);
                fclose(file);
            }
        //fclose(file);
        }
        // jrb_traverse(tmp2, tree){
        //     Element* temp = (Element* )tmp2->val.v;
        //     hard_link(temp, tree);
        // }        
    }
    jrb_traverse(tmp2, tree){
        Element* temp = (Element* )tmp2->val.v;
        hard_link(temp, tree);
    }
}

bool hard_link(Element *e, JRB tree){
    //this may or may not work
    //check e->inode against all other inodes
    //if name is not the same, and inode is, hardlink
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element* d = (Element* )tmp->val.v;
        if(strcmp(e->name, d->name)!= 0){
            if(e->inode == d->inode){
                if(e->bytes == NULL && d->bytes != NULL){
                    //link
                    link(d->name, e->name);
                    e->modtime = d->modtime;
                    e->mode = d->mode;
                    e->processed = true;
                    // printf("LINK CREATED -----------\n");
                    // printf("original :%s\n", d->name);
                    // printf("new :%s\n", e->name);
                    // printf("------------------------\n");
                    return true;
                }
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------
void final_check(JRB tree){
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element *e = (Element* )tmp->val.v;
        if(e->processed == false){
            //printf("final pass: %s\n", e->name);
            if(e->bytes != NULL){
                FILE *file = fopen(e->name, "wb");
                //e->processed = true;
                if(file != NULL && e->bytes != NULL && e->filesize > 0){
                    fwrite(e->bytes, sizeof(char), e->filesize, file);
                    e->processed = true;
                    //printf("made file :%s\n", e->name);
                    fclose(file);
                }
            }
            else if(is_dir(e)){
                mkdir(e->name, 0777);
                e->processed = true;
            }
            else{
                hard_link(e, tree);
            }
        }
    }
}

void create_modtimes(JRB tree){
    JRB tmp;
    struct utimbuf t;
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;
        t.modtime = e->modtime;
        utime(e->name, &t);
    }
}

void create_modes(JRB tree){
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;
        chmod(e->name, e->mode);
    }
}

int main(int argc, char* argv[]){
    Dllist inodes;
    Dllist dirs;
    Dllist tmp, tmp2;
    JRB tree;

    tree = make_jrb();
    dirs = new_dllist();
    inodes = new_dllist();
    bool seen = false;

    while(1){
        seen = false;
        Element *e = malloc(sizeof(Element));
        null_set(e);
        //file namesize
        int bytes_read = (int)fread(&e->namesize, sizeof(int), 1, stdin);
        if(bytes_read == 0){
            break;
        }
        //printf("namesize: %d\n", e->namesize);
        //filename
        bytes_read = 0;
        e->name = (char*)malloc((sizeof(char)*e->namesize)+1);
        bytes_read = (int)fread(e->name, sizeof(char), e->namesize, stdin);
        // if(bytes_read != e->namesize){
        //     fprintf(stderr, "Bad tarfile\n");
        //     exit(1);
        // }
        e->name[e->namesize] = '\0';
        //printf("name: %s\n", e->name);
        //inode
        bytes_read = 0;
        bytes_read = (int)fread(&e->inode, sizeof(long), 1, stdin);
        // if(bytes_read != sizeof(long)){
        //     fprintf(stderr, "Bad tarfile\n");
        //     exit(1);
        // }
        //printf("inode: %ld\n", e->inode);
        //add inode to list and check if already on list
        dll_traverse(tmp, inodes){
            if(e->inode == tmp->val.l){
            seen = true;
            }
        }
        if (!seen){
            //Append inode if file not seen
            dll_append(inodes, new_jval_l(e->inode));
        }

        if(!seen){
            bytes_read = 0;
            bytes_read = fread(&e->mode, sizeof(int), 1, stdin);
            // if(bytes_read != sizeof(int)){
            //     fprintf(stderr, "Bad tarfile\n");
            //     exit(1);
            // }   
            //printf("mode: %d\n", e->mode);
            bytes_read = 0;
            bytes_read = fread(&e->modtime, sizeof(long), 1, stdin);
            // if(bytes_read != sizeof(long)){
            //     fprintf(stderr, "Bad tarfile\n");
            //     exit(1);
            // }
            //printf("modtime: %ld\n", e->modtime);

            if(is_dir(e) == false){
                //printf("notdir\n");
                fflush(stdout);
                bytes_read = 0;
                bytes_read = fread(&e->filesize, sizeof(long), 1, stdin);
                // if(bytes_read != sizeof(long)){
                //     fprintf(stderr, "Bad tarfile\n");
                //     exit(1);
                // }

                e->bytes = (char*)malloc((sizeof(char)*e->filesize)+1);
                // bytes_read = 0;
                fread(e->bytes, sizeof(char), e->filesize, stdin);
                // if(bytes_read != e->filesize){
                //     fprintf(stderr, "Bad tarfile\n");
                //     exit(1);
                // }
                e->bytes[e->filesize] = '\0';
            }
            else{
                dll_append(dirs, new_jval_s(strdup(e->name)));
            }
        }
        insert_element(e, tree);
        //this prints each element as its read
        //print(e);
    }
    //prints tree
    // printf("--------------------\n");
    // print_jrb(tree);
    // printf("--------------------\n");
    //prints list of directories
    // printf("dirs\n");
    // dll_traverse(tmp2, dirs){
    //     printf("%s\n", tmp2->val.s);
    // }
    //------------------------
    // printf("child testing\n");
    // char* t1 = "dir";
    // char* t2 = "dir/sub";
    // char* t3 = "dir/t1";
    // char* t4 = "dir/sub/t1";
    // if(direct_child(t1, t4)){
    //     printf("is child\n");
    // }
    // else{
    //     printf("not child");
    // }
    //------------------------
    //printf("link testing\n");
    link_elements(tree, dirs);
    print_jrb(tree);

    create_dirs(dirs, tree);
    create_files(tree);
    final_check(tree);
    create_modtimes(tree);
    create_modes(tree);

    return 0;
}