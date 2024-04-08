//Peter Hoffman

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//Free list struct
typedef struct Chunk{
  int size;
  struct Chunk* next;
  struct Chunk* prev;
} Chunk;

//Global list pointer
Chunk* free_list_head = NULL;

void freelist_insert(Chunk* chunk);
void remove_freelist_chunk(Chunk* chunk);
Chunk* get_freelist_begin();
Chunk* get_next_free_chunk(Chunk* chunk);
size_t alignment(int val);
void print_free_list();

void *my_malloc(size_t size);
void my_free(void *ptr);
void *free_list_begin();
void *free_list_next(void *node);
void coalesce_free_list();

//Appends node to freelist, inserts in ascending order
void freelist_insert(Chunk* chunk){
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

//Removes chunk and links adjacent nodes to each other
void remove_freelist_chunk(Chunk* chunk){
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

//Both of these return pointers to free list head
Chunk* get_freelist_begin(){
  return free_list_head;
}
void *free_list_begin(){
  return (void*)free_list_head;
}

//Both of these return next freelist pointer if it exists
Chunk* get_next_free_chunk(Chunk* chunk){
  Chunk *nchunk = chunk;
  if (nchunk != NULL && nchunk->next != NULL) {
    return nchunk->next;
  } else {
    return NULL;
  }
}
void *free_list_next(void *node){
  Chunk *chunk = (Chunk *)node;
  if (chunk != NULL && chunk->next != NULL) {
    return chunk->next;
  } else {
    return NULL;
  }
}

//Returns aligned size given a requested size
size_t alignment(int val){
  int tmp = -8;
  val += 7 + 8;
  val = (val & tmp);
  return (size_t)val;
}

void *my_malloc(size_t size){
  Chunk* mod_chunk;
  //Check if call is greater than 8184, if so call sbrk on passed size and return ptr
  if(size >= 8184){
    void* alloc = sbrk(alignment(size));
    int* size_ptr = (int*)((void*)alloc);
    *size_ptr = alignment(size);
    return (alloc + 8);
  }
  else{
    //Check if free list exists
    if(get_freelist_begin() == NULL){
      void* ptr = sbrk(8192);
      mod_chunk = (Chunk*)ptr;
      mod_chunk->size = 8192;
      //Insert into free list
      freelist_insert(mod_chunk);
    }
    else{
      bool found = false;
      mod_chunk = get_freelist_begin();
      //Walk list to find chunk that fits
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
        //Insert into free list
        freelist_insert(mod_chunk);
      }            
    }

    //Resize free list chunk size
    mod_chunk->size -= alignment(size);
    Chunk* alloc = (Chunk*)((void*)mod_chunk + mod_chunk->size + 8);
    alloc->size = alignment(size);

    //Set size of first 8 bytes for alloc ptr
    int* size_ptr = (int*)((void*)alloc - 8);
    *size_ptr = alignment(size);

    //If the free list chunk is now size 0, remove it from the list
    if(mod_chunk->size == 0){
      remove_freelist_chunk(mod_chunk);
      free_list_head = NULL;
    }
    return (void*)alloc;
  }
}

//Inserts pointer back into free list
void my_free(void *ptr){
  ptr -= 8;
  Chunk* new_chunk = (Chunk*)ptr;
  freelist_insert(new_chunk);
}

//Checks adjacent nodes to see if address is the same and coalesces
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

//Prints free list for debugging
void print_free_list(){
  Chunk* current_chunk;
  current_chunk = get_freelist_begin();

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
  if(current_chunk == NULL){
    printf("No free list\n");
  }
}