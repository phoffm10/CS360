//Peter Hoffman
//CS360 Lab 2

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

//Person struct
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

//Forward declarations
void single_print(JRB tree);
void reset_flags(JRB tree);
void cyclecheck(JRB tree);
bool search(Person* p, char* name, JRB tree);

//Function to find person if they exist or return a new person*
Person* get_person(Person* p, JRB tree, char* name){
    JRB tmp = jrb_find_str(tree, p->name);
    if (tmp == NULL) {
        //Create new key from name if key not found
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
        return tmp->val.v;
    }
}

//Function to print a person struct
void print(Person* p){
    printf("%s\n", p->name);
    printf("  Sex: %s\n", p->sex ? p->sex : "Unknown");
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
        if(j != 0 && !strcmp(p->children[j]->name,p->children[j-1]->name)){
            continue;
        }
        printf("    %s\n", p->children[j]->name);
    }
    printf("\n");
}

//Searches for key and reinserts person with same key
void update_node(JRB tree, char* name, Person* p){
    jrb_delete_node(jrb_find_str(tree, name));
    jrb_insert_str(tree, name, new_jval_v((void *) p));
}

//Function to check if all nodes have been printed
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

//Topologically sort the JRB tree
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

//Used if only single parents remaining
void single_print(JRB tree){
    Dllist list;
    Dllist dtmp;
    list = new_dllist();
    Jval jtmp;

    JRB tmp, tmp2, tmp3;
    jrb_traverse(tmp, tree){
        Person* p = (Person*)tmp->val.v;
        p = get_person(p, tree, p->name);
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
            free(name);
        }
    }
    dll_rtraverse(dtmp, list){
        Person* p = (Person* )dtmp->val.v;
        print(p);
    }
    free_dllist(list);
}

//Function to check for cycles
void cyclecheck (JRB tree){
    JRB tmp, tmp2;
    jrb_traverse(tmp, tree){
        Person* p = (Person*)tmp->val.v;
        char* name = strdup(p->name);
        reset_flags(tree);

        if(p->num_children != 0){
            for(int i = 0; i < p->num_children; i++){ 
                JRB tmp2;
                Person* ptemp = malloc(sizeof(Person));
                tmp2 = jrb_find_str(tree, p->children[i]->name);
                ptemp = (Person*) tmp2->val.v;
                if(search(ptemp,name,tree)){
                    fprintf(stderr, "Bad input -- cycle in specification\n");
                    exit(1);
                }
            }
        }
    }
}

//Search component of cycle check
bool search(Person* p, char* name, JRB tree){
    if(p->visited == true){
        return true;
    }
    p->visited = true;

    if(strcmp(p->name, name) == 0){
        return true;
    }
    for(int i = 0; i < p->num_children; i++){      
        JRB tmp;
        tmp = jrb_find_str(tree, p->children[i]->name);
        Person* ptemp2 = malloc(sizeof(Person));
        ptemp2 = (Person*)tmp->val.v;

        ptemp2 = get_person(ptemp2, tree, ptemp2->name);
        if (search(ptemp2, name, tree)){
            return true;
        }
    ptemp2->visited = false;
    }
    return false;
}

//Used to reset visited flags
void reset_flags(JRB tree) {
    JRB tmp;
    jrb_traverse(tmp, tree) {
        Person* p = (Person *)tmp->val.v;
        p->visited = false;
    }
}

