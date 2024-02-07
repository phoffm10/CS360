//Peter Hoffman
//CS360 Lab 2

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

/*
TODO
-how do i input data into JRB trees?
-What should I do with JRB once its loaded
-How to read in multiple words for name
*/



// ./bin/famtree < fam1.txt
typedef struct Person{
    char* key;
    char* name;
    char* sex;
    struct Person* father;
    struct Person* mother;
//    struct Person* father_of;//these should be lists of Person structs
//    struct Person* mother_of;
    struct Person** children;
    int num_children;
    int max_children;
    bool visited;
} Person;

//Person *person;

void print_person(Person *p){
    printf("%s\n", p->name);
    printf("  Sex: %s\n", p->sex);
    printf("  Father: %s\n", p->father ? p->father->name : "Unknown");
    printf("  Mother: %s\n", p->mother ? p->mother->name : "Unknown");
    printf("  Children: ");
    if(p->num_children == 0){
        printf("None\n");
    }
    for (int j = 0; j < p->num_children; j++) {
        if(j == 0){
            printf("\n");
        }
        printf("    %s\n", p->children[j]->name);
    }
    printf("\n");  
}

int main(int argc, char *argv[]) {
    JRB t, tmp;
    IS is;
    Person *p = NULL;   //used to check if person needs to be printed
    int nsize, i;
    char* temp;

    is = new_inputstruct(NULL);
    t = make_jrb();

    while (get_line(is) >= 0) {
        for (i = 0; i < is->NF; i++) {
            nsize = strlen(is->fields[i]);
            temp = malloc(sizeof(char) * (nsize + 1));
            strcpy(temp, is->fields[i]);

            if (strcmp(temp, "PERSON") == 0) {
                //if there was a previous person, print person
                if (p != NULL) {
                    //this is where i need to input data into JRB tree
                    print_person(p);
                }

                //new person every time "PERSON" shows up
                p = malloc(sizeof(Person));

                p->num_children = 0;
                p->max_children = 10;
                p->children = malloc(p->max_children * sizeof(Person*));
                
                //stores name of the new person
                if (i + 1 < is->NF) {
                    p->name = strdup(is->fields[i + 1]);
                }
            } 
            //if line does not start with "PERSON", checks other keywords
            //stores father of person
            else if (strcmp(temp, "FATHER") == 0) {
                if (i + 1 < is->NF) {
                    p->father = malloc(sizeof(Person));
                    p->father->name = strdup(is->fields[i + 1]);
                }
            }
            //stores mother of person
            else if (strcmp(temp, "MOTHER") == 0) {
                if (i + 1 < is->NF) {
                    p->mother = malloc(sizeof(Person));
                    p->mother->name = strdup(is->fields[i + 1]);
                }
            }
            //stores father of in person 
            else if (strcmp(temp, "FATHER_OF") == 0) {
                //assumes male if father of
                p->sex = strdup("Male");
                if (i + 1 < is->NF) {
                    if (p->num_children >= p->max_children) {
                        //resize children array if necessary
                        p->max_children *= 2;
                        Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));

                        p->children = new_child;
                    }
                    p->children[p->num_children] = malloc(sizeof(Person));
                    p->children[p->num_children]->name = strdup(is->fields[i + 1]);
                    p->num_children++;
                }
            }
            //stores mother of in person 
            else if (strcmp(temp, "MOTHER_OF") == 0) {
                //assumes female if mother of
                p->sex = strdup("Female");
                if (i + 1 < is->NF) {
                    if (p->num_children >= p->max_children) {
                        //resize children array if necessary
                        p->max_children *= 2;
                        Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));

                        p->children = new_child;
                    }
                    p->children[p->num_children] = malloc(sizeof(Person));
                    p->children[p->num_children]->name = strdup(is->fields[i + 1]);
                    p->num_children++;
                }
            }
            //stores sex in person 
            else if (strcmp(temp, "SEX") == 0) {
                if (i + 1 < is->NF) {
                    if (strcmp(is->fields[i + 1],"M")){
                        p->sex = strdup("Female");
                    }
                    else{
                        p->sex = strdup("Male");
                    }
                }
            }
        }
    }
    
    // prints last person
    //this is where i need to input data into JRB tree
    if (p != NULL) {
        print_person(p);
    }

    jettison_inputstruct(is);
    return 0;
}