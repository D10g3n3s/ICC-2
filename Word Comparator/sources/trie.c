#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trie.h>

struct _trie{
    TRIE *children[NWORDS];
    bool isLeaf;
};

// Function that creates a trie
TRIE* createTrie(){
    TRIE *newTrie = malloc(sizeof(TRIE));
    if (newTrie != NULL){
        newTrie->isLeaf = FALSE;

        for (int i = 0; i < NWORDS; i++)
            newTrie->children[i] = NULL;
    }

    return newTrie;
}

// Function that sets a word to lowercase in the needed characters
char* setLower(char* word){
    int length = strlen(word);
    char *string = malloc(length * sizeof(char));

    for (int i = 0; i < length; i++){
        if (word[i] >= 'A' && word[i] <= 'Z')
            string[i] = tolower(word[i]);
        else 
            string[i] = word[i];
    }

    return string;
}

// Function that inserts a word into a trie
void insertIntoTrie(TRIE* root, char *word){
    TRIE* temp = root;

    // Setting the needed characters to lowercase
    char *letter = setLower(word);

    // Inserting
    for (int i = 0; word[i] != '\0'; i++){
        // Finding the right index of a letter
        int index = (int) letter[i] - 'a'; 

        // If that index doesn't exist adding it to the trie
        if (temp->children[index] == NULL)
            temp->children[index] = createTrie();

        // Going deeper into the trie
        temp = temp->children[index];
    }

    // Setting the node as a leaf to represent end of the word
    temp->isLeaf = TRUE;

    free(letter);
}


// Function that search for a word into a trie
bool searchIntoTrie(TRIE *root, char *word){
    TRIE* temp = root;

    // Setting the needed characters to lowercase
    char *letter = setLower(word);

    // Searching for the letter
    for (int i = 0; word[i] != '\0'; i++){
        // Finding the index of the letter
        int position = letter[i] - 'a';

        // If the index exists then the word may exist if not the word doesn't exists
        if (temp->children[position] == NULL){
            free(letter);
            return FALSE;
        }

        // Going deeper into the trie
        temp = temp->children[position];
    }


    // If existing but not end of the word, then it isn't an added word to the trie
    if (temp != NULL && temp->isLeaf == TRUE){
        free(letter);
        return TRUE;
    }

    free(letter);

    // Returning true cause the word was found in the trie
    return FALSE;
}

// Function that prints if a word is in a trie or not
void printNotFound(TRIE *root, char *word){
    if (searchIntoTrie(root, word) == FALSE)
        printf("%s ", word);
}

// Function that deletes a trie
void deleteTrie(TRIE* node){
    for (int i = 0; i < NWORDS; i++){
        if (node->children[i] != NULL)
            deleteTrie(node->children[i]);
        else
            continue;
    }

    free(node);
}