//Peter Hoffman
//Lab 6 CS360

#include <sys/stat.h>
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

//Struct to hold directories and files
typedef struct Element{
    char* key;
    char* name;
    char* bytes;
    int namesize;
    long inode;
    int mode;
    long modtime;
    long filesize;
} Element;

//Forward declarations
void null_set(Element *e);
bool is_dir(Element *e);
void insert_element(Element *e, JRB tree);
Element* element_return(char* key, JRB tree);
void print(Element *e);
void print_jrb(JRB tree);
void create_dirs(Dllist dirs, JRB tree);
void create_files(JRB tree);
void hard_link(Element *e, JRB tree);
void create_modtimes(JRB tree);
void create_modes(JRB tree);
void parse_input(JRB tree, Dllist dirs, Dllist inodes);
void free_mem(JRB tree, Dllist dirs, Dllist inodes);

void null_set(Element *e){
    //Initializes element struct
    e->name = NULL;
    e->bytes = NULL;
    e->namesize = -1;
    e->inode = -1;
    e->mode = -1;
    e->modtime = -1;
    e->filesize = -1;
}

bool is_dir(Element *e){
    //Checks if element is a directory
    if (S_ISDIR(e->mode)){
        return true;
    }
    return false;
}

void insert_element(Element *e, JRB tree){
    //Inserts element struct into tree
    e->key = strdup(e->name);
    jrb_insert_str(tree, e->key, new_jval_v((void *) e));
}

Element* element_return(char* key, JRB tree){
    //Searches JRB and returns element
    JRB tmp = jrb_find_str(tree, key);
    if(tmp == NULL){
        return NULL;
    }
    return tmp->val.v;
}

void print(Element *e){
    //Prints element struct
    if(e->namesize != -1){
        printf("Namesize: \t%d\n", e->namesize);
    }
    fflush(stdout);
    if(e->name != NULL){
        printf("Name: \t\t%s\n", e->name);
    }
    fflush(stdout);
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
    //Prints JRB elements
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;
        printf("Key: \t\t%s\n", e->key);
        print(e);
    }
}

void create_dirs(Dllist dirs, JRB tree){
    //Traverse directory list and creates directories
    Dllist tmp;
    dll_traverse(tmp, dirs){
        mkdir(tmp->val.s, 0777);
        Element *e = element_return(tmp->val.s, tree);
    }
}

void create_files(JRB tree){
    JRB tmp, tmp2;

    //Traverse tree and call fwrite if file has bytes
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
    //Traverses and links necessary files
    jrb_traverse(tmp2, tree){
        Element* temp = (Element* )tmp2->val.v;
        hard_link(temp, tree);
    }
}

void hard_link(Element *e, JRB tree){
    //Checks elements inodes against all other inodes
    //If name is not the same, and inode is, hardlink
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element* d = (Element* )tmp->val.v;
        if(strcmp(e->name, d->name)!= 0){
            if(e->inode == d->inode){
                if(e->bytes == NULL && d->bytes != NULL){
                    link(d->name, e->name);
                    e->modtime = d->modtime;
                    e->mode = d->mode;
                }
            }
        }
    }
}

void create_modtimes(JRB tree){
    //Sets file modtimes
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
    //Sets file modes
    JRB tmp;
    jrb_traverse(tmp, tree){
        Element* e = (Element* )tmp->val.v;
        chmod(e->name, e->mode);
    }
}

void parse_input(JRB tree, Dllist dirs, Dllist inodes){
    bool seen = false;
    Dllist tmp;

    while(1){
        seen = false;
        Element *e = malloc(sizeof(Element));
        //Initializes element struct
        null_set(e);

        //Stores namesize, errors out if not 4 bytes
        int bytes_read = (int)fread(&e->namesize, sizeof(char), 4, stdin);
        if (bytes_read == 0) {
            if (feof(stdin)) {
                free(e);
                break;
            } else {
                fprintf(stderr, "Bad tarfile.\n");
                free(e);
                exit(1);
            }
        }

        //Stores name
        e->name = (char*)malloc((sizeof(char)*e->namesize)+1);
        bytes_read = (int)fread(e->name, sizeof(char), e->namesize, stdin);
        if(bytes_read != e->namesize){
            fprintf(stderr, "Bad tarfile\n");
            exit(1);
        }
        e->name[e->namesize] = '\0';

        //Stores inode
        bytes_read = (int)fread(&e->inode, sizeof(long), 1, stdin);
        if(bytes_read == 0){
            fprintf(stderr, "Bad tarfile\n");
            exit(1);
        }

        //Adds inode to list and checks if already on list
        dll_traverse(tmp, inodes){
            if(e->inode == tmp->val.l){
            seen = true;
            }
        }
        if (!seen){
            //Append inode if element not seen
            dll_append(inodes, new_jval_l(e->inode));
        }

        if(!seen){
            //Stores mode
            bytes_read = fread(&e->mode, sizeof(int), 1, stdin);
            if(bytes_read == 0){
                fprintf(stderr, "Bad tarfile\n");
                exit(1);
            }   

            //Stores modtime
            bytes_read = fread(&e->modtime, sizeof(long), 1, stdin);
            if(bytes_read == 0){
                fprintf(stderr, "Bad tarfile\n");
                exit(1);
            }

            if(is_dir(e) == false){
                
                //Stores filesize
                bytes_read = fread(&e->filesize, sizeof(long), 1, stdin);
                if(bytes_read == 0){
                    fprintf(stderr, "Bad tarfile\n");
                    exit(1);
                }

                //Stores file bytes
                e->bytes = (char*)malloc((sizeof(char)*e->filesize)+1);
                bytes_read = fread(e->bytes, sizeof(char), e->filesize, stdin);
                if(bytes_read != e->filesize){
                    fprintf(stderr, "Bad tarfile\n");
                    exit(1);
                }
                e->bytes[e->filesize] = '\0';
            }
            else{
                //Stores directory names
                dll_append(dirs, new_jval_s(strdup(e->name)));
            }
        }
        //Inserts element struct into JRB
        insert_element(e, tree);
    }
}

void free_mem(JRB tree, Dllist dirs, Dllist inodes){
    //Frees allocated memory
    JRB jtmp;
    Dllist tmp;
    jrb_traverse(jtmp, tree){
        Element* e = (Element* )jtmp->val.v;
        if(e->key != NULL){
            free(e->key);
        }
        if(e->name != NULL){
            free(e->name);
        }
        if(e->bytes != NULL){
            free(e->bytes);
        }
        free(e);
    }
    jrb_free_tree(tree);

    dll_traverse(tmp, dirs){
        free(tmp->val.s);
    }
    free_dllist(dirs);
    free_dllist(inodes);
}

int main(int argc, char* argv[]){
    Dllist inodes;
    Dllist dirs;
    JRB tree;

    tree = make_jrb();
    dirs = new_dllist();
    inodes = new_dllist();

    //Reads tarc file and creates element structs
    parse_input(tree, dirs, inodes);
    
    //Prints elements to stdout
    print_jrb(tree);

    //Creating directories
    create_dirs(dirs, tree);
    create_files(tree);
    create_modtimes(tree);
    create_modes(tree);

    //Freeing memory
    free_mem(tree, dirs, inodes);

    return 0;
}