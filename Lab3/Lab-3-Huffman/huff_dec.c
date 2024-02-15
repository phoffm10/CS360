//Peter Hoffman
//CS360 Lab3

//need to parse code definition file
//store values as decoding key
//parse input file to stardard output


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    struct node *zero;
    struct node *one;
    char *s_zero;
    char *s_one;
} node;

void create_node(node *node, char* bitstream, char* string);
//should create a node based on current tree and how many branches have already been created
//needs to traverse tree and append node to correct leaf


node * decode(node *root, char *bit_string);
//called for every bit in decoding sequence
//takes 1 "step", returns curr node or prints strng and sets curr as root


void create_node(node *root, char* bitstream, char* string){
    node *curr = (node*)malloc(sizeof(node));
    curr = root;

    for (unsigned int i = 0; i < strlen(bitstream); i++){
        char bit = bitstream[i];
        if (bit == '1'){
            if ((curr->one == NULL) && i != (strlen(bitstream)-1)){
                //create node at 1
                node *next = (node*)malloc(sizeof(node));
                curr->one = next;
                //set curr node as curr->one
                curr = curr->one;
            }
            else if ((curr->one != NULL) && i != (strlen(bitstream)-1)){
                //set curr node as curr->one
                curr = curr->one;
            }
            else{
                //copy string to curr->s_one
                curr->s_one = strdup(string);
            }
        }
        else{
            if ((curr->zero == NULL) && i != (strlen(bitstream)-1)){
                //create node at 0
                node *next = (node*)malloc(sizeof(node));
                curr->zero = next;
                //set curr node as curr->zero
                curr = curr->zero;
            }
            else if ((curr->zero != NULL) && i != (strlen(bitstream)-1)){
                //set curr node as node->zero
                curr = curr->zero;
            }
            else{
                //copy string to node->s_zero
                curr->s_zero = strdup(string);
            }
        }
    }
}

int main(int argc, char *argv[]) {

    //holds code values until stored in tree
    char* s_str;
    char* b_str;
    
    //Defining root node
    node *root;
    root = (node *) malloc(sizeof(node));
    root->s_zero = NULL;
    root->s_one = NULL;

    //printf("%s\n", root->one->s_one);
    // syntax for adding nodes
    // char *encoding = "011";
    // node *cur_node = root;
    // for (int i=0; i<strlen(encoding); i++) {
    //     if (encoding[i] == '1') {
    //         cur_node = cur_node->one;
    //     } else {
    //         cur_node = cur_node->zero;
    //     }
    // }

    if (argc <= 1) exit(1);

    FILE *f = fopen(argv[1], "rb");

    int buf_len = 0, buf_size = 1024;

    char *buf = malloc(buf_size * sizeof(char));

    int read_count = 0;
    while((read_count = fread(buf + buf_len, sizeof(char), 256, f))){
        buf_len += read_count;
        if (buf_len >= buf_size / 4) {
            buf_size *= 2;
            buf = realloc(buf, buf_size);
        }
    }
    // printf("%d %s", buf_len, buf);
    //printf("File as bytes: ");
    int string_flag = 0;
    int since_last_null = 0;
    for (int i=0; i<buf_len; i++) {
        if (buf[i]) {
            since_last_null++;
        } else {
            //char *substr = buf + i - since_last_null;

            //printf("\nChars before this null: \"%s\"\n", substr);
            //string and bitstream stored in substr, call functions from here
            
            // printf("Bytes before this null: ");
            // for (int j=0; j<since_last_null; j++) {
            //     printf("0x%02x ", substr[j]);
            // }
            // printf("\n");
            if(string_flag % 2 == 0){
                //char* s_str = buf + i - since_last_null;
                s_str = strdup(buf + i - since_last_null);
                //printf("string: %s", s_str);
            }
            else{
                //char* b_str = buf + i - since_last_null;
                b_str = strdup(buf + i - since_last_null);
                //printf("bitstream: %s", b_str);
            }
            string_flag++;
            since_last_null = 0;

            if (string_flag != 0 && string_flag % 2 == 0){
                //string and bitstream stored as char*
                //call tree building function from here
                create_node(root, b_str, s_str);
                printf("--------------\n");
                printf("string: %s, bitstream: %s\n", s_str, b_str);
                /*
                for (unsigned int i = 0; i < strlen(b_str); i++){
                    char bit = b_str[i];
                    printf("individual bits: %c\n", bit);
                }
                printf("--------------\n");
                */
            }           

        }

    }

    //read encoded file here
    //need logic to determine remainder bits outside of 8bit words
    //find bit sequence size with fseek() and SEEKEND-4 to isolate integer val
    //use lsr anded with 0x01 to isolate single bit
    //call decode for each bit,

    printf("\n");
    printf("File as chars: ");
    for (int i=0; i<buf_len; i++) {
        if (buf[i] >= '\n') {
            printf("%c", buf[i]);
        }
    }
    printf("\n");
    printf("$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("node string: %s\n", root->one->one->one->zero->one->s_one);
    printf("$$$$$$$$$$$$$$$$$$$$$$$\n");

    return 0;
}
