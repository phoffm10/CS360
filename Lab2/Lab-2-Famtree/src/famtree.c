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
-need to implement topological sort for jrb
*/

typedef struct Person{
    char* key;
    char* name;
    char* sex;
//    char* _father;
//    char* _mother;
    struct Person* father;
    struct Person* mother;
//    struct Person* father_of;//these should be lists of Person structs
//    struct Person* mother_of;
    struct Person** children;
    int num_children;
    int max_children;
    //set val when reading parents in
    int num_parents;
    bool visited;
    bool printed;
} Person;

void print_person(Person* p, JRB tree, JRB tmp){
   printf("-----------------------\n");
    jrb_traverse(tmp, tree) {
        p = (Person *) tmp->val.v;
        //p->printed = true;
        printf("%s\n", p->name);
        printf("  Sex: %s\n", p->sex ? p->sex : "Unknown");
        //printf("  Father: %s\n",p->father->name);
        printf("  Father: %s\n", p->father!=NULL ? p->father->name : "Unknown");
        printf("  Mother: %s\n", p->mother!=NULL ? p->mother->name : "Unknown");
        printf("  Children: ");
        if(p->num_children == 0){
        printf("None\n");
        }

        //printf("%d %p\n", p->num_children, p->children);
        //fflush(stdout);
        for (int j = 0; j < p->num_children; j++) {
            if(j == 0){
                printf("\n");
            }
        
        //printf("%p\n", p->children[j]);
        //fflush(stdout);

        printf("    %s\n", p->children[j]->name);
    }
    printf("num parents: %d\n", p->num_parents);
    printf("visited: %d\n", p->visited);
    printf("printed: %d\n", p->printed);
    printf("\n"); 
    }
    printf("-----------------------\n");
}

