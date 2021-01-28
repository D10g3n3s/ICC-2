#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Function that reads only one word ignoring special characters
char* readWord(FILE *input){
    char *str;

    //Fazendo a alocação inicial
    str = (char*) malloc(32 * sizeof(char)); 

    int pos = 0, tamanho = 32;
    
    do {
        //Reallocando o tamanho da memória heap in caso da palavra exceder o tamanho limite
        if (pos == tamanho) {
            str = realloc(str, 2 * tamanho);
            tamanho *= 2;
        }

        //Lendo os caracteres
        str[pos] = (char) fgetc(input);
        pos++;
        if (str[pos - 1] == '\n' || str[pos - 1] == ' ' || !isalpha(str[pos - 1])) break;
        else if (str[pos - 1] == '\r') pos--;

    } while (!feof(input));

    str[pos - 1] = '\0';
    str = realloc(str, pos);
    
    return str;
}