//Peter Hoffman
//CS360 Lab1
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

int initial_range, jump_range, num_jumps, initial_power, num_players, individual_healing;
double power_reduction;

int total_healing = 0;
int best_healing = 0;
double current_healing = 0;

int* current_path;
int* best_path;
int* best_path_healing;
int best_path_length;

void dfs(Node nodes[], int start, int max_hops, int hop_num){
    if (hop_num > max_hops || nodes[start].visited){
        return;
    }

    nodes[start].visited = true;
    current_healing = initial_power * pow(1-power_reduction, hop_num-1);
    if ((nodes[start].max_pp-nodes[start].curr_pp) > current_healing){
        individual_healing = rint(current_healing);
    }
    else{
        individual_healing = (nodes[start].max_pp-nodes[start].curr_pp);
    }

    nodes[start].healing = individual_healing;
    //printf("%s Hop: %d Healing: %d\n", nodes[start].name, hop_num, nodes[start].healing);

    current_path[hop_num - 1] = start;
    //best_path_healing[hop_num-1] = individual_healing;

    //if (hop_num == max_hops) {
        int total_healing = 0;
        for (int i = 0; i < hop_num; i++) {
            //best_path_healing[i] = nodes[current_path[i]].healing;
            //total_healing += best_path_healing[i];
            // printf("Current path #%d: %s +%d\n", i, nodes[current_path[i]].name, nodes[current_path[i]].healing);
            total_healing += nodes[current_path[i]].healing;
            //best_path_healing[i] = nodes[current_path[i]].healing;
        }
        //list not being populated correctly
        //keep track of best path length
        //best healing is correct
        if (total_healing > best_healing) {
            // printf("Best: %d, Current: %d\n", best_healing, total_healing);
            best_healing = total_healing;


            for (int i = 0; i < hop_num; i++) {
                best_path[i] = current_path[i];
                best_path_healing[i] = nodes[current_path[i]].healing;
            }
            best_path_length = hop_num;
        }
    //}

    for (int i = 0; i < nodes[start].adj_size; i++){
        int adjacentIndex = nodes[start].adj[i] - nodes;

        dfs(nodes, adjacentIndex, max_hops, hop_num+1);
    }
    nodes[start].visited = false;
}

int main(int argc, char *argv[]) {

Node *n;

//storing command line args
if (argc >= 5){
initial_range = atoi(argv[1]);      //string to int using atoi
jump_range = atoi(argv[2]);
num_jumps = atoi(argv[3]);
initial_power = atoi(argv[4]);
power_reduction = atof(argv[5]);    //string to double using atof
}
else{
    printf("bad usage");
}

//for counting lines in input
num_players = 0;
char c;

//read file to get num players from newline
do{
    c = getchar();
    if (c == '\n'){
        ++num_players;
    }
} while (c != EOF);

/*
//testing print lines
printf("initial range: %d\n", initial_range);
printf("jump range: %d\n", jump_range);
printf("num jumps: %d\n", num_jumps);
printf("initial power: %d\n", initial_power);
printf("power reduction: %lf\n", power_reduction);
printf("num players: %d\n", num_players);
*/

//malloc structs based on # of newline chars
n = (Node *) malloc(sizeof(Node)*num_players);
if (n == NULL){
    printf("malloc failed\n");
    return 1;
}

//storing node data
rewind(stdin);
for (int i = 0; i<num_players; i++){
    if (fscanf(stdin, "%d %d %d %d %99s", &n[i].x, &n[i].y, &n[i].curr_pp, &n[i].max_pp, n[i].name)== 5){
    }
    else{
        printf("error reading data\n");
        free(n);
        return 1;
    }
}

/*
//testing print lines
for (int i = 0; i < num_players; i++){
printf("%d ", n[i].x);
printf("%d ", n[i].y);
printf("%d ", n[i].curr_pp);
printf("%d ", n[i].max_pp);
printf("%s\n", n[i].name);
}
*/


//creating adjlist rows
int** adjlist = (int**)malloc(num_players * sizeof(int*));
if (adjlist == NULL){
    printf("malloc failed");
}
//creating adjlist cols
for(int i = 0; i < num_players; i++){
    adjlist[i] = (int*)malloc(num_players * sizeof(int));
    if (adjlist[i] == NULL){
        printf("malloc failed");
    }
}
//populates adjlist based on found distance
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

for (int i = 0; i < num_players; i++) {
    n[i].adj_size = 0;
    for (int j = 0; j < num_players; j++) {
        if (adjlist[i][j] > 0) {
            n[i].adj_size++;
        }
    }
}

//allocate the adjacency lists
for (int i = 0; i < num_players; i++) {
    n[i].adj = (struct node**)malloc(n[i].adj_size * sizeof(struct node*));
    if (n[i].adj == NULL) {
        printf("malloc failed");
    }
}

//adding nodes onto their adjacency lists
for (int i = 0; i < num_players; i++) {
    int index = 0;
    for (int j = 0; j < num_players; j++) {
        if (adjlist[i][j] > 0) {
            n[i].adj[index++] = &n[j];
        }
    }
}


/*
//prints adjlist
for (int j = 0; j < num_players; j++){
    for (int i = 0; i < num_players; i++){
        printf(" %d ", n[i].adj[j]);
    }
    printf("\n");
}
*/

//allocating mem for best paths
    current_path = malloc(num_jumps * sizeof(int));
    best_path = malloc(num_jumps * sizeof(int));
    best_path_healing = (int*)malloc(num_jumps * sizeof(int));


// call dfs
dfs(n, 0, num_jumps, 1);

//run dfs on nodes in initial range
for(int i = 1;i < (num_players); i++){
    double distance = sqrt((pow((n[0].x-n[i].x), 2)+pow((n[0].y-n[i].y), 2)));
    if (distance <= initial_range){
//        best_healing = 0;
        dfs(n, i, num_jumps, 1);
    }
}

//best_healing = 0;
//printf("best path:\n");

for (int i = 0; i < best_path_length; i++) {
    printf("%s %d\n", n[best_path[i]].name, best_path_healing[i]);
    //best_healing += n[best_path[i]].healing;
}
printf("Total_Healing %d\n", best_healing);


//freeing memory
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