/*
 _____________________________________________________________
|     ___________________________________________________     |
|    |             Universidade de São Paulo             |    |
|    |                                                   |    |
|    | Instituto de Ciências Matemáticas e de Computação |    |
|    |                                                   |    |
|    |           Diógenes Silva Pedro BCC 020            |    |
|    |                                                   |    |
|    |                  nUSP: 11883476                   |    |
|    |                                                   |    |
|    |               diogenes.pedro@usp.br               |    |
|    |                                                   |    |
|    |            diogenes.pedro60@gmail.com             |    |
|    |                                                   |    |
|    |                                                   |    |
|    |         Code that recursive solves a maze         |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

//Function that reads a string of undefined size and allocates the exact size of heap memory 
char* readLine(FILE* input){
    char *str;

    str = (char*) malloc (32 * sizeof(char)); //Doing inicial allocation

    int pos = 0, tamanho = 32;
    
    do {
        //Reallocating the heap memory in case the word exceds the limit
        if (pos == tamanho) {
            str = realloc (str, 2 * tamanho);
            tamanho *= 2;
        }

        //Getting the chars
        str[pos] = (char) fgetc(input);
        if (str[pos] == '\r') pos--;
        pos++;

    } while (str[pos-1] != '\n' && !feof(input));

    str[pos-1] = '\0'; 
    str = realloc(str, pos);
    
    return str;
}

//Function that reads the size of the maze
void readMazeInfo(int *height, int *length, int *initial_x, int *initial_y, FILE *archive){
    //Reading the matrix size and the initial positions
    fscanf(archive, "%d %d %d %d", &(*height), &(*length), &(*initial_x), &(*initial_y));
}

//Function that reads and create a matrix of the maze
char** readMaze(char **maze, int height, int length, FILE *archive, int *people, int *ways){
    //Alocatting the heap memory for the maze
    maze = (char**) calloc (height, sizeof(char*));
    for (int i = 0; i < height; i++){
        maze[i] = (char*) calloc (length, sizeof(char));
    }

    //Reading the maze
    for (int i = 0; i < height; i++){
        for (int j = 0; j < length; j++){
            char c;
            fscanf(archive, "%c", &c);
            if (c != '\n'){
                maze[i][j] = c;
                if (c == '#') (*people)++;
                else if (c == '.') (*ways)++;
            }
            else j--;
        }
    }

    return maze;
}

//Function that walks through the maze
int walkMaze(char **maze, int height, int length, int x, int y){
    // If x,y is the goal, return true.
    if (x < 0 || x > (height - 1) || y < 0 || y > (length - 1)) return TRUE;

    // If x,y is not open, return false.
    if (maze[x][y] != '.') return FALSE;

    // Mark x,y part of solution path.
    maze[x][y] = '*';

    //Looking up
    if (walkMaze(maze, height, length, x-1, y) == TRUE) return TRUE;

    //Looking right
    if (walkMaze(maze, height, length, x, y+1) == TRUE) return TRUE;

    //Looking down
    if (walkMaze(maze, height, length, x+1, y) == TRUE) return TRUE;

    //Looking left
    if (walkMaze(maze, height, length, x, y-1) == TRUE) return TRUE;

    return FALSE;
}

//Function that discover how much of the maze were explored
void visitedWays(char **maze, int *traveled, double *explored, int height, int length, int ways){
    //Discovering how much ways we traveled
    for (int i = 0; i < height; i++){
        for (int j = 0; j < length; j++){
            if (maze[i][j] == '*') (*traveled)++;
        }
    }

    *explored = floor(100 * (double) (*traveled)/ways);
}

//Function that prints out a maze
void printMaze(char **maze, int height, int length){
    //Printing the maze after the solve
    for (int i = 0; i < height; i++){
        for (int j = 0; j < length; j++){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Function that prints out infos about the maze
void printMazeInfo(int people_number, int ways, int visited_ways, double explored, int solved){
    if(solved) printf("Voce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", people_number);
    printf("----Numero total de caminhos validos:   %d\n", ways);
    printf("----Numero total de caminhos visitados: %d\n", visited_ways);
    printf("----Exploracao total do labirinto: %.1lf%%\n", explored);
}   

int main(){
    char *filename = NULL;

    //Reading the name of the archive
    filename = readLine(stdin);

    //Creating a file pointer to open the archive
    FILE* archive;
    archive = fopen(filename, "r");

    //Testando o erro de arquivo inexistente
    if (archive == NULL){
        printf("Não possível abrir o arquivo\n");
    }

    //Variables for the maze
    int height, length, initial_x, initial_y;

    //Reading infos of the maze
    readMazeInfo(&height, &length, &initial_x, &initial_y, archive);

    //Creating the maze and reading it
    char **maze = NULL;
    int people_number = 0, ways = 0;
    maze = readMaze(maze, height, length, archive, &people_number, &ways);
    
    //Closing the archive after use
    fclose(archive);

    //Variables for maze info
    int visited_ways = 0;
    double explored;
    int solved = FALSE;

    //Walking through the maze
    solved = walkMaze(maze, height, length, initial_x, initial_y);

    //Discovering how many ways were visited
    visitedWays(maze, &visited_ways, &explored, height, length, ways);
    
    //Printing the maze
    printMaze(maze, height, length);
    
    //Printing the result
    printMazeInfo(people_number, ways, visited_ways, explored, solved);
    
    //Deallocating the heap memoty
    for(int i = 0; i < height; i++){
        free(maze[i]);
    }
    free(maze);
    free(filename);

    return 0;
}