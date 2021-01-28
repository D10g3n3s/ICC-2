#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <dict.h>
#include <tweets.h>

// Function that adds words of a dict to a trie
void addDict(TRIE *root){
    // What's the archive name
    char *filename = readLine(stdin);
    FILE *fp = fopen(filename, "r");

    if (fp != NULL){
        while(!feof(fp)){
            char *word = readWord(fp);
            if (word != NULL && word[0] != '\0')
                insertIntoTrie(root, word);
            free(word);
        }
    }

    free(filename);
    fclose(fp);
}

// Function that checks wrong words into all tweets
void findWrongWords(TRIE *root, TWEETS *tweetList){
    for (int i = 0; i < tweetList->nTweets; i++){
        for (int j = 0; j < tweetList->tweets[i]->nWords; j++){
            if (tweetList->tweets[i]->words[j][0] != '\0')
                printNotFound(root, tweetList->tweets[i]->words[j]);
        }
        printf("\n");
    }
}