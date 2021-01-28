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
|    |                      P1 ICC2                      |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function that creates a callocated matrix
double** createMatrix(int size){
    double **matrix;

    //Allocating the matrix in the heap memory
    matrix = calloc (size, sizeof(double));
    for (int i = 0; i < size; i++){
        matrix[i] = calloc (size, sizeof(double));
    }

    return matrix;
}

//Function that generates the values of a matrix
void generateMatrix(double **matrix, int size, double sum){
    double realsum = 0;

    for (int i = 0; i < size; i++){
        sum = 0;
        for (int j = 0; j < size; j++){
            if (i == j){                        //c
                matrix[i][j] = realsum;         
            }
            else if(i < j){                     //c
                matrix[i][j] = (i + j) / 4.0;   //2a
            }
            else
                matrix[i][j] = (i + j) / 2.0;   //2a
            
            sum += matrix[i][j];                //a
        }
        realsum = sum;
    }
}

int main (){
    int n;

    //Reading the size of the matrix
    scanf("%d", &n);

    //Creating the matrix
    double **matrix;
    matrix = createMatrix(n);

    //Generating the values of the matrix
    generateMatrix(matrix, n, 0);

    //Printing the last line
    for (int i = 0; i < n; i++){
        printf("%.2lf ", matrix[n-1][i]);
    }
    printf("\n");

    //Deallocating the heap memory
    for (int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}