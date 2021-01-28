#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tweets.h>
#include <ctype.h>

// Function that creates a wordlist
JSONWORDS* createWordList(){
    JSONWORDS *list = malloc(sizeof(JSONWORDS));
    list->words = NULL;
    list->nWords = 0;

    return list;
}

// Function that particionates a string and saves it to the word list
bool getPartFromStr(char *sourceStr, int *sourcePos, char **destStr, char delimiter){
    *destStr = NULL;
    bool isEndOfPart = FALSE;

    char c;
    int dest_pos = 0;
    do {
        c = sourceStr[*sourcePos];

        if (!isalpha(c) && c != '\n' && c != '\0')
            c = ' ';

        if (c == '\0') {
            *destStr = realloc(*destStr, (dest_pos + 1) * sizeof(char));
            (*destStr)[dest_pos] = '\0';
            return TRUE;
        }

        else if (c == delimiter) {
            isEndOfPart = TRUE;
            c = '\0';
        }

        *destStr = realloc(*destStr, (dest_pos + 1) * sizeof(char));
        (*destStr)[dest_pos] = c;

        (*sourcePos)++;
        dest_pos++;
    } while (!isEndOfPart);

    return FALSE;
}

// Function that parcionates a given string into its delimiters and save in a char** wordlist
JSONWORDS *splitTweet(char *string, char delimiter){
    JSONWORDS *splitList = createWordList();

    bool isOver = FALSE;

    int strPos = 0;

    do {
        splitList->words = realloc(splitList->words, (splitList->nWords + 1) * sizeof(char*));
        char **curPart = &splitList->words[splitList->nWords];

        isOver = getPartFromStr(string, &strPos, curPart, delimiter); 
        splitList->nWords++;
    } while(!isOver);

    return splitList;
}

// Function that counts the number of tweets into a json file
int howManyTweets(FILE *fp){
    int amount = 0;

    if (fp == NULL)
        printf("Não foi possível abrir o arquivo");

    char *line = NULL;
    if (fp != NULL){
        while(!feof(fp)){
            line = readLine(fp);
            
            char *checkText = strndup(line + 25, 4);

            // Line + 25 does the pointer goes to the t into the "text"
            if (strcmp(checkText, "text") == 0)
                amount++;

            free(checkText);
            free(line);
        }
    }

    return amount;
}

// Function that saves the content of the tweets and split it
void copyContentTweets(TWEETS* tweetList, FILE* fp){
    if (fp != NULL){
        rewind(fp);

        char *line = NULL; 
        while(!feof(fp)){
            line = readLine(fp);
            
            char *checkText = strndup(line + 25, 4);

            // Line + 25 does the pointer goes to the t into the "text"
            if (strcmp(checkText, "text") == 0){
                // Line + 33 makes the pointer go to the start of the content of the text into the tweet
                // then copying strlen(line + 33) - 2 cause it's the number of characters into the line not including '\0'
                // and "
                char *content = strndup(line + 33, strlen(line + 33) - 2);

                tweetList->tweets[tweetList->nTweets] = splitTweet(content, ' ');
                tweetList->nTweets++;
                free(content);
            }

            free(checkText);
            free(line);
        }
    }
}

// Function that creates a list of tweets
TWEETS* addTweets(bool *checkWrongWords){
    // What's the archive name
    char *filename = readLine(stdin);
    FILE *fp = fopen(filename, "r");
    free(filename);

    if (fp != NULL){

        // Discovering how many tweets are there in the json
        int amount = howManyTweets(fp);

        // If json returned error
        if (amount == 0){
            *checkWrongWords = FALSE;
            printf("No tweets to check\n");
            fclose(fp);
        }

        // If a tweet was found
        if (amount > 0){
            // Allocating the right memory to the tweets
            TWEETS *tweetList = malloc(sizeof(TWEETS));
            tweetList->nTweets = 0;
            tweetList->tweets = malloc(amount * sizeof(JSONWORDS*));
            for (int i = 0; i < amount; i++){
                tweetList->tweets[i] = NULL;
            }
            
            // Saving the contents of the tweets
            copyContentTweets(tweetList, fp);

            fclose(fp);

            return tweetList;
        }
    }

    return NULL;
}

// Function that deallocates the heap memory
void deleteTweets(TWEETS* tweetList){
    for (int i = 0; i < tweetList->nTweets; i++){
        for (int j = 0; j < tweetList->tweets[i]->nWords; j++){
            free(tweetList->tweets[i]->words[j]);
        }
        free(tweetList->tweets[i]->words);
        free(tweetList->tweets[i]);
    }
    free(tweetList->tweets);
    free(tweetList);
}