//Peter Hoffman
#include <stdio.h>
#include <stdlib.h>

typedef struct sllist{
  int data;
  struct sllist* next;
} *Sllist;

void *my_malloc(size_t size);
void my_free(void *ptr);
void *free_list_begin();
void *free_list_next(void *node);
void coalesce_free_list();

//Sll framework------------------
Sllist new_sllist();
void sll_insert(Sllist node, int val);
void sll_traverse(Sllist list);
Sllist find_node(Sllist list, int val);
void free_sllist(Sllist list);
//-------------------------------

//Initializes sll
Sllist new_sllist(){
  Sllist list;
  list = (Sllist)malloc(sizeof(struct sllist));
  list->next = NULL;
  return list;
}

//Appends node to end of list
void sll_insert(Sllist node, int val){
  Sllist newnode;

  newnode = (Sllist) malloc(sizeof(struct sllist));
  newnode->data = val;
  newnode->next = NULL;

  while (node->next != NULL) {
    node = node->next;
  }
  node->next = newnode;
}

//Loops through list elements
void sll_traverse(Sllist list){
  Sllist ptr = list->next;
  while (ptr != NULL) {
    printf("%d\n", ptr->data);
    ptr = ptr->next;
  }
}

//Finds and returns node pointer
Sllist find_node(Sllist list, int val){
  Sllist ptr = list->next;
  while (ptr != NULL) {
    if(ptr->data == val){
      return ptr;
    }
    ptr = ptr->next;
  }
  return NULL;
}

//Frees pointers to each element
void free_sllist(Sllist list){
  Sllist ptr = list->next;
  while (ptr != NULL) {
    Sllist temp = ptr;
    ptr = ptr->next;
    free(temp);
  } 
  free(ptr);
  free(list); 
}

int main(int argc, char* argv[]){

  Sllist list;

  list = new_sllist();

  sll_insert(list, 8);
  sll_insert(list, 5);
  sll_insert(list, 78);
  sll_insert(list, 99);
  sll_insert(list, 8234);

  sll_traverse(list);

  Sllist tmp = list->next;
  while(tmp != NULL){
    if(tmp->data == 78){
      tmp->data = 70;
    }
    tmp = tmp->next;
  }

  Sllist temp = find_node(list, 99);
  temp->data = 5000;

  sll_traverse(list);

  free_sllist(list);
  return 0;
}