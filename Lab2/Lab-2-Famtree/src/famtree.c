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
-need to implement cycle check correctly
*/

typedef struct Person{
    char* key;
    char* name;
    char* sex;
    struct Person* father;
    struct Person* mother;
    struct Person** children;
    int num_children;
    int max_children;
    int num_parents;
    bool visited;
    bool printed;
    bool curr_path;
} Person;

void single_print(JRB tree);
void reset_flags(JRB tree);
void cyclecheck(JRB tree);
bool search(Person* p, char* name, JRB tree);

/*
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
    printf("num_parents: %d", p->num_parents);
    printf("visited: %d\n", p->visited);
    printf("printed: %d\n", p->printed);
    printf("\n"); 
    }
    printf("-----------------------\n");
}
*/

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
        p->curr_path = false;
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
            p = get_person(p, tree, p->name);
            //if person has unprinted parents
            if(!(p->printed) && 
                (p->mother == NULL || p->mother->printed) && 
                (p->father == NULL || p->father->printed)){

                print(p);
                p->printed = true;
            }
        }
        jrb_traverse(tmp, tree){
            Person* p = (Person*)tmp->val.v;
            p = get_person(p, tree, p->name);
            if(p->printed){
                for (int j = 0; j < p->num_children; j++) {      
                    p->children[j]->num_parents--;
                }
            }
        }
        
        bool no_parents = false;
        jrb_traverse(tmp, tree){
            Person* p = (Person*)tmp->val.v;
            if(!p->printed && p->num_parents == 0){
                no_parents = true;
            }
        }
        bool single_parents = true;
        jrb_traverse(tmp, tree){
            Person* p = (Person*)tmp->val.v;
            if(!p->printed && p->num_parents != 1){
                single_parents = false;
            }
        }
        if(no_parents==false && single_parents == true){
            single_print(tree);
        }

        if (no_parents==false && single_parents == false){
            jrb_traverse(tmp, tree){
                Person* p = (Person*)tmp->val.v;
                    if(!p->printed){
                        print(p);
                        p->printed = true;
                    }
            }
        }
        
    }
}

void single_print(JRB tree){
    Dllist list;
    Dllist dtmp;
    list = new_dllist();
    Jval jtmp;

    JRB tmp, tmp2, tmp3;
    jrb_traverse(tmp, tree){
        Person* p = (Person*)tmp->val.v;
        p = get_person(p, tree, p->name);
            //if person has unprinted parents, need to print parents first.
        if(!p->printed && (p->num_children == 0)){
            p->printed = true;
            jtmp = new_jval_v(p);
            dll_append(list, jtmp);

            char* name;
            if(p->mother != NULL){
                name = strdup(p->mother->name);
            }
            else{
                name = strdup(p->father->name);
            }

            jrb_traverse(tmp3, tree){
                jrb_traverse(tmp2, tree){
                    Person* p2 = (Person*)tmp2->val.v;
                    if(!p2->printed){
                        if(strcmp(name, p2->name)==0){
                            p2->printed = true;
                            jtmp = new_jval_v(p2);
                            dll_append(list, jtmp);
                            if(p2->mother != NULL){
                                name = strdup(p2->mother->name);
                            }
                            else{
                                name = strdup(p2->father->name);
                            }
                        }
                    }
                }
            }
        }
    }
    dll_rtraverse(dtmp, list){
        //printf("dll print");
        Person* p = (Person* )dtmp->val.v;
        print(p);
    }
}


void cyclecheck (JRB tree){
    JRB tmp;
    jrb_traverse(tmp, tree){
        Person* p = (Person*)tmp->val.v;
        char* name = strdup(p->name);
        
        if(search(p,name,tree)){
            fprintf(stderr, "Bad input -- cycle in specification");
            exit(1);
        }
    }
}

bool search(Person* p, char* name, JRB tree){
    if(p->visited == true){
        return false;
    }
    p->visited = true;
    if(strcmp(p->name, name) == 0){
        return true;
    }
    for(int i = 0; i < p->num_children; i++){

        p->children[i] = get_person(p->children[i], tree, p->children[i]->name);
        if (search(p->children[i], name, tree)){
            return true;
        }
    }
    return false;
}