int main(int argc, char *argv[]) {
    JRB tree, tmp;
    IS is;
    Person *p = NULL;
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
            
            //New person every time "PERSON" shows up
            p = malloc(sizeof(Person));

            //Stores name of the name of the person from fields    
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //Stores read name as persons name
            p->name = strdup(name);

            //If person exists, return person*, if not create a new person* with read name
            p = get_person(p, tree, p->name);            
        } 
        
        //Stores father of person
        else if (strcmp(temp, "FATHER") == 0) {
            
            //Read in name from fields
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //Check for two fathers
            if(p->father != NULL && strcmp(p->father->name, name) != 0){
                fprintf(stderr,"Bad input -- child with two fathers on line %d\n", is->line);
                exit(1);
            }

            //Allocates mem for father and reads name
            p->father = malloc(sizeof(Person));

            //Stores read name as fathers name
            p->father->name = strdup(name);
            
            //Checks if father already exists
            p->father = get_person(p->father, tree, p->father->name);
            p = get_person(p, tree, p->name);

            //Increments childs mother's number of children and adds childs name
            p->father->children[p->father->num_children] = malloc(sizeof(Person));
            p->father->children[p->father->num_children]->name = strdup(p->name);
            p->father->num_children++;

            //Check for gender reassignment, throw error
            if(p->father->sex!=NULL && strcmp(p->father->sex,"Female")==0){
                fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                exit(1);
            }
            //Sets fathers sex as male
            p->father->sex = strdup("Male");

            //Adds parent to num parents
            if(p->num_parents < 2){
                p->num_parents++;
            }
            //Updates fathers struct and current struct
            update_node(tree, p->father->name, p->father);
            //update_node(tree, p->name, p);
        }

        //Stores mother of person
        else if (strcmp(temp, "MOTHER") == 0) {

            //Read in name from fields            
            nsize = strlen(is->fields[1]);
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //Check for two mothers, throw error
            if(p->mother != NULL && strcmp(p->mother->name, name) != 0){
                fprintf(stderr,"Bad input -- child with two mothers on line %d\n", is->line);
                exit(1);
            }

            //Allocates mem for mother and reads name
            p->mother = malloc(sizeof(Person));
            //Stores read name as mothers name
            p->mother->name = strdup(name);
            
            //Check of mother already exists
            p->mother = get_person(p->mother, tree, p->mother->name);
            //p = get_person(p, tree, p->name);

            //Increments childs mother's number of children and adds childs name
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
            //Sets mothers sex as female            
            p->mother->sex = strdup("Female");

            //Updates mothers node in tree
            update_node(tree, p->mother->name, p->mother);
            update_node(tree, p->name, p);
        }

        //Stores father of in person 
        else if (strcmp(temp, "FATHER_OF") == 0) {
            
            //Assumes male if father of
            if(p->sex!=NULL && strcmp(p->sex,"Female")==0){
                fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                exit(1);
            }
            p->sex = strdup("Male");
            
            //Resize children array if necessary
            if (p->num_children >= p->max_children) {
                p->max_children *= 2;
                Person **new_child = realloc(p->children, p->max_children * sizeof(Person*));
                p->children = new_child;
            }

            //Read in next name
            strcpy(name, is->fields[1]);
            for (i = 1; i < is->NF-1; i++) {
                strcat(name, " ");
                strcat(name, is->fields[i + 1]);
            }

            //Allocates mem for child and reads name
            p->children[p->num_children] = malloc(sizeof(Person));
            
            //Stores read name in child of father
            p->children[p->num_children]->name = strdup(name);
            
            //Check if child already exists
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            
            if(p->children[p->num_children]->father != NULL && strcmp(p->children[p->num_children]->father->name, p->name) != 0){
                fprintf(stderr,"Bad input -- child with two fathers on line %d\n", is->line);
                exit(1);
            }

            //Sets childs father as current person
            p->children[p->num_children]->father = p;
            if(p->children[p->num_children]->num_parents < 2){
                p->children[p->num_children]->num_parents++;
            }
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            //Updates child struct within father
            update_node(tree, p->children[p->num_children]->name, p->children[p->num_children]);
            update_node(tree, p->name, p);
            p->num_children++;
        }
        //Stores mother of in person 
        else if (strcmp(temp, "MOTHER_OF") == 0) {
            
            //Assumes female if mother of
            if(p->sex!=NULL && strcmp(p->sex,"Male")==0){
                fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                exit(1);
            }
            p->sex = strdup("Female");

            //Resize children array if necessary
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

            //Allocates mem for child and reads name
            p->children[p->num_children] = malloc(sizeof(Person));
            
            //Reads name in child of father
            p->children[p->num_children]->name = strdup(name);

            //Check if child already exists    
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);

            //If mother has already been set, throw error
            if(p->children[p->num_children]->mother != NULL && strcmp(p->children[p->num_children]->mother->name, p->name) != 0){
                fprintf(stderr,"Bad input -- child with two mothers on line %d\n", is->line);
                exit(1);
            }

            //Sets mother of child as current person
            p->children[p->num_children]->mother = p;
            if(p->children[p->num_children]->num_parents < 2){
                p->children[p->num_children]->num_parents++;
            }
            p->children[p->num_children] = get_person(p->children[p->num_children], tree, p->children[p->num_children]->name);
            //Updates childs person struct within mother
            update_node(tree, p->children[p->num_children]->name, p->children[p->num_children]);

            p->num_children++;
        }

        //Sets sex of person
        else if (strcmp(temp, "SEX") == 0) {
            
            //Check if person already exists
            p = get_person(p, tree, p->name);
            if (strcmp(is->fields[1],"M")){
                //If sex has already been set, throw error
                if(p->sex!=NULL && strcmp(p->sex,"Male")==0){
                    fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                    exit(1);
                }
                p->sex = strdup("Female");
            }
            else{
                //If sex has already been set, throw error
                if(p->sex!=NULL && strcmp(p->sex,"Female")==0){
                    fprintf(stderr,"Bad input - sex mismatch on line %d\n", is->line);
                    exit(1);
                }
                p->sex = strdup("Male");
            }
            //Update person struct
            update_node(tree, p->name, p);
        }
        free(temp);
    }
    
    reset_flags(tree);
    //cyclecheck(tree);
    topsort(tree);


jrb_traverse(tmp, tree){   
    Person* p = (Person*)tmp->val.v;
    free(p->name);
    free(p->sex);
    free(p->key);
    free(p->children);
    free(p); 
} 
  
/*
// Freeing p->children array
    if(p->num_children!=0){
        for (int i = 0; i < p->num_children; i++) {
            free(p->children[i]);
        }
        free(p->children);
    }
    free(p);
*/
    jrb_free_tree(tree);
    jettison_inputstruct(is);
    return 0;
}