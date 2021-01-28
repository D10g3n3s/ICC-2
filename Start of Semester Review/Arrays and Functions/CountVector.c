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
|    |           Revisão de Vetores e Funções            |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;

//Function that creates a number vector
int* createNumberVector(int *vec, int *len){
    while(!feof(stdin)){
        vec = realloc (vec, (*len+1) * sizeof(int*));
        scanf("%d", &vec[*len]);
        (*len)++;
    }

    return vec;
}

//Function that creates a vector with no repeated ellements based on other vector given
int* uniqueVector (int *baseVector, int *numbers, int *newLen, int howManyNumbers){
    int isDefined = FALSE;
    int numberPos = 0;
    int newVectorLen = 0;
    int baseNumber = 0;

    numbers = malloc (1 * sizeof(int));

    for (int i = 0; i < howManyNumbers; i++){
        baseNumber = baseVector[i];
        for (int j = 0; j < newVectorLen; j++){
            if (baseNumber == numbers[j]){
                isDefined = TRUE;
            }
        }

        if (!isDefined){
            numbers = realloc (numbers, (newVectorLen+1) * sizeof(int));
            numbers[numberPos] = baseNumber;
            newVectorLen++;
            numberPos++;
        }
        else if (isDefined){
            isDefined = FALSE;
        } 
            
    }  

    //Saving the length of the new vector by reference
    *newLen = newVectorLen;

    return numbers;
}

//Function that calculates the frequency of elements
int* calculateFrequency(int *baseVector, int *frequency, int *numbers, int count, int howManyNums){
    int baseNumber = 0;

    frequency = calloc (count, sizeof(int));

    for (int i = 0; i < count; i++){
        baseNumber = numbers[i];
        for (int j = 0; j < howManyNums; j++){
            if (baseNumber == baseVector[j]){
                frequency[i]++;
            }
        }  
    }

    return frequency;
}

//Function that shows the results
void printResult(int *numbers, int *frequency, int count){
    for (int i = 0; i < count; i++){
        printf("%d (%d)\n", numbers[i], frequency[i]);
    }
}

int main(){

    int *number_vector = NULL;
    int *unique_vector = NULL;
    int *frequency = NULL;
    int len = 0, unique_vec_len = 0;

    number_vector = createNumberVector(number_vector, &len);

    unique_vector = uniqueVector(number_vector, unique_vector, &unique_vec_len, len);

    frequency = calculateFrequency(number_vector, frequency, unique_vector, unique_vec_len, len);

    printResult(unique_vector, frequency, unique_vec_len);

    free(number_vector);
    free(unique_vector);
    free(frequency);

    return 0;
}