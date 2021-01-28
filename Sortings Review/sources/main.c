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
|    |       Code for test with sorting algorithms       |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <sortings.h>

char* randomString(int length){
    char *alphanum = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    char *string = calloc((length + 1), sizeof(char));

    for (int i = 0; i < length; i++)
        string[i] = alphanum[rand() % 52];

    string[length] = '\0';

    return string;
}

RECORD* createRandRecords(int length){
    RECORD* newRecord = malloc (length * sizeof(RECORD));

    for (int i = 0; i < length; i++){
        newRecord[i].key = rand() % 50;
        newRecord[i].string = randomString(newRecord[i].key);
    }

    return newRecord;
}

int* createRandArray(int length){
    int *newArray = malloc(length * sizeof(int));

    for (int i = 0; i < length; i++){
        newArray[i] = rand() % 200;
    }

    return newArray;
}

void printRecordArray(RECORD *records, int length){
    for (int i = 0; i < length; i++){
        printf("%d ", records[i].key);
        printf("'%s'\n", records[i].string);
    }
    printf("\n");
}

void printArray(int *array, int length){
    for (int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void deallocateRecords(RECORD *records, int length){
    for (int i = 0; i < length; i++){
        free(records[i].string);
    }
    free(records);
}

int main (){
    int arr_size;
    scanf("%d", &arr_size);

    RECORD *records = createRandRecords(arr_size);

    printRecordArray(records, arr_size);

    int *arr = createRandArray(arr_size);
    printArray(arr, arr_size);
    printf("Now sorting the array...\n");
    printArray(arr, arr_size);

    // printRecordArray(records, arr_size);

    free(arr);
    deallocateRecords(records, arr_size);

    return 0;
}