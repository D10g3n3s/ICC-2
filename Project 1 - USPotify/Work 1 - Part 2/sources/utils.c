#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que le uma string de tamanho indefinido e alloca o tamanho exato na memória heap
char* readLine(FILE* input){
    char *str;

    // Fazendo a alocação inicial
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
        if (str[pos] == '\r') pos--;
        pos++;

    } while (str[pos-1] != '\n' && !feof(input));

    str[pos-1] = '\0'; 
    str = realloc(str, pos);
    
    return str;
}