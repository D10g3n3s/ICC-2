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
|    |         C program for studying hash code          |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function that reads a string of undefined size and allocates the exact size of heap memory 
char* readLine(FILE* input){
    char *str;

    str = (char*) malloc (32 * sizeof(char)); //Doing inicial allocation

    int pos = 0, tamanho = 32;
    
    do {
        // Reallocating the heap memory in case the word exceds the limit
        if (pos == tamanho) {
            str = realloc (str, 2 * tamanho);
            tamanho *= 2;
        }

        // Getting the chars
        str[pos] = (char) fgetc(input);
        if (str[pos] == '\r') pos--;
        pos++;

    } while (str[pos-1] != '\n' && !feof(input));

    str[pos-1] = '\0'; 
    str = realloc(str, pos);
    
    return str;
}

// Function that creates a vector of struct with the info of the name of the student and the value
char** discoverStudent(int length){
    char **discovered = malloc(length * sizeof(char*));

    for (int i = 0; i < length; i++){
        discovered[i] = readLine(stdin);
    }

    return discovered;
}

// Function that deallocates the vector of structs
void deallocateStudent(char **students, int length){
    for (int i = 0; i < length; i++){
        free(students[i]);
    }
    free(students);
}

typedef struct _hash {
    char **table;
    int length;
} HASH;

// Function that creates the hash struct
HASH* createHash(int length){
    HASH *newHash = calloc(1, sizeof(HASH));
    newHash->table = calloc(length, sizeof(char*));
    newHash->length = length;

    return newHash;
}

// Function that sets the hash function
int hashFunction(char *key, int length){
    int keyValue = 0;
    for (int i = 0; key[i] != '\0'; i++){
        keyValue += (int) key[i];
    }

    return keyValue % length;
}

// Function that inserts into the hash table
void insertHash(HASH *hash, char *student){
    int pos = hashFunction(student, hash->length);
    
    for (int i = 0; i < hash->length; i++){
        if (hash->table[pos] == NULL){
            hash->table[pos] = student;
            break;
        }
        
        pos = (pos + 1) % hash->length;
    }
}

// Function that deletes from the hash table
void removeFromHash(HASH *hash, char *student){
    int pos = hashFunction(student, hash->length);
    
    for (int i = 0; i < hash->length; i++){
        if (hash->table[pos] != NULL){
            if (strcmp(hash->table[pos], student) == 0){
                hash->table[pos] = NULL;
                break;
            }
        }
        pos = (pos + 1) % hash->length;
    }
}

// Function that prints the hash table and it's situation
void printHash(HASH *hash){
    for (int i = 0; i < hash->length; i++){
        if (hash->table[i] != NULL)
            printf("%d: %s\n", i, hash->table[i]);
        else
            printf("%d: XXXX\n", i);
    }
    printf("\n");
}

// Funtion that searchs through the hash table
void searchHash(HASH *hash, char *student){
    int pos = hashFunction(student, hash->length);

    for (int i = 0; i < hash->length; i++){
        if (hash->table[pos] != NULL){
            if (strcmp(hash->table[pos], student) == 0){
                printf("%s esta presente no lugar %d\n", student, pos);
                return;
            }
        }

        pos = (pos + 1) % hash->length;
    }

    printf("%s nao esta presente\n", student);
}

// Function that deletes the hash struct
void deleteHash(HASH *hash){
    free(hash->table);
    free(hash);
}

int main(){
    // Discovering the hash size and the number of students to be added to the hash
    int numberChars, numberStudents;
    scanf("%d %d\n\r", &numberChars, &numberStudents);

    HASH *hash = createHash(numberChars);
    char **students = discoverStudent(numberStudents);

    // Inserting the students into the hash
    for (int i = 0; i < numberStudents; i++)
        insertHash(hash, students[i]);

    // Discovering the number of students going out from the class and which one are those
    int outStudents;
    scanf("%d\n\r", &outStudents);

    char **goingOut = discoverStudent(outStudents);
    
    // Printing the state of the hash function
    printHash(hash);

    // Removing the students from the hash table
    for (int i = 0; i < outStudents; i++)
        removeFromHash(hash, goingOut[i]);

    // Discovering the number of students to found and which one are those
    int numberSearchs;
    scanf("%d\n\r", &numberSearchs);

    char **studentsToFind = discoverStudent(numberSearchs);

    for (int i = 0; i < numberSearchs; i++)
        searchHash(hash, studentsToFind[i]);
    
    // Deallocating the heap memory
    deallocateStudent(students, numberStudents);
    deallocateStudent(goingOut, outStudents);
    deallocateStudent(studentsToFind, numberSearchs);
    deleteHash(hash);

    return 0;
}