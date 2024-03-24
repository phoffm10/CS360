//Peter Hoffman
//Lab 6 CS360

#include <sys/stat.h>
//#include <sys/time.h>
#include <utime.h>
#include <time.h>
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
    //bool processed;
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
void hard_link(Element *e, JRB tree);
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
}

bool is_dir(Element *e){
    if (S_ISDIR(e->mode)){
        return true;
    }
    return false;
}

bool is_parent_dir(char* path, char* dir){
    //Finds string within a string
    char* dir_position = strstr(path, dir);
    if (dir_position == NULL){
        // If string not found
        return false;
    }
    return true;
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
        return true;
    }
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
                }
            }
        }
    }
}

void print(Element *e){
    if(e->namesize != -1){
        printf("Namesize: \t%d\n", e->namesize);
    }
    fflush(stdout);
    if(e->name != NULL){
        printf("Name: \t\t%s\n", e->name);
    }
    fflush(stdout);
    //parent
    if(e->parent != NULL){
        printf("Parent: \t%s\n", e->parent->name);
    }
    //children
    if(e->num_children == 0){
        printf("Children: \tNone\n");
    }
    else{
        printf("Children:\n");

        for(int i = 0; i < e->num_children; i++){
            printf("\t\t\t%s\n", e->children[i]->name);
        }
    }
    if(e->inode != -1){
        printf("Inode: \t\t%ld\n", e->inode);
    }
    fflush(stdout);
    if(e->mode != -1){
        printf("Mode: \t\t%o\n", e->mode);
    }
    fflush(stdout);
    if(e->modtime != -1){
        printf("Modtime: \t%ld\n", e->modtime);
    }
    fflush(stdout);
    if(e->filesize != -1){
        printf("Filesize: \t%ld\n", e->filesize);
    }
    fflush(stdout);
    if(e->bytes != NULL){
        printf("Bytes: \t\t%s\n", e->bytes);
    }
    fflush(stdout);
    printf("\n");
}

void print_jrb(JRB tree){
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;
        printf("Key: \t\t%s\n", e->key);
        print(e);
    }
}

void create_dirs(Dllist dirs, JRB tree){
    Dllist tmp;
    dll_traverse(tmp, dirs){
        mkdir(tmp->val.s, 0777);
        Element *e = element_return(tmp->val.s, tree);
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
            if(file != NULL && e->bytes != NULL && e->filesize > 0){
                fwrite(e->bytes, sizeof(char), e->filesize, file);
                fclose(file);
            }
        }      
    }
    jrb_traverse(tmp2, tree){
        Element* temp = (Element* )tmp2->val.v;
        hard_link(temp, tree);
    }
}

void hard_link(Element *e, JRB tree){
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
                }
            }
        }
    }
}

void create_modtimes(JRB tree){
    JRB tmp;
    struct utimbuf t;
    time_t current_time;
    time(&current_time);
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;
        t.actime = current_time;
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
        int bytes_read = (int)fread(&e->namesize, sizeof(char), 4, stdin);
        if (bytes_read == 0) {
            if (feof(stdin)) {
                break;
            } else {
                fprintf(stderr, "Bad tarfile.\n");
                exit(1);
            }
        }

        e->name = (char*)malloc((sizeof(char)*e->namesize)+1);
        bytes_read = (int)fread(e->name, sizeof(char), e->namesize, stdin);
        if(bytes_read != e->namesize){
            fprintf(stderr, "Bad tarfile\n");
            exit(1);
        }
        e->name[e->namesize] = '\0';

        bytes_read = (int)fread(&e->inode, sizeof(long), 1, stdin);
        if(bytes_read == 0){
            fprintf(stderr, "Bad tarfile\n");
            exit(1);
        }

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
            bytes_read = fread(&e->mode, sizeof(int), 1, stdin);
            if(bytes_read == 0){
                fprintf(stderr, "Bad tarfile\n");
                exit(1);
            }   

            bytes_read = fread(&e->modtime, sizeof(long), 1, stdin);
            if(bytes_read == 0){
                fprintf(stderr, "Bad tarfile\n");
                exit(1);
            }

            if(is_dir(e) == false){

                bytes_read = fread(&e->filesize, sizeof(long), 1, stdin);
                if(bytes_read == 0){
                    fprintf(stderr, "Bad tarfile\n");
                    exit(1);
                }

                e->bytes = (char*)malloc((sizeof(char)*e->filesize)+1);
                bytes_read = fread(e->bytes, sizeof(char), e->filesize, stdin);
                if(bytes_read != e->filesize){
                    fprintf(stderr, "Bad tarfile\n");
                    exit(1);
                }
                e->bytes[e->filesize] = '\0';
            }
            else{
                dll_append(dirs, new_jval_s(strdup(e->name)));
            }
        }
        insert_element(e, tree);
    }

    link_elements(tree, dirs);
    print_jrb(tree);

    create_dirs(dirs, tree);
    create_files(tree);
    create_modtimes(tree);
    create_modes(tree);

    return 0;
}