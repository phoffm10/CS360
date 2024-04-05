//Peter Hoffman
#include <stdio.h>
#include <stdlib.h>
//can i include this?
#include <unistd.h>
#include <stdbool.h>

//How do i structure/insert values into this list and have them correspond to spots in memory?
//Should my insert function be different than it is now, add to the end instead of beginning?

//walk list and find last non null to add chunk
//sort list when i insert chunks by location

//print debug free list function
//function to return max of two ints
//subract malloc bytes from nodes and move ptr by that many bytes

//find chunk big enough
//cast to a void*
//add passed+padded+aligned+8 size to void* ptr using ptr arithmatic


typedef struct Chunk{
  int size;
  struct Chunk* next;
  struct Chunk* prev;
} Chunk;

Chunk* free_list_head = NULL;

void *my_malloc(size_t size);
void my_free(void *ptr);
//really dont need this below
void *free_list_begin();
void *free_list_next(void *node);
void coalesce_free_list();

Chunk* create_chunk(int size){
  //cannot be called with less than 16
  //sbrk on passed size
  //maxsize = 8192

  size_t sbrk_size = (size_t)size;
  void* ptr = sbrk(sbrk_size);
  Chunk* new_chunk = (Chunk*)ptr;

  new_chunk->size = size;
  new_chunk->next = NULL;
  new_chunk->prev = NULL;
  //freelist_insert(new_chunk);
  return new_chunk;
}


//Appends node to end of list
void freelist_insert(Chunk* chunk){
  //need to add functionality to insert sorted
  chunk->next = NULL;
  chunk->prev = NULL;

  if(free_list_head == NULL){
    free_list_head = chunk;
    return;
  }

  Chunk* current = free_list_head;
  Chunk* prev = NULL;
  while(current != NULL && chunk > current){
    prev = current;
    current = current->next;
  }

  chunk->next = current;
  chunk->prev = prev;
  if(prev != NULL){
    prev->next = chunk;
  }
  else{
    free_list_head = chunk;
  }
  if(current != NULL){
    current->prev = chunk;
  }
}

void remove_freelist_chunk(Chunk* chunk){
  //should link adjacent nodes around given node
  if(chunk->prev != NULL){
    chunk->prev->next = chunk->next;
  }
  else{
    free_list_head = chunk->next;
  }
  if(chunk->next != NULL){
    chunk->next->prev = chunk->prev;
  }
}

Chunk* get_freelist_begin(){
  return free_list_head;
}
void *free_list_begin(){
  return (void*)free_list_head;
}

Chunk* get_next_free_chunk(Chunk* chunk){
  return chunk->next;
}

void *free_list_next(void *node){
  return ((Chunk*)node)->next;
}

size_t alignment(int val){
  int tmp = -8;
  val += 7 + 8;
  val = (val & tmp);
  return (size_t)val;
}

//This does not work, needs testing
void *my_malloc(size_t size){
  Chunk* mod_chunk;
  //check if call is greater than 8184, if so call sbrk on passed size and return ptr
  if(size > 8184){
    // printf("above max\n");
    // printf("size: %d\n", size);
    // printf("aligned: %d\n", alignment(size));
    void* alloc = sbrk(alignment(size));
    return (alloc + 8);
  }
  else{
    //check if free list exists
    if(get_freelist_begin() == NULL){
      //sbrk8192
      void* ptr = sbrk(8192);
      mod_chunk = (Chunk*)ptr;
      mod_chunk->size = 8192;
      //insert into free list
      freelist_insert(mod_chunk);
      //free list head should = sbrk(8192)
    }
    else{
      bool found = false;
      mod_chunk = get_freelist_begin();
      //walk list to find chunk that fits
      while (mod_chunk != NULL) {
        if(mod_chunk->size >= alignment(size)){
          void* ptr = mod_chunk;
          found = true;
          break;
        }
        mod_chunk = get_next_free_chunk(mod_chunk);
      }
      //if not found call sbrk8192
      if(found == false){
        void* ptr = sbrk(8192);
        mod_chunk = (Chunk*)ptr;
        mod_chunk->size = 8192;
        //insert into free list
        freelist_insert(mod_chunk);
      }            
    }

    //cut up free chunk ptr to alloc mem
    //move free list chunk ptr up by aligned size
    void* alloc = (char*)mod_chunk + 8;
    Chunk* new_free;
    void* tmp;
    tmp = (char*)mod_chunk + alignment(size);
    new_free = (Chunk*)tmp;
    //set new chunk size for moved chunk
    new_free->size = mod_chunk->size - alignment(size);
    //relink to list (how?)
    freelist_insert(new_free);
    remove_freelist_chunk(mod_chunk);
    //return ptr to inital mem to user
    return alloc;
  }
}

void my_free(void *ptr){
  ptr -= 8;
  Chunk* new_chunk = (Chunk*)ptr;
  freelist_insert(new_chunk);
}

void coalesce_free_list(){
  Chunk* current_chunk = free_list_begin();
  while (current_chunk != NULL && current_chunk->next != NULL){
    Chunk* next_chunk = get_next_free_chunk(current_chunk);

    if((char*)current_chunk + current_chunk->size == (char*)next_chunk){
      current_chunk->size += next_chunk->size;
      current_chunk->next = next_chunk->next;

      remove_freelist_chunk(next_chunk);
      continue;
    }
    current_chunk = get_next_free_chunk(current_chunk);
  }
}

void print_free_list(){
  Chunk* current_chunk;
  current_chunk = get_freelist_begin();
  printf("$$$$$$$$$$$$$$$$\n");
  printf("head\n");
  printf("pointer: %p\n", (void*)free_list_head);
  printf("as int: %ld\n", (long)free_list_head);
  printf("size: %d\n", free_list_head->size);
  printf("$$$$$$$$$$$$$$$$\n");

  while (current_chunk != NULL) {
    // Process current_chunk
    printf("-------------------\n");
    printf("chunk\n");
    printf("pointer: %p\n", (void*)current_chunk);
    printf("as int: %ld\n", (long)current_chunk);
    printf("size: %d\n", current_chunk->size);
    printf("-------------------\n");
    current_chunk = get_next_free_chunk(current_chunk);
  }
}

// int main(int argc, char* argv[]){
//   // Chunk* newchunk = create_chunk(2000);
//   // freelist_insert(newchunk);
//   // Chunk* newchunk1 = create_chunk(3000);
//   // freelist_insert(newchunk1);
//   // Chunk* newchunk2 = create_chunk(4000);
//   // freelist_insert(newchunk2);
//   // freelist_insert(create_chunk(4567));
//   // freelist_insert(create_chunk(16));
//   // freelist_insert(create_chunk(30));

//   // print_free_list();

//   // printf("alignment test\n");
//   // int test = 9990;
//   // printf("initial: %d\n", test);
//   // printf("aligned: %d\n", alignment(test));
//   // printf("malloc testing\n");
//   // my_malloc(8185);
//   return 0;
// }