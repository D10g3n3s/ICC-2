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
|    |   Programa que realiza a ordenação de nomes com   |    |
|    |                   cocktail sort                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct PERSON_DATA{
    char *city;
    char *name;
} PERSON_DATA;

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

//Function that found the first occurrence of a given char
int findOccurrence(char *str, char c){
    int i;

    for (i = 0; i < strlen(str); i++){
        if (str[i] == c) return i + 1;
    }

    return -1;
}

//Function that divides the information of the people and saves it on the struct
void createPeopleData(PERSON_DATA **people, int name_number){
    char** information = NULL;
    information = (char**) calloc (name_number, sizeof(char*));

    //Reading the information and saving on the struct
    for (int i = 0; i < name_number; i++){
        information[i] = readLine(stdin);

        //Saving the informations in the struct
        int len = findOccurrence(information[i], '.') + 1;
        if (len != -1){
            people[i]->name = calloc (len, sizeof(char));
            strncpy(people[i]->name, information[i], len-1);
            people[i]->name[len] = '\0';

            int l = strlen(information[i]) - len + 1;
            people[i]->city = calloc (l, sizeof(char));
            strncpy(people[i]->city, information[i] + len, l);
        }
    }

    //Deallocating the heap memory of the string matrix
    for (int i = 0; i < name_number; i++){
        free(information[i]);
    }
    free(information);
}

//Function that ordenates the struct, with cocktail sort, in alphabetic order
void sortingPeopleData(PERSON_DATA **people, int name_number){
    boolean ordenated = FALSE;
    PERSON_DATA *temp;

    //Sorting
    while (!ordenated){
        ordenated = TRUE;

        for (int i = 0; i < name_number - 1; i++){
            if (strcasecmp(people[i]->name, people[i+1]->name) > 0){
                temp = people[i];
                people[i] = people[i+1];
                people[i+1] = temp;

                ordenated = FALSE;
            }
        }

        for (int i = name_number - 1; i > 0; i--){
            if (strcasecmp(people[i-1]->name, people[i]->name) > 0){
                temp = people[i-1];
                people[i-1] = people[i];
                people[i] = temp;
                
                ordenated = FALSE;
            }
        }
    }
}

//Function that does binary search
int stringBinarySearch(PERSON_DATA **people, int lo, int hi, char *key){
    if (hi >= lo) {
        int mid = lo + (hi - lo) / 2;

        //If key is the mid element
        if (!strcasecmp(people[mid]->name, key)) return mid; 

        //Checks if the key is behind the mid element, if so, we search in the left part
        if (strcasecmp(people[mid]->name, key) > 0) return stringBinarySearch(people, lo, mid - 1, key); 
  
        //The element must be in the right part so cheking there
        return stringBinarySearch(people, mid + 1, hi, key); 
    }

    //Returning an error code if the elements isn't found
    return -1; 
}

int main(){
    int name_number;
    char *numbers = NULL;
    
    //Discovering how many names we'll read
    numbers = readLine(stdin);
    name_number = atoi(numbers);
    free(numbers);

    //Allocating the struct of the people
    PERSON_DATA **people;
    people = (PERSON_DATA**) calloc (name_number, sizeof(PERSON_DATA*));
    for (int i = 0; i < name_number; i++){
        people[i] = (PERSON_DATA*) calloc (1, sizeof(PERSON_DATA));
        people[i]->city = NULL;
        people[i]->name = NULL;
    }

    //Creating a struct to save the names then sorting it
    createPeopleData(people, name_number);
    sortingPeopleData(people, name_number);

    //Dicovering how many names we'll search among all possibles
    int search_number;
    numbers = readLine(stdin);
    search_number = atoi(numbers);
    free(numbers);

    //Creating and array to save if the name search is or not from São Carlos
    int *is_san_charles;
    is_san_charles = (int*) calloc (search_number, sizeof(int));

    //Searching the names
    for (int i = 0; i < search_number; i++){
        int test;

        //Discovering the name to be search
        char *searching_word;
        searching_word = readLine(stdin);

        //Checking if the searched name is a São Carlense
        test = stringBinarySearch(people, 0, name_number - 1, searching_word);

        if (test != -1){
            if (!strcasecmp(people[test]->city, "Sao Carlos.")) is_san_charles[i] = 1;
            else is_san_charles[i] = 0;
        }
        else
            is_san_charles[i] = 0;

        free(searching_word);
    }

    //Printing the awnsers
    for (int i = 0; i < name_number; i++){
        printf("%s\n", people[i]->name);
    }

    for (int i = 0; i < search_number; i++){
        printf("%d\n", is_san_charles[i]);
    }

    //Deallocating the heap memory
    for (int i = 0; i < name_number; i++){
        free(people[i]->city);
        free(people[i]->name);
        free(people[i]);
    }
    free(people);
    free(is_san_charles);

    return 0;
}