//Peter Hoffman
//CS360 Lab 2

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"


// ./bin/famtree < fam1.txt
typedef struct Person{
    char* key;
    char* name;
    char* sex;
    struct Person *father;
    struct Person *mother;
    struct Person *father_of;
    struct Person *mother_of;
    bool visited;
} Person;

//Person *person;

void print_person(Person *p){
        printf("Name: %s\n", p->name);
        printf("  Sex: %s\n", p->sex);
        printf("  Father: %s\n", p->father ? p->father->name : "Unknown");
        printf("  Mother: %s\n", p->mother ? p->mother->name : "Unknown");
        printf("  Father of: %s\n", p->father_of ? p->father_of->name : "Unknown");
        printf("  Mother of: %s\n", p->mother_of ? p->mother_of->name : "Unknown");
        printf("  Children: ");
        if(p->father_of == NULL && p->mother_of == NULL){
            printf("None\n");
        }
        if (p->father_of != NULL){
            printf("\n    %s\n", p->father_of->name);
        }
        if (p->mother_of != NULL){
            printf("\n    %s\n", p->mother_of->name);
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
                //this is where i need to input data into JRB tree
                if (p != NULL) {
                    print_person(p);
                }

                //new person every time "PERSON" shows up
                p = malloc(sizeof(Person));

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
                p->sex = strdup("M");
                if (i + 1 < is->NF) {
                    p->father_of = malloc(sizeof(Person));
                    p->father_of->name = strdup(is->fields[i + 1]);
                }
            }
            //stores mother of in person 
            else if (strcmp(temp, "MOTHER_OF") == 0) {
                //assumes female if mother of
                p->sex = strdup("F");
                if (i + 1 < is->NF) {
                    p->mother_of = malloc(sizeof(Person));
                    p->mother_of->name = strdup(is->fields[i + 1]);
                }
            }
            //stores sex in person 
            else if (strcmp(temp, "SEX") == 0) {
                if (i + 1 < is->NF) {
                    p->sex = strdup(is->fields[i + 1]);
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