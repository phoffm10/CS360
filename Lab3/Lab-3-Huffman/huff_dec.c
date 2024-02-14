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
    
} node;

node *make_node();
void link_node(node *parent, bool is_zero_leaf, node *child);
void add_node_to_tree(node *root, char *bit_string_path, char *decoded_string);
char *find_decoding(node *root, char *bit_string);

int main(int argc, char *argv[]) {
    if (argc <= 1) exit(1);

    FILE *f = fopen(argv[1], "rb");
    //char c;
    int buf_len = 0, buf_size = 1024;
    char *buf = malloc(buf_size * sizeof(char));

/*
    for (c = getchar(); c != EOF; c = getchar()){
        printf("%c", c);
    }
*/  
    //s = malloc(sizeof(char));
    int read_count = 0;
    while((read_count = fread(buf + buf_len, sizeof(char), 256, f))){
        buf_len += read_count;
        if (buf_len >= buf_size / 4) {
            buf_size *= 2;
            buf = realloc(buf, buf_size);
        }
    }
    // printf("%d %s", buf_len, buf);
    printf("File as bytes: ");
    int since_last_null = 0;
    for (int i=0; i<buf_len; i++) {
        if (buf[i]) {
            since_last_null++;
        } else {
            char *substr = buf + i - since_last_null;
            printf("\nChars before this null: \"%s\"\n", substr);
            printf("Bytes before this null: ");
            for (int j=0; j<since_last_null; j++) {
                printf("0x%02x ", substr[j]);
            }
            printf("\n");
            since_last_null = 0;
        }
        // printf("%02x (len=%d) ", buf[i], since_last_null);
    }
    printf("\n");
    printf("File as chars: ");
    for (int i=0; i<buf_len; i++) {
        if (buf[i] >= '\n') {
            printf("%c", buf[i]);
        }
    }
    printf("\n");
    //unsigned char digit;
    //fread(&digit, 1, 1, fp);
    
    
    //read in values as chars, (2 bytes or 8 bits at a time) (syntax for fread or fgetc)
//loop code file
    //read in chars into string until null char (how)
    //then read in chars for bit sequence associated until null (how should i store and associate these vals)
    //repeat until end of code file


    

    return 0;
}
