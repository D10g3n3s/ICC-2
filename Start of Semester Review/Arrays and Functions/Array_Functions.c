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
#include <string.h>

#define TRUE 1;
#define FALSE 0;

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

//Function that creates a vector of the inputs
int* createVector (int *baseVector, int *howManyNumbers){
    char *dataInput = NULL;
    char **separatedString = NULL;
    int count = 0, nullStringCount = 0;
    char *str = NULL;

    dataInput = readLine(stdin);
    
    char *p = dataInput;  

    ///Separating with the space delimitador    
    while ((str = strsep(&p, " ")) != NULL){
        separatedString = realloc (separatedString, (count+1) * sizeof(char*));
        separatedString[count] = strdup(str);
        if (strcmp(separatedString[count], "")) count++;
        else free(separatedString[count]);
    }

    //Allocating the vector size and giving it his values
    baseVector = (int*) calloc (count, sizeof(int));
    for (int i = 0; i < count; i++){
        baseVector[i] = atoi(separatedString[i]);
    }

    //Saving the length of the vector
    *howManyNumbers = count;

    //Deallocating the heap memoty used
    free(dataInput);
    free(str);
    for (int i = 0; i < count + nullStringCount; i++){
        free(separatedString[i]);
    }
    free(separatedString);

    return baseVector;
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
    int *numbers = NULL;
    int *frequency = NULL;
    int *baseVector = NULL;
    int howManyNumbers = 0;
    int newLen = 0;

    //Calling the function that creates the vector of integers but with repetition
    baseVector = createVector(baseVector, &howManyNumbers);

    //Calling the function to create the vector without repeated ellements
    numbers = uniqueVector(baseVector, numbers, &newLen, howManyNumbers);

    //Calling the function that calculates the frequency
    frequency = calculateFrequency(baseVector, frequency, numbers, newLen, howManyNumbers);

    //Calling the function that show the user the results
    printResult(numbers, frequency, newLen);

    //Dealocating the HEAP memory used
    free(numbers);
    free(frequency);
    free(baseVector);

    return 0;
}