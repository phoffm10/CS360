//Peter Hoffman
//CS360 Lab 2

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "fields.h"
#include "dllist.h"

//general structure
//output is standard out

// ./bin/famtree < fam1.txt
typedef struct {
    char* key;
    char* name;
    char* sex;
    struct Person *father;
    struct Person *mother;
    struct Person** children;
    bool visited;
} Person;

Person *person;

int main(int argc, char *argv[]) {
  /*
    //from lecture notes
    IS is;
    int i;

    //if (argc != 2) { fprintf(stderr, "usage: printwords filename\n"); exit(1); }
 
  // Open the file as an inputstruct.  Error check. 

    is = new_inputstruct(NULL);
    if (is == NULL) {
        perror(NULL);
        exit(1);
    }

  // Read each line with get_line().  Print out each word.

    while(get_line(is) >= 0) {
        for (i = 0; i < is->NF; i++) {
            printf("%d: %s\n", is->line, is->fields[i]);
        }
    }
*/
  /* Free up the memory allocated with new_inputstruct, and
     close the open file.  This is not necessary in this program, 
     since we are exiting anyway, but I just want to show how you free it up. */
    
  //  jettison_inputstruct(is);
  //end of lecture notes code
  JRB t, tmp;
  IS is;
  Person *p;
  int nsize, i;
  char* temp;

  is = new_inputstruct(NULL);
  t = make_jrb();

  while (get_line(is) >= 0) {
    for (i = 0; i < is->NF; i++){
      nsize = strlen(is->fields[i]);
      temp = (char *) malloc(sizeof(char)*(nsize+1));
      strcpy(temp, is->fields[i]);      
      


      if (strcmp(temp,"PERSON")==0){
        p = malloc(sizeof(Person));
        p->name = (char *) malloc(sizeof(char)*(nsize+1));
        strcpy(p->name, is->fields[i+1]);
        printf("Person name: %s\n", p->name);
      }
      //how do i add these to a struct
      if (strcmp(temp,"MOTHER_OF")==0){
        printf("Is mother to: %s\n", is->fields[i+1]);
      }
      //how to add to struct
      if (strcmp(temp,"FATHER_OF")==0){
        printf("Is father to: %s\n", is->fields[i+1]);
      }
      //how to add to struct
      if (strcmp(temp,"SEX")==0){
        printf("Sex is: %s\n", is->fields[i+1]);
      }
      //printf("%d: %s\n", is->line, is->fields[i]);

    }

    /*
    if (is->NF > 0) {

      // Each line is name followed by score.  The score is easy to get. 

      p = malloc(sizeof(Person));

      // The name is a different matter, because names may be composed of any 
      //   number of words with any amount of whitespace.  We want to create a 
      //   name string that has each word of the name separated by one space. 
  
      //  Our first task is to calculate the ssize of our name. 

      nsize = strlen(is->fields[1]);
      for (i = 0; i < is->NF; i++) nsize += (strlen(is->fields[i])+1);

      // We then allocate the string and copy the first word into the string. 
      if(is->fields[1] == "SEX"){
      p->sex = (char *) malloc(sizeof(char) + 1);
      strcpy(p->sex, is->fields[1]);
      }

      //p->sex = (char *) malloc(sizeof(char) + 1);
      else{
      p->name = (char *) malloc(sizeof(char)*(nsize+1));
      strcpy(p->name, is->fields[1]);
      }

      // We copy in the remaining words, but note how we do so by calling strcpy
      //   into the exact location of where the name goes, rather than, say, repeatedly
      //   calling strcat() as we would do in a C++-like solution.  This is much more 
      //   efficient (not to mention inconvenient) than using strcat(). 
         
      nsize = strlen(is->fields[1]);
      
      for (i = 0; i < is->NF; i++) {
        if(is->fields[2] == "SEX"){
          strcpy(p->sex, is->fields[i+1]);
        }
        else if (is->fields[1] == "PERSON"){
        p->name[nsize] = ' ';
        strcpy(p->name+nsize+1, is->fields[i+1]);
        nsize += strlen(p->name+nsize);
        }
      }

      // We create a key for inserting into the red-black tree.  That is going
      //   to be the score, padded to 10 characters, followed by the name.  We 
      //   allocate (nsize+12) characters: nsize for the name, 10 for the score,
      //   one for the space, and one for the null character. 

      p->key = (char *) malloc(sizeof(char) * (nsize + 1));
      sprintf(p->key, "%s", p->name);
 
      jrb_insert_str(t, p->key, new_jval_v((void *) p));
    }
  }

  // Traverse the tree and print the people. 

  jrb_traverse(tmp, t) {
    p = (Person *) tmp->val.v;
    printf("%-40s %s\n", p->name, p->sex);
  }
  */
  //test printing
  //printf("%s\n", p->name);
  }
    fprintf(stdout, "Hello stdout!\n");
    fprintf(stderr, "Hello stderr!\n");
  return 0;
}
