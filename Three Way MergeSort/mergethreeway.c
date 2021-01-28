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
|    |         Exercise that mergesort in 3 ways         |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WAYS 3

typedef struct _books{
    char *name;
    float price;
} BOOKS;

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

//Function that reads and save in the book struct the name and the price of a book, for all books
void createBooksData(BOOKS **books, int nBooks){
    //Allocating a string matrix to auxiliate on the read
    char **data;
    data = (char**) calloc (nBooks, sizeof(char*));

    //Reading the data of the books and saving in the struct
    for (int i = 0; i < nBooks; i++){
        data[i] = readLine(stdin);

        books[i]->name = (char*) calloc (strlen(data[i]) + 3, sizeof(char));

        char *price = NULL;
        price = index(data[i], ',');
        
        books[i]->price = atof(price + 2);

        int priceLen = strlen(price + 2);
        int textLen = (strlen(data[i]) - priceLen);

        strncpy(books[i]->name, data[i], textLen);
        strcat(books[i]->name, "R$");
        strncat(books[i]->name, data[i] + textLen, priceLen);
    }

    //Deallocating the auxiliar string matrix
    for (int i = 0; i < nBooks; i++){
        free(data[i]);
    }
    free(data);
}

//Function that checks for the lower value and returns it
int min(const int a, const int b){
    return a < b? a : b;
}

//Auxiliar function to the mergesort
void threeWayMerge(BOOKS **books, int start, int firstDiv, int secDiv, int end){
    BOOKS **merged_arr = (BOOKS**) calloc (((end - start) + 1), sizeof(BOOKS*));

    int i = start; //Index of the first part
    int j = start + firstDiv + 1; //Index of the second part 
    int k = start + secDiv + 1; //Index of the third part
    int l = 0; //Index of the merged array part

    //Merging the ordenated list in the merged array
    while (i <= start + firstDiv && j <= start + secDiv && k <= end){
        if (books[i]->price <= books[j]->price){
            if (books[i]->price <= books[k]->price){
                merged_arr[l] = books[i];
                i++;
            }
            else {
                merged_arr[l] = books[k];
                k++;
            }
        }   
        else {
            if (books[j]->price <= books[k]->price){
                merged_arr[l] = books[j];
                j++;
            }
            else {
                merged_arr[l] = books[k];
                k++;
            }
        }
        l++;
    }

    //Checking if the first and second arrays still have remaning values
    while (i <= start + firstDiv && j <= start + secDiv){
        if (books[i]->price <= books[j]->price){
            merged_arr[l] = books[i];
            i++;
        }
        else {
            merged_arr[l] = books[j];
            j++;
        }
        l++;
    }

    //Checking if the second and thrid arrays still have remaning values
    while (j <= start + secDiv && k <= end){
        if (books[j]->price <= books[k]->price){
            merged_arr[l] = books[j];
            j++;
        }
        else {
            merged_arr[l] = books[k];
            k++;
        }
        l++;
    }

    //Checking if the first and thrid arrays still have remaning values
    while (i <= start + firstDiv && k <= end){
        if (books[i]->price <= books[k]->price){
            merged_arr[l] = books[i];
            i++;
        }
        else {
            merged_arr[l] = books[k];
            k++;
        }
        l++;
    }

    //Checking if there's still remaining values in any of the arrays
    while (i <= start + firstDiv){
        merged_arr[l] = books[i];
        i++;
        l++;
    }

    while (j <= start + secDiv){
        merged_arr[l] = books[j];
        j++;
        l++;
    }

    while (k <= end){
        merged_arr[l] = books[k];
        k++;
        l++;
    }

    //Copying the auxiliar array to the original array
    for (int i = start, l = 0; i <= end; i++, l++){
        books[i] = merged_arr[l]; 
    }

    //Deallocating the auxiliar heap memory used
    free(merged_arr);
}

//Function that mergesort in three ways
void sortBooksData(BOOKS **books, int start, int end){
    for (int i = start; i <= end; i++){
        printf ("%.2f ", books[i]->price);
        if (i == end) printf("\n");
    }
    
    //Base case, checks if the array has size of 1
    if (end <= start) return;

    int len = end - start + 1;

    int firstDiv = (len / WAYS) + min(len % WAYS, 1) - 1;
    int secDiv = 2 * (len / WAYS) + min(len % WAYS, 2) - 1;

    //Divide
    sortBooksData(books, start, start + firstDiv);
    sortBooksData(books, start + firstDiv + 1, start + secDiv);
    sortBooksData(books, start + secDiv + 1, end);

    //Conquer - Merge
    threeWayMerge(books, start, firstDiv, secDiv, end);
}

int main(){
    int nBooks;
    char *number;

    //Discovering the amount of books
    number = readLine(stdin);
    nBooks = atoi(number);
    free(number);

    //Allocating the structure of books
    BOOKS **books;
    books = (BOOKS**) calloc (nBooks, sizeof(BOOKS*));
    for (int i = 0; i < nBooks; i++){
        books[i] = (BOOKS*) calloc (1, sizeof(BOOKS));
        books[i]->name = NULL;
    }

    //Reading and saving the infos os the books
    createBooksData(books, nBooks);

    //Sorting the books by the price
    sortBooksData(books, 0, nBooks - 1);
    printf("\n");

    //Printing the books in order after the sort
    for (int i = 0; i < nBooks; i++){
        printf("%s\n", books[i]->name);
    }

    //Deallocating the heap memory
    for (int i = 0; i < nBooks; i++){
        free(books[i]->name);
        free(books[i]);
    }
    free(books);

    return 0;
}