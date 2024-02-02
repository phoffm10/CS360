//Peter Hoffman
//CS360 Lab 1 chain_heal
/*
CITES:
geeksforgeeks DFS in C "https://www.geeksforgeeks.org/c-program-to-implement-dfs-traversal-using-adjacency-matrix-in-a-given-graph/"
The C Programming Language 2nd Ed., Kernighan and Ritchie - Chapter 1.5, Counting Characters in Input
Adjacency Lists in C "https://www.programiz.com/dsa/graph-adjacency-list"
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

//Node struct to store player information and adjacency
typedef struct node{
    char name[100];
    int x,y;
    int curr_pp, max_pp;
    struct node *prev;
    bool visited;
    int healing;

    int adj_size;
    struct node** adj;
} Node;

//Global variables used
int initial_range, jump_range, num_jumps, initial_power, num_players, individual_healing;
double power_reduction;

int total_healing = 0;
int best_healing = 0;
double current_healing = 0;

int* current_path;
int* best_path;
int* best_path_healing;
int best_path_length;

//DFS function
void dfs(Node nodes[], int start, int max_hops, int hop_num){
    if (hop_num > max_hops || nodes[start].visited){
        return;
    }

//Setting current node visited
    nodes[start].visited = true;
    current_healing = initial_power * pow(1-power_reduction, hop_num-1);

//Healing math with power reduction
    if ((nodes[start].max_pp-nodes[start].curr_pp) > current_healing){
        individual_healing = rint(current_healing);
    }
    else{
        individual_healing = (nodes[start].max_pp-nodes[start].curr_pp);
    }
    nodes[start].healing = individual_healing;

//Updating current path
    current_path[hop_num - 1] = start;
    int total_healing = 0;

//Adding individual healings to total healing
    for (int i = 0; i < hop_num; i++) {
        total_healing += nodes[current_path[i]].healing;
    }

//Setting best healing if total is greater
    if (total_healing > best_healing) {
        best_healing = total_healing;

        //Sets best path from current
        for (int i = 0; i < hop_num; i++) {
            best_path[i] = current_path[i];
            best_path_healing[i] = nodes[current_path[i]].healing;
        }
        best_path_length = hop_num;
    }

//Recursively calls DFS on other nodes
    for (int i = 0; i < nodes[start].adj_size; i++){
        int adjacentIndex = nodes[start].adj[i] - nodes;

        dfs(nodes, adjacentIndex, max_hops, hop_num+1);
    }
    nodes[start].visited = false;
}


int main(int argc, char *argv[]) {

Node *n;

//Storing command line args
//Usage is ./chain_heal initial_range jump_range num_hops initial_power power_reduction
if (argc >= 5){
initial_range = atoi(argv[1]);
jump_range = atoi(argv[2]);
num_jumps = atoi(argv[3]);
initial_power = atoi(argv[4]);
power_reduction = atof(argv[5]);
}
else{
    printf("Bad usage");
}

//Variables used to count lines in input
num_players = 0;
char c;

//Read through file to get num_players from newline chars
do{
    c = getchar();
    if (c == '\n'){
        ++num_players;
    }
} while (c != EOF);

//malloc node structs based on # of newline chars
n = (Node *) malloc(sizeof(Node)*num_players);
if (n == NULL){
    printf("malloc failed\n");
    return 1;
}

//Resets the file pointer and stores node information
rewind(stdin);
for (int i = 0; i<num_players; i++){
    if (fscanf(stdin, "%d %d %d %d %99s", &n[i].x, &n[i].y, &n[i].curr_pp, &n[i].max_pp, n[i].name)== 5){
    }
    else{
        printf("Error reading data\n");
        free(n);
        return 1;
    }
}

//Creating adjacency matrix rows
int** adjlist = (int**)malloc(num_players * sizeof(int*));
if (adjlist == NULL){
    printf("malloc failed");
}

//Creating adjacency matrix cols
for(int i = 0; i < num_players; i++){
    adjlist[i] = (int*)malloc(num_players * sizeof(int));
    if (adjlist[i] == NULL){
        printf("malloc failed");
    }
}

//Populates adjacency matrix based on found distance
for (int i = 0; i < num_players; i++){
    int curr_x = n[i].x;
    int curr_y = n[i].y;
    for (int j = 0; j < (num_players); j++){
        if (i == j){
            adjlist[i][j] = 0;
        }
        else{
            double distance = sqrt((pow((curr_x-n[j].x), 2)+pow((curr_y-n[j].y), 2)));
            if (distance <=  jump_range){
                adjlist[i][j] = 1;
            }
            else{
                adjlist[i][j] = 0;
            }
        }
    }
}

//Storing adjacency matrix list size in each node
for (int i = 0; i < num_players; i++) {
    n[i].adj_size = 0;
    for (int j = 0; j < num_players; j++) {
        if (adjlist[i][j] > 0) {
            n[i].adj_size++;
        }
    }
}

//malloc the adjacency lists for each node
for (int i = 0; i < num_players; i++) {
    n[i].adj = (struct node**)malloc(n[i].adj_size * sizeof(struct node*));
    if (n[i].adj == NULL) {
        printf("malloc failed");
    }
}

//Populates adjacency lists on each node
for (int i = 0; i < num_players; i++) {
    int index = 0;
    for (int j = 0; j < num_players; j++) {
        if (adjlist[i][j] > 0) {
            n[i].adj[index++] = &n[j];
        }
    }
}

//Allocating memory for best paths
current_path = malloc(num_jumps * sizeof(int));
best_path = malloc(num_jumps * sizeof(int));
best_path_healing = (int*)malloc(num_jumps * sizeof(int));


//Call dfs on first node
dfs(n, 0, num_jumps, 1);

//Run dfs on all nodes in initial range
for(int i = 1;i < (num_players); i++){
    double distance = sqrt((pow((n[0].x-n[i].x), 2)+pow((n[0].y-n[i].y), 2)));
    if (distance <= initial_range){
        dfs(n, i, num_jumps, 1);
    }
}

//Prints best path from dfs and total healing
for (int i = 0; i < best_path_length; i++) {
    printf("%s %d\n", n[best_path[i]].name, best_path_healing[i]);
}
printf("Total_Healing %d\n", best_healing);

//Freeing memory
free(current_path);
free(best_path);
free(best_path_healing);
for (int i = 0; i < num_players; i++){
    free(n[i].adj);
    free(adjlist[i]);
}
free(adjlist);
free(n);
    
return 0;
}