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
|    |                  Word Comparator                  |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <dict.h>

int main(){
    TRIE* root = createTrie();
    TWEETS* tweets = NULL;
    bool checkWrongWords = TRUE;

    // Adding words from dictionary into the trie
    addDict(root);

    // Finding the tweets and saving it
    tweets = addTweets(&checkWrongWords);

    // Searching for the wrong words if necessary
    if (checkWrongWords)
        findWrongWords(root, tweets);

    // Deallocating the heap memory of the structures
    deleteTrie(root);
    if (tweets != NULL)
        deleteTweets(tweets);

    return 0;
}