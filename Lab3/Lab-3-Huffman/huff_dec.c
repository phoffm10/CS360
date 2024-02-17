//Peter Hoffman
//CS360 Lab3 - Huffman Encoding

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Node struct
typedef struct node {
    struct node *zero;
    struct node *one;
    char *s_zero;
    char *s_one;
} node;

//Forward declarations
void create_node(node *node, char* bitstream, char* string);
node* decode(node *root, node *curr, int ibit);
void free_node(node *node);

void free_node(node *node){
    if (node == NULL){
        return;
    }
    //Frees nodes recursively
    free_node(node->one);
    free_node(node->zero);

    free(node->s_one);
    free(node->s_zero); 
    
    free(node);
}

void create_node(node *root, char* bitstream, char* string){
    
    //Sets current node as node passed to function
    node *curr = root;

    for (unsigned int i = 0; i < strlen(bitstream); i++){
        char bit = bitstream[i];
        if (bit == '1'){
            if ((curr->one == NULL) && i != (strlen(bitstream)-1)){
                //Creates node at 1 leaf
                node *next = (node*)malloc(sizeof(node));
                next->one = NULL;
                next->zero = NULL;
                next->s_one = NULL;
                next->s_zero = NULL;

                curr->one = next;
                //Sets curr node as curr->one
                curr = curr->one;

                free(next->one);
                free(next->zero);
                free(next->s_one);
                free(next->s_zero);
            }
            else if ((curr->one != NULL) && i != (strlen(bitstream)-1)){
                //Sets curr node as curr->one
                curr = curr->one;
            }
            else{
                //Copies string to curr->s_one
                curr->s_one = strdup(string);
            }
        }
        else{
            if ((curr->zero == NULL) && i != (strlen(bitstream)-1)){
                //Create node at 0 leaf
                node *next = (node*)malloc(sizeof(node));
                next->one = NULL;
                next->zero = NULL;
                next->s_one = NULL;
                next->s_zero = NULL;

                curr->zero = next;
                //Sets curr node as curr->zero
                curr = curr->zero;

                free(next->one);
                free(next->zero);
                free(next->s_one);
                free(next->s_zero);
            }
            else if ((curr->zero != NULL) && i != (strlen(bitstream)-1)){
                //Sets curr node as node->zero
                curr = curr->zero;
            }
            else{
                //Copies string to node->s_zero
                curr->s_zero = strdup(string);
            }
        }
    }
}

node* decode(node *root, node *curr, int ibit){
    //Check if 1 bit is valid and what node branches exist
    if (ibit == '1'){
        if (curr->one == NULL){
            if(curr->s_one == NULL){
                fprintf(stderr, "Unrecognized bits\n");
                exit(1);
            }
            //Prints string at leaf and sets curr node to root
            printf("%s", curr->s_one);
            curr = root;
            return curr;
        }
        //Advances down the tree if curr->one exists
        else{
            curr = curr->one;
            return curr;
        }
    }
    //Check if 0 bit is valid and what node branches exist
    else{
        if (curr->zero == NULL){
            if(curr->s_zero == NULL){
                fprintf(stderr, "Unrecognized bits\n");
                exit(1);
            }
            //Prints string at leaf and sets curr node to root
            printf("%s", curr->s_zero);
            curr = root;
            return curr;
        }
        //Advances down the tree if curr->zero exists
        else{
            curr = curr->zero;
            return curr;            
        }
    }
}

int main(int argc, char *argv[]) {

    //Temps for holding code values until stored in tree
    char* s_str;
    char* b_str;
    
    //Defining root node
    node *root;
    root = (node *) malloc(sizeof(node));
    root->one = NULL;
    root->zero = NULL;
    root->s_zero = NULL;
    root->s_one = NULL;

    //Usage
    if (argc <= 1) exit(1);

    //Initializing file pointers
    FILE *fc = fopen(argv[1], "rb");
    FILE *fe = fopen(argv[2], "rb");

    //Setting a starting buffer size
    int buf_len = 0, buf_size = 2048;

    char *buf = malloc(buf_size * sizeof(char));

    int read_count = 0;
    while((read_count = fread(buf + buf_len, sizeof(char), 256, fc))){
        buf_len += read_count;
        if (buf_len >= buf_size / 4) {
            buf_size *= 2;
            buf = realloc(buf, buf_size);
        }
    }

    int string_flag = 0;
    int since_last_null = 0;
    for (int i=0; i<buf_len; i++) {
        if (buf[i]) {
            since_last_null++;
        } 
        else {

            //Stores bitsream and string as char*
            if(string_flag % 2 == 0){
                s_str = strdup(buf + i - since_last_null);
            }
            else{
                b_str = strdup(buf + i - since_last_null);
            }
            string_flag++;
            since_last_null = 0;

            //String and bitstream sent to create_node
            if (string_flag != 0 && string_flag % 2 == 0){
                create_node(root, b_str, s_str);
                free(b_str);
                free(s_str);
            }           
        }
    }

    //Reads int from last 4 bytes of encoding file
    unsigned int esize = 0;
    fseek(fe, -4, SEEK_END);
    fread(&esize, sizeof(unsigned int), 1, fe);
    rewind(fe);
    
    //Getting filesize
    fseek(fe, 0, SEEK_END);
    unsigned int filesize = (int)ftell(fe);

    //Checking if filesize is less than 4 bytes
    if(filesize<4){
        fprintf(stderr,"Error: file is not the correct size.\n");
        exit(1);
        }
    
    rewind(fe);

    //Setting amount of characters to read from int value 
    unsigned int charsize = 0;
    if(esize % 8 != 0){
        charsize = (esize/8)+1;
    }
    else{
        charsize = (esize/8);
    }

    //Reads specified bytes from encoding file
    char *encbuf = malloc(charsize * sizeof(char));
    fread(encbuf, sizeof(char), charsize, fe);

    filesize = 0;
    filesize = (int)ftell(fe);

    //Error if file is different from expexted value given by trailing int
    if (filesize != charsize){
        fprintf(stderr,"Error: Total bits = %d, but file's size is %d\n", esize, filesize);
        exit(1);
    }

    //Initializes temp node   
    node *tmp = root;

    //Runs for amount of chars in encoding buffer
    for (unsigned int k = 0; k < charsize; k++){
        if(esize == 0){
            break;
        }
        //Only runs if less than 8 bits remaining
        if (esize < 8){
            for (unsigned int i = 0; i < esize; i++){
                int chb = encbuf[k];
                int ibit = 0;
                ibit = (chb >> i) & 0x01; //Isolates right most bit
                tmp = decode(root, tmp, ibit? '1' : '0');
            }
        }
        else{
            for (int i = 0; i < 8; i++){
                int chb = encbuf[k];
                int ibit = 0;
                ibit = (chb >> i) & 0x01;  //Isolates right most bit
                tmp = decode(root, tmp, ibit? '1' : '0');
            }
            esize = esize - 8;
        }
    }

    //Freeing memory
    free(buf);
    free(encbuf);
    free_node(tmp);
    fclose(fc);
    fclose(fe);

    return 0;
}


