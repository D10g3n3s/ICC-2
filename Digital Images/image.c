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
|    |          Code that creates digital images         |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _image {
    int **matrix;
    int size;
    int seed;
    int x;
    int y;
} IMAGE;

//Function that creates and image
void createPgm(IMAGE *image, char *filename) {
    FILE *pgmimg = fopen(filename, "wb");

    fprintf(pgmimg, "P2\n");
    fprintf(pgmimg, "%d %d\n", image->size, image->size);
    fprintf(pgmimg, "255\n");
    
    for (int i = 0; i < image->size; i++){
        for (int j = 0; j < image->size; j++){
            fprintf(pgmimg, "%d ", image->matrix[i][j]);
        }

        fprintf(pgmimg, "\n");
    }

    fclose(pgmimg);
}

//Function that changes the image matrix
void changeMatrix(IMAGE *image, int x, int y, int p){
    int v, m;
    
    //Checking if the actual position is out of the matrix
    if (x < 0 || x > (image->size - 1) || y < 0 || y > (image->size - 1)) 
        return;

    //For the first recursive call the program doesn't calculate the next and the prev
    if (p == 1337);
    
    //Checking the necessity of changing the image
    else{
        v = image->matrix[x][y];
        
        m = p - v;
        if (m < 0)
            m*=(-1);

        if (m == 0)
            return;

        if (m <= image->seed)
            image->matrix[x][y] = p;

        if (m > image->seed)
            return;
    }

    //Upwards
    changeMatrix(image, x - 1, y, image->matrix[x][y]);
    
    //Going right
    changeMatrix(image, x, y + 1, image->matrix[x][y]);
    
    //Downwards
    changeMatrix(image, x + 1, y, image->matrix[x][y]);
    
    //Going left
    changeMatrix(image, x, y - 1, image->matrix[x][y]);
}

//Function that prints a matrix
void printMatrix(IMAGE *image){
    for (int i = 0; i < image->size; i++){
        for (int j = 0; j < image->size; j++){
            printf("%d\t", image->matrix[i][j]);
        }
        printf("\n");
    }    
}

//Function that creates and image
int** createMatrix(IMAGE *image){
    //Allocating the heap memory
    int **matrix = malloc(image->size * sizeof(int*));
    for (int i = 0; i < image->size; i++){
        matrix[i] = malloc(image->size * sizeof(int));
    }

    //Setting the seed to the rand function
    srand(image->seed);

    //Reading the image matrix
    for (int i = 0; i < image->size; i++){
        for (int j = 0; j < image->size; j++){
            matrix[i][j] = rand() % 256;
        }
    }

    return matrix;
}

//Function that saves the informations about the image in the struct
void startImage(IMAGE *image){
    scanf("%d %d %d %d", &image->size, &image->x, &image->y, &image->seed);

    //Creating the image matrix
    image->matrix = createMatrix(image);

    //Printing the matrix before the change
    printMatrix(image);

    //Creating the image before the change of the image
    #ifdef DEBUG
        createPgm(image, "beforechange.pgm");
    #endif

    //Chaging the image
    changeMatrix(image, image->x, image->y, 1337);

    //Printing the matrix after the change
    printf("\n");
    printMatrix(image);   
    
    //Creating the image after the change of the image
    #ifdef DEBUG
        createPgm(image, "afterchange.pgm");
    #endif
}

int main(){
    IMAGE *image = malloc(sizeof(IMAGE));

    startImage(image); 

    //Deallocating the heap memory
    for (int i = 0; i < image->size; i++){
        free(image->matrix[i]);
    }
    free(image->matrix);
    free(image);

    return 0;
}