void reset_flags(JRB tree) {
    JRB tmp;
    // Perform DFS traversal from each person in the family tree
    jrb_traverse(tmp, tree) {
        Person* p = (Person *)tmp->val.v;
        p->visited = false;
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
            
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //check for two fathers
            if(p->father != NULL && strcmp(p->father->name, name) != 0){
                fprintf(stderr,"Bad input -- child with two fathers on line %d\n", is->line);
                exit(1);
            }

            //allocates mem for father and reads name
            p->father = malloc(sizeof(Person));

            //stores read name as fathers name
            p->father->name = strdup(name);
            
            //checks if father already exists
            p->father = get_person(p->father, tree, p->father->name);
            p = get_person(p, tree, p->name);

            //increments childs mother's number of children and adds childs name
            p->father->children[p->father->num_children] = malloc(sizeof(Person));
            p->father->children[p->father->num_children]->name = strdup(p->name);
            p->father->num_children++;

            //Bad input - sex mismatch on line 76
            if(p->father->sex!=NULL && strcmp(p->father->sex,"Female")==0){
                fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                exit(1);
            }
            //sets fathers sex as male
            p->father->sex = strdup("Male");

            //adds parent to num parents
            if(p->num_parents < 2){
                p->num_parents++;
            }
            //updates fathers node in tree
            update_node(tree, p->father->name, p->father);
            update_node(tree, p->name, p);
        }
        //stores mother of person
        else if (strcmp(temp, "MOTHER") == 0) {

            //Bad input -- child with two mothers on line 67
            
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //check for two mothers
            if(p->mother != NULL && strcmp(p->mother->name, name) != 0){
                fprintf(stderr,"Bad input -- child with two mothers on line %d\n", is->line);
                exit(1);
            }

            //allocates mem for mother and reads name
            p->mother = malloc(sizeof(Person));
            //stores read name as mothers name
            p->mother->name = strdup(name);
            
            //check of mother already exists
            p->mother = get_person(p->mother, tree, p->mother->name);
            p = get_person(p, tree, p->name);

            //increments childs mother's number of children and adds childs name
            p->mother->children[p->mother->num_children] = malloc(sizeof(Person));
            p->mother->children[p->mother->num_children]->name = strdup(p->name);
            p->mother->num_children++;
            if(p->num_parents < 2){
                p->num_parents++;
            }

            //Bad input - sex mismatch on line 76
            if(p->mother->sex!=NULL && strcmp(p->mother->sex,"Male")==0){
                fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                exit(1);
            }
            //sets mothers sex as female            
            p->mother->sex = strdup("Female");

            //updates mothers node in tree
            update_node(tree, p->mother->name, p->mother);
            update_node(tree, p->name, p);

        }
        //stores father of in person 
        else if (strcmp(temp, "FATHER_OF") == 0) {
            
            //assumes male if father of
            if(p->sex!=NULL && strcmp(p->sex,"Female")==0){
                fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                exit(1);
            }
            p->sex = strdup("Male");
            
            //resize children array if necessary
            if (p->num_children >= p->max_children) {
                p->max_children *= 2;
                Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));
                p->children = new_child;
            }

            
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //allocates mem for child and reads name
            p->children[p->num_children] = malloc(sizeof(Person));
            
            //stores read name in child of father
            p->children[p->num_children]->name = strdup(name);
            
            //check if child already exists
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            
            if(p->children[p->num_children]->father != NULL && strcmp(p->children[p->num_children]->father->name, p->name) != 0){
                fprintf(stderr,"Bad input -- child with two fathers on line %d\n", is->line);
                exit(1);
            }

            //sets childs father as current person
            p->children[p->num_children]->father = p;
            if(p->children[p->num_children]->num_parents < 2){
                p->children[p->num_children]->num_parents++;
            }
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            //updates child node within father
            update_node(tree, p->children[p->num_children]->name, p->children[p->num_children]);
            update_node(tree, p->name, p);
            p->num_children++;
        }
        //stores mother of in person 
        else if (strcmp(temp, "MOTHER_OF") == 0) {
            
            //assumes female if mother of
            if(p->sex!=NULL && strcmp(p->sex,"Male")==0){
                fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                exit(1);
            }
            p->sex = strdup("Female");

            //resize children array if necessary
            if (p->num_children >= p->max_children) {
                p->max_children *= 2;
                Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));
                p->children = new_child;
            }
            
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //allocates mem for child and reads name
            p->children[p->num_children] = malloc(sizeof(Person));
            
            //stores read name in child of father
            p->children[p->num_children]->name = strdup(name);

            //check if child already exists    
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);

            if(p->children[p->num_children]->mother != NULL && strcmp(p->children[p->num_children]->mother->name, p->name) != 0){
                fprintf(stderr,"Bad input -- child with two mothers on line %d\n", is->line);
                exit(1);
            }

            //sets mother of child as current person
            p->children[p->num_children]->mother = p;
            if(p->children[p->num_children]->num_parents < 2){
                p->children[p->num_children]->num_parents++;
            }
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            //updates childs node within father
            update_node(tree, p->children[p->num_children]->name, p->children[p->num_children]);

            p->num_children++;
        }
        else if (strcmp(temp, "SEX") == 0) {
            
            //check if person already exists
            p = get_person(p, tree, p->name);
            if (strcmp(is->fields[1],"M")){
                if(p->sex!=NULL && strcmp(p->sex,"Male")==0){
                    fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                    exit(1);
                }
                p->sex = strdup("Female");
            }
            else{
                if(p->sex!=NULL && strcmp(p->sex,"Female")==0){
                    fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                    exit(1);
                }
                p->sex = strdup("Male");
            }
            //update person node with new sex
            update_node(tree, p->name, p);
        }
        //printf("Name: %s\n", name);
      
    }

    //print_person(p, tree, tmp);
    reset_flags(tree);
/*
    if(has_cycle(tree)==true){
        fprintf(stderr, "Bad input -- cycle in specification\n");
        exit(1);
    }
*/
    //cycle_check(tree);
    //cyclecheck(tree);
    topsort(tree);
    //top_sort(tree);

    jettison_inputstruct(is);
    return 0;
}