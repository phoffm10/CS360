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
-What should I do with JRB once its loaded(how do i find the top of the tree and print in order)
-how do i merge/not create new people if perosn struct already created? (check p->name against keys)
-need to imply children with father and mother keywords
*/

typedef struct Person{
    char* key;
    char* name;
    char* sex;
    char* _father;
    char* _mother;
    struct Person* father;
    struct Person* mother;
//    struct Person* father_of;//these should be lists of Person structs
//    struct Person* mother_of;
    struct Person** children;
    int num_children;
    int max_children;
    bool visited;
} Person;

void print_person(Person* p, JRB tree, JRB tmp){
   printf("-----------------------\n");
    jrb_traverse(tmp, tree) {
        p = (Person *) tmp->val.v;
        printf("%s\n", p->name);
        printf("  Sex: %s\n", p->sex ? p->sex : "Unknown");
        //printf("  Father: %s\n",p->father->name);
        printf("  Father: %s\n", p->father!=NULL ? p->father->name : "Unknown");
        printf("  Mother: %s\n", p->mother!=NULL ? p->mother->name : "Unknown");
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
    printf("-----------------------\n");
}

void update_parents(JRB tree, JRB tmp){


}


//returns person* if found and new person if not
Person* get_person(Person* p, JRB tree, char* name){
    JRB tmp = jrb_find_str(tree, p->name);
    if (tmp == NULL) {
    //create new key from name if key not found
        p->key = strdup(p->name);
        p->mother = NULL;
        p->father = NULL;
        p->sex = NULL;
        //p->num_children = 0;
        //p->max_children = 10;
        //p->children = malloc(p->max_children * sizeof(Person*));
        jrb_insert_str(tree, p->key, new_jval_v((void *) p));
        return p;
    }
    else{
        // return p;
        return tmp->val.v;
    }
}

int main(int argc, char *argv[]) {
    JRB tree, tmp;
    IS is;
    Person *p = NULL;   //used to check if person needs to be printed
    int nsize, i;
    char* temp;

    is = new_inputstruct(NULL);
    tree = make_jrb();

    while (get_line(is) >= 0) {
        nsize = strlen(is->fields[0]);
        temp = malloc(sizeof(char) * (nsize + 1));
        strcpy(temp, is->fields[0]);

        char name[1000] = {0};
        strcpy(name, "");
        
        if (is->NF < 2) {
            //printf("No input\n");
            continue;
        } /*else {
            printf("Line: %s\n", is->text1);
        }*/

        if (strcmp(temp, "PERSON") == 0) {              
            
            //print_person(p, tree, tmp);
            //new person every time "PERSON" shows up
            p = malloc(sizeof(Person));

            p->num_children = 0;
            p->max_children = 10;
            p->children = malloc(p->max_children * sizeof(Person*));
            
            //stores name of the name of the person
            // p->name = strdup(is->fields[1]);         
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                // name[nsize] = ' ';
                // strcpy(name+nsize+1, is->fields[i+1]);
                // nsize += strlen(name+nsize);
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);

                //strcat(p->name," ");
                //strcat(p->name, is->fields[i+1]);
            }
            p->name = strdup(name);

            //if person exists, return person*, if not create a new person* with read name
            p = get_person(p, tree, p->name);
            p->num_children = 0;
            p->max_children = 10;
            p->children = malloc(p->max_children * sizeof(Person*));
            
        } 

        //if line does not start with "PERSON", checks other keywords
        //stores father of person
        else if (strcmp(temp, "FATHER") == 0) {
            //need to check if father name is already a key-----------------
            p->father = malloc(sizeof(Person));
            // p->father->name = strdup(is->fields[i + 1]);
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }
            p->father->name = strdup(name);
            
            p->father = get_person(p->father, tree, p->father->name);
            p->num_children = 0;
            p->max_children = 10;
            
            p->children = malloc(p->max_children * sizeof(Person*));
            p->father = get_person(p->father, tree, p->father->name);
            //sets fathers sex as male
            p->father->sex = strdup("Male");
            jrb_delete_node(jrb_find_str(tree, p->father->name));
            jrb_insert_str(tree, p->father->name, new_jval_v((void *) p->father));
        }
        //stores mother of person
        else if (strcmp(temp, "MOTHER") == 0) {
            //need to check if mother name is already a key--------------------
            p->mother = malloc(sizeof(Person));
            // p->mother->name = strdup(is->fields[i + 1]);
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }
            p->mother->name = strdup(name);
            p->mother = get_person(p->mother, tree, p->mother->name);
            
            p->num_children = 0;
            p->max_children = 10;
            p->children = malloc(p->max_children * sizeof(Person*));
            
            //sets mothers sex as female
            //--------
            
            //p->mother->children[p->num_children] = malloc(sizeof(Person));
            //p->mother->children[p->num_children]->name = p->name;
            //p->mother->num_children++;
            //----------
            p->mother->sex = strdup("Female");
            jrb_delete_node(jrb_find_str(tree, p->mother->name));
            jrb_insert_str(tree, p->mother->name, new_jval_v((void *) p->mother));
        }
        //stores father of in person 
        else if (strcmp(temp, "FATHER_OF") == 0) {
            //assumes male if father of
            p->sex = strdup("Male");
            //need to check if child name is already a key--------------------
            if (p->num_children >= p->max_children) {
                //resize children array if necessary
                p->max_children *= 2;
                Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));

                p->children = new_child;
            }
            //this adds name of each child and checks against known people
            p->children[p->num_children] = malloc(sizeof(Person));
            // p->children[p->num_children]->name = strdup(is->fields[i + 1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }
            p->children[p->num_children]->name = strdup(name);
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            p->children[p->num_children]->num_children = 0;
            p->children[p->num_children]->max_children = 10;
            p->children[p->num_children]->children = malloc(p->children[p->num_children]->max_children * sizeof(Person*));
            
            p->children[p->num_children]->father = p;

            jrb_delete_node(jrb_find_str(tree, p->children[p->num_children]->name));
            jrb_insert_str(tree, p->children[p->num_children]->name, new_jval_v((void *) p->children[p->num_children]));

            p->num_children++;
        }
        //stores mother of in person 
        else if (strcmp(temp, "MOTHER_OF") == 0) {
            //assumes female if mother of
            p->sex = strdup("Female");
            //need to check if child name is already a key--------------------
            if (p->num_children >= p->max_children) {
                //resize children array if necessary
                p->max_children *= 2;
                Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));

                p->children = new_child;
            }
            //this adds name of each child and checks against known people
            p->children[p->num_children] = malloc(sizeof(Person));
            // p->children[p->num_children]->name = strdup(is->fields[i + 1]);
            strcpy(name, is->fields[1]);
            
            for (i = 1; i < is->NF-1; i++) {
                // strcat(p->children[p->num_children]->name," ");
                // strcat(p->children[p->num_children]->name, is->fields[i+1]);
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }
            p->children[p->num_children]->name = strdup(name);
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            p->children[p->num_children]->num_children = 0;
            p->children[p->num_children]->max_children = 10;
            p->children[p->num_children]->children = malloc(p->children[p->num_children]->max_children * sizeof(Person*));
            //p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);

            p->children[p->num_children]->mother = p;
            jrb_delete_node(jrb_find_str(tree, p->children[p->num_children]->name));
            jrb_insert_str(tree, p->children[p->num_children]->name, new_jval_v((void *) p->children[p->num_children]));

            p->num_children++;
        }
        else if (strcmp(temp, "SEX") == 0) {
            
            p = get_person(p, tree, p->name);
            if (strcmp(is->fields[1],"M")){
                p->sex = strdup("Female");
            }
            else{
                p->sex = strdup("Male");
            }
            jrb_delete_node(jrb_find_str(tree, p->name));
            jrb_insert_str(tree, p->name, new_jval_v((void *) p));
        }
        //printf("Name: %s\n", name);
      
    }
    update_parents(tree, tmp);
    print_person(p, tree, tmp);

    jettison_inputstruct(is);
    return 0;
}