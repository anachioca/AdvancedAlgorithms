#include <iostream>
#include <vector>
using namespace std;

/*
This algorithm counts all possible solutions for the "rat in a maze" problem, using backtracking.
*/

//checks if the position is valid
int isValid(int x, int y, int N){
    if (x < 0 || y < 0 || y >= N || x >= N) return 0;
    return 1;
}

void BackTracking(int** maze, int x, int y, int* solutions, int N){

    // if the rat has reached the cheese, increment the number of solutions!
    if (x == N-1 && y == N-1){
        *solutions = *solutions + 1;
        //printf("solutions: %d\n", *solutions);
        return;
    }

    // if the rat hits a wall or a cell that has already been visited, returns.
    if (maze[x][y] == 1 || maze[x][y] == 2) return;

    maze[x][y] = 2; //marks cell as visited

    // explore all directions that are valid (not a wall and a valid position in the matrix)
    if (isValid(x+1, y, N))
        BackTracking(maze, x+1, y, solutions, N);
    
    if (isValid(x, y+1, N))
        BackTracking(maze, x, y+1, solutions, N);

    if (isValid(x-1, y, N))
        BackTracking(maze, x-1, y, solutions, N);

    if (isValid(x, y-1, N))
        BackTracking(maze, x, y-1, solutions, N);
    
    maze[x][y] = 0; //marks cell as not visited.
}

int main(){
    int N;
    int solutions = 0;
    scanf("%d", &N);
    int **maze = (int**)malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++){
        maze[i] = (int*)malloc(N*sizeof(int));
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            scanf("%d", &maze[i][j]);
        }
    }

    BackTracking(maze, 0, 0, &solutions, N);
    printf("%d", solutions);

    return 0;
}