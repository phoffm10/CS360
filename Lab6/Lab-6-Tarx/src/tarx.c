//Peter Hoffman
//Lab 6 CS360

#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
    struct Element *parent;
    struct Element **children;
} Element;

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
    return e->mode == 0x000041ed;
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
        printf("mode: %ld\n", e->mode);
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
        //filename
        e->name = (char*)malloc((sizeof(char)*e->namesize)+1);
        fread(e->name, sizeof(char), e->namesize, stdin);
        e->name[e->namesize] = '\0';
        //inode
        fread(&e->inode, sizeof(long), 1, stdin);
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
            fread(&e->mode, sizeof(int), 1, stdin);
            fread(&e->modtime, sizeof(long), 1, stdin);

            if(is_dir(e) == false){
                fread(&e->filesize, sizeof(long), 1, stdin);

                e->bytes = (char*)malloc((sizeof(char)*e->filesize)+1);
                fread(e->bytes, sizeof(char), e->filesize, stdin);
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

    return 0;
}