void print_dlist(Person* p, Dllist l, Dllist dtmp){
   printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    dll_traverse(dtmp, l) {
        p = (Person *)dtmp->val.v;
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
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}

//returns person* if found and new person if not
Person* get_person(Person* p, JRB tree, char* name){
    JRB tmp = jrb_find_str(tree, p->name);
    if (tmp == NULL) {
    //create new key from name if key not found
        //p = malloc(sizeof(Person));
        p->key = strdup(p->name);
        p->mother = NULL;
        p->father = NULL;
        p->sex = NULL;
        p->num_children = 0;
        p->max_children = 20;
        p->num_parents = 0;
        p->visited = false;
        p->printed = false;
        p->children = malloc(p->max_children * sizeof(Person*));
        jrb_insert_str(tree, p->key, new_jval_v((void *) p));
        return p;
    }
    else{
        // return p;
        return tmp->val.v;
    }
}

void print(Person* p){
    printf("%s\n", p->name);
    printf("  Sex: %s\n", p->sex ? p->sex : "Unknown");
    //printf("  Father: %s\n",p->father->name);
    printf("  Father: %s\n", p->father!=NULL ? p->father->name : "Unknown");
    printf("  Mother: %s\n", p->mother!=NULL ? p->mother->name : "Unknown");
    printf("  Children: ");
    if(p->num_children == 0){
    printf("None\n");
    }
        //printf("%d %p\n", p->num_children, p->children);
        //fflush(stdout);
    for (int j = 0; j < p->num_children; j++) {       
        if(j == 0){
            printf("\n");
        }
        if(j != 0 && !strcmp(p->children[j]->name,p->children[j-1]->name)){
            continue;
        }
        printf("    %s\n", p->children[j]->name);
    }
    printf("\n");
}
//searches for key and reinserts person with same key
void update_node(JRB tree, char* name, Person* p){
    jrb_delete_node(jrb_find_str(tree, name));
    jrb_insert_str(tree, name, new_jval_v((void *) p));
}

bool all_printed(JRB tree){
    JRB tmp;
    jrb_traverse(tmp, tree){
        Person* p = (Person *)tmp->val.v;
        if (p->printed == false){
            return false;
        }
    }
    return true;
}

void topsort(JRB tree){
    JRB tmp;
    while(!all_printed(tree)){
        jrb_traverse(tmp, tree){
            Person* p = (Person*)tmp->val.v;
            if(!p->printed && (p->num_parents == 0)){
                print(p);
                p->printed = true;
                for (int j = 0; j < p->num_children; j++) {      
                    p->children[j]->num_parents--;
                }
            }
        }
        jrb_traverse(tmp, tree){
            Person* p = (Person*)tmp->val.v;
            if(!p->printed){
                print(p);
                p->printed = true;
            }
        }
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
        
        //if no input, continue
        if (is->NF < 2) {
            continue;
        }

        if (strcmp(temp, "PERSON") == 0) {              
            
            //new person every time "PERSON" shows up
            p = malloc(sizeof(Person));

            //stores name of the name of the person       
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //stores read name as persons name
            p->name = strdup(name);

            //if person exists, return person*, if not create a new person* with read name
            p = get_person(p, tree, p->name);
            
        } 

        //if line does not start with "PERSON", checks other keywords
        
        //stores father of person
        else if (strcmp(temp, "FATHER") == 0) {
            //allocates mem for father and reads name
            p->father = malloc(sizeof(Person));
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //stores read name as fathers name
            p->father->name = strdup(name);
            
            //checks if father already exists
            p->father = get_person(p->father, tree, p->father->name);
            p = get_person(p, tree, p->name);

            /*
            if(p->father->num_children == 0){
                int children = p->father->num_children;
                for(int j = 0; j < children; j++){
                    if (strcmp(p->name, p->father->children[j]->name) != 0){
                        p->father->children[p->father->num_children] = malloc(sizeof(Person));
                        p->father->children[p->father->num_children]->name = strdup(p->name);
                        p->father->num_children++;
                        p->num_parents++;
                    }
                }
            }
            else{
                p->father->children[p->father->num_children] = malloc(sizeof(Person));
                p->father->children[p->father->num_children]->name = strdup(p->name);
                p->father->num_children++;
                p->num_parents++;
            }
            */
            //father duplicate error check

            //increments childs mother's number of children and adds childs name
            p->father->children[p->father->num_children] = malloc(sizeof(Person));
            p->father->children[p->father->num_children]->name = strdup(p->name);
            p->father->num_children++;

            //sets fathers sex as male
            p->father->sex = strdup("Male");

            //adds parent to num parents
            p->num_parents++;

            //updates fathers node in tree
            update_node(tree, p->father->name, p->father);
            update_node(tree, p->name, p);
        }
        //stores mother of person
        else if (strcmp(temp, "MOTHER") == 0) {
            //allocates mem for mother and reads name
            p->mother = malloc(sizeof(Person));
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }
            //stores read name as mothers name
            p->mother->name = strdup(name);
            
            //check of mother already exists
            p->mother = get_person(p->mother, tree, p->mother->name);
            p = get_person(p, tree, p->name);

            /*
            if(p->mother->num_children == 0){
                int children = p->mother->num_children;
                for(int j = 0; j < children; j++){
                    if (strcmp(p->name, p->mother->children[j]->name) != 0){
                        p->mother->children[p->mother->num_children] = malloc(sizeof(Person));
                        p->mother->children[p->mother->num_children]->name = strdup(p->name);
                        p->mother->num_children++;
                        p->num_parents++;
                    }
                }
            }
            else{
                p->mother->children[p->mother->num_children] = malloc(sizeof(Person));
                p->mother->children[p->mother->num_children]->name = strdup(p->name);
                p->mother->num_children++;
                p->num_parents++;
            }
            */

            //increments childs mother's number of children and adds childs name
            p->mother->children[p->mother->num_children] = malloc(sizeof(Person));
            p->mother->children[p->mother->num_children]->name = strdup(p->name);
            p->mother->num_children++;
            p->num_parents++;


            //sets mothers sex as female            
            p->mother->sex = strdup("Female");

            //updates mothers node in tree
            update_node(tree, p->mother->name, p->mother);
            update_node(tree, p->name, p);

        }
        //stores father of in person 
        else if (strcmp(temp, "FATHER_OF") == 0) {
            //assumes male if father of
            p->sex = strdup("Male");
            
            //resize children array if necessary
            if (p->num_children >= p->max_children) {
                p->max_children *= 2;
                Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));
                p->children = new_child;
            }

            //allocates mem for child and reads name
            p->children[p->num_children] = malloc(sizeof(Person));
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //stores read name in child of father
            p->children[p->num_children]->name = strdup(name);
            
            //check if child already exists
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            
            //printf("@@@@@@@@@@@@@\n");
            //printf("p->name: %s\n", p->name);
            //printf("p->children[p->num_children]->name: %s\n", p->children[p->num_children]->name);
            //printf("@@@@@@@@@@@@@\n");

            //sets childs father as current person
            p->children[p->num_children]->father = p;
            p->children[p->num_children]->num_parents++;
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            //updates child node within father
            update_node(tree, p->children[p->num_children]->name, p->children[p->num_children]);
            update_node(tree, p->name, p);
            //printf("$$$$$ num parents: %d", p->children[p->num_children]->num_parents);
            p->num_children++;
        }
        //stores mother of in person 
        else if (strcmp(temp, "MOTHER_OF") == 0) {
            //assumes female if mother of
            p->sex = strdup("Female");

            //resize children array if necessary
            if (p->num_children >= p->max_children) {
                p->max_children *= 2;
                Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));
                p->children = new_child;
            }

            //allocates mem for child and reads name
            //Person *child = malloc(sizeof(Person));
            p->children[p->num_children] = malloc(sizeof(Person));
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }
            
            //stores read name in child of father
            p->children[p->num_children]->name = strdup(name);
            //child->name = strdup(name);

            //check if child already exists
            //child = get_person(child, tree, child->name);
            //p->children[p->num_children] = get_person(p->children[p->num_children], tree, child->name);

            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            //printf("@@@@@@@@@@@@@\n");
            //printf("name: %s",name);
            //printf("p->name: %s\n", p->name);
            //printf("p->children[p->num_children]->name: %s\n", p->children[p->num_children]->name);
            //printf("num_children: %d", p->num_children);
            //printf("@@@@@@@@@@@@@\n");
/*
//--------
            bool childExists = false;
            for (int j = 0; j < p->num_children; j++) {
                if (strcmp(p->children[j]->name, child->name) == 0) {
                childExists = true;
                break;
                }
            }
            if (!childExists) {
            // set the child's father as the current person
                child->mother = p;
                child->num_parents++;

            // add the child to the children array
            p->children[p->num_children] = child;
            p->num_children++;
            }
//----------
*/            
            //sets mother of child as current person
            p->children[p->num_children]->mother = p;
            p->children[p->num_children]->num_parents++;
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            //updates childs node within father
            update_node(tree, p->children[p->num_children]->name, p->children[p->num_children]);

            p->num_children++;
        }
        else if (strcmp(temp, "SEX") == 0) {
            
            //check if person already exists
            p = get_person(p, tree, p->name);
            if (strcmp(is->fields[1],"M")){
                p->sex = strdup("Female");
            }
            else{
                p->sex = strdup("Male");
            }
            //update person node with new sex
            update_node(tree, p->name, p);
        }
        //printf("Name: %s\n", name);
      
    }

    //print_person(p, tree, tmp);
    //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    topsort(tree);
    //printf("%d", !jrb_empty(tree));

/*
//------------------topological sort
    int nodecount=0;
    jrb_traverse(tmp, tree){
        nodecount++;
    }
    printf("nodecount: %d\n", nodecount);
    Dllist l;
    Dllist dtmp;
    l = new_dllist();
    
    bool unchanged = true;
    //Person* none = NULL;
    //do{
    //while(jrb_empty(tree)){
    for(int k = 0; k < nodecount; k++){
        Jval jtmp;
        JRB tmp_node;
        jrb_traverse(tmp_node, tree){
            
            Person *print_p = (Person *)tmp_node->val.v;
            print_p = get_person(print_p, tree, print_p->name);
            jtmp = new_jval_v(tmp_node->val.v);
            if((print_p->father==NULL)&&(print_p->mother==NULL)){
                dll_append(l, jtmp);
                
                for (int j = 0; j < print_p->num_children; j++) {
                    if(strcmp(print_p->sex,"Male")){
                        //if name female, remove mother from children nodes
                        print_p->children[j]->mother = NULL;
                    }
                    else{
                        print_p->children[j]->father = NULL;
                        //if name male, remove father from children nodes
                    }
                }
                
                jrb_delete_node(jrb_find_str(tree, print_p->name));

                unchanged = false;
            }
        }
    }
    //} while(nodecount>=0);
    //} while(!(jrb_empty(tree)));//while tree is not empty
    if(unchanged == true){
        printf("cycle");
    }
    print_dlist(p, l, dtmp);
*/
//-----------------------------------

    jettison_inputstruct(is);
    return 0;
}