#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uspotify.h>

// Function that allocates and start the uspotify struct for each of the struct needed
USPOTIFY* createUSPOTIFY(){
    USPOTIFY *uspotify = (USPOTIFY*) malloc(sizeof(USPOTIFY));
    uspotify->nArtist = 0;
    uspotify->nTracks = 0;
    uspotify->artists = (ARTIST**) malloc(sizeof(ARTIST*));

    return uspotify;
}

typedef struct _csvWords{
    char **words;
    int amount;
} CSVWORDS;

// Function that creates a wordlist
CSVWORDS* createWordList(){
    CSVWORDS *list = malloc (sizeof(CSVWORDS));
    list->words = NULL;
    list->amount = 0;

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
CSVWORDS *splitList(char *string, char delimiter){
    CSVWORDS *splitList = createWordList();

    bool isOver = FALSE;

    int strPos = 0;

    do {
        splitList->words = realloc(splitList->words, (splitList->amount + 1) * sizeof(char*));
        char **curPart = &splitList->words[splitList->amount];

        isOver = getPartFromStr(string, &strPos, curPart, delimiter); 
        splitList->amount++;
    } while(!isOver);

    return splitList;
}

// Function that finds the index of an existing artist, if the artist doesn't exist error code
int indexOfArtist(USPOTIFY *uspotify, char *currentArtist){
    for (int i = 0; i < uspotify->nArtist; i++){
        if (strcmp(currentArtist, uspotify->artists[i]->artistName) == 0)
            return i;
    }

    return -1;
}

// Fuction that finds the index of an existing album, if the album doesn't exist error code
int indexOfAlbum(USPOTIFY *uspotify, char *currentAlbum, int artistIndex){
    for (int i = 0; i < uspotify->artists[artistIndex]->nAlbums; i++){
        if (strcmp(currentAlbum, uspotify->artists[artistIndex]->albums[i]->albumName) == 0)
            return i;
    }

    return -1;
}

// Function that creates a new artist
ARTIST* createArtist(CSVWORDS *wordList){
    ARTIST *newArtist = (ARTIST*) malloc(sizeof(ARTIST));
    newArtist->artistName = strdup(wordList->words[4] + 1);
    newArtist->artistID = strdup(wordList->words[5] + 1);
    newArtist->nAlbums = 0;
    newArtist->nTracksArtist = 0;
    newArtist->popularity = 0;
    newArtist->albums = NULL;

    return newArtist;
}

// Function that creates a new album
ALBUM* createAlbum(CSVWORDS *wordList){
    ALBUM *newAlbum = (ALBUM*) malloc(sizeof(ALBUM));
    newAlbum->albumName = strdup(wordList->words[2] + 1);
    newAlbum->albumID = strdup(wordList->words[3] + 1);
    newAlbum->nTracks = 0;
    newAlbum->tracks = NULL;

    return newAlbum;
}

// Function that creates a new track
TRACK* createTrack(CSVWORDS *wordList){
    TRACK *newTrack = (TRACK*) malloc(sizeof(TRACK));
    newTrack->trackName = strdup(wordList->words[0]);
    newTrack->trackID = strdup(wordList->words[1] + 1);
    newTrack->relaseDate = strdup(wordList->words[6] + 1);
    newTrack->length = atoi(wordList->words[7] + 1);
    newTrack->popularity = atoi(wordList->words[8] + 1);
    newTrack->acousticness = atof(wordList->words[9] + 1);
    newTrack->danceability = atof(wordList->words[10] + 1);
    newTrack->energy = atof(wordList->words[11] + 1);
    newTrack->instrumentalness = atof(wordList->words[12] + 1);
    newTrack->liveness = atof(wordList->words[13] + 1);
    newTrack->loudness = atof(wordList->words[14] + 1);
    newTrack->speechiness = atof(wordList->words[15] + 1);
    newTrack->time = atof(wordList->words[16] + 1);
    newTrack->timeSignature = atoi(wordList->words[17] + 1);

    return newTrack;
}

// Function that sets a new track to a album of an artist
USPOTIFY* setTrack(USPOTIFY *uspotify, CSVWORDS *wordList, int artistIndex, int albumIndex){
    int nTracks = uspotify->artists[artistIndex]->albums[albumIndex]->nTracks;
    // Reallocing space for a new track in the album
    uspotify->artists[artistIndex]->albums[albumIndex]->tracks = 
        realloc(uspotify->artists[artistIndex]->albums[albumIndex]->tracks, (nTracks + 1)*sizeof(TRACK*));
    // Adding a new track to the album
    uspotify->artists[artistIndex]->albums[albumIndex]->tracks[nTracks] = createTrack(wordList);
    uspotify->artists[artistIndex]->albums[albumIndex]->nTracks++;
    uspotify->artists[artistIndex]->nTracksArtist++;
    uspotify->artists[artistIndex]->popularity += atoi(wordList->words[8] + 1);

    return uspotify;
}

// Function that sets a new Album to a artist
USPOTIFY* setAlbum(USPOTIFY *uspotify, CSVWORDS *wordList, int artistIndex){
    // Checking if the album alredy exists in the albuns of given artist
    int albumIndex = indexOfAlbum(uspotify, wordList->words[2] + 1, artistIndex);

    // If -1 the album doesn't exist in the artist list, then reallocating a space for him
    if (albumIndex == -1){
        uspotify->artists[artistIndex]->albums = realloc(uspotify->artists[artistIndex]->albums, 
                                    (uspotify->artists[artistIndex]->nAlbums + 1) * sizeof(ALBUM*));
        // Creating a new album for the artist and saving a track
        uspotify->artists[artistIndex]->albums[uspotify->artists[artistIndex]->nAlbums] = createAlbum(wordList);
        uspotify = setTrack(uspotify, wordList, artistIndex, uspotify->artists[artistIndex]->nAlbums);
        uspotify->artists[artistIndex]->nAlbums++;
    }
    else
        uspotify = setTrack(uspotify, wordList, artistIndex, albumIndex);

    return uspotify;
}

// Function that set the values for the struct
USPOTIFY* setDataFrame(USPOTIFY *uspotify, CSVWORDS *wordList){
    // Checking if the artist exists in the DataFrame
    int artistIndex = indexOfArtist(uspotify, wordList->words[4] + 1);
    
    // If -1 the artist doesn't exist in the list, then reallocating a space for him
    if (artistIndex == -1){
        uspotify->artists = realloc(uspotify->artists, (uspotify->nArtist + 1) * sizeof(ARTIST*));
        // Creating a new artist in the list of all artists
        uspotify->artists[uspotify->nArtist] = createArtist(wordList);
        uspotify = setAlbum(uspotify, wordList, uspotify->nArtist);
        uspotify->nArtist++;
    }
    else 
        uspotify = setAlbum(uspotify, wordList, artistIndex);

    return uspotify;
}

// Function that deallocated the heap memory of a word list
void freeList(CSVWORDS *wordlist){
    for (int i = 0; i < wordlist->amount; i++){
        free(wordlist->words[i]);
    }
    free(wordlist->words);
    free(wordlist);
}

// Function that reads the CSV and saves its values into the DataFrame
USPOTIFY* readCSV(USPOTIFY *uspotify, FILE *fp){
    while(!feof(fp)){
        char *line = readLine(fp);
        if (strcmp(line, "") == 0) free(line);

        // If line is now empty creating a list with the line splicing it with the choosen separator
        else {
            CSVWORDS *splitedLine = splitList(line, ';');

            // Setting the values in the struct
            uspotify = setDataFrame(uspotify, splitedLine);

            // Deallocating the wordlist that were alredy used
            freeList(splitedLine);

            free(line);
            
            // Counting the number of tracks
            uspotify->nTracks++;
        }
    }

    return uspotify;
}

// Function that calculates the popularity of each artist
void artistPopularity(USPOTIFY *uspotify){
    for (int i = 0; i < uspotify->nArtist; i++){
        int numberTimes = uspotify->artists[i]->nTracksArtist;
        uspotify->artists[i]->popularity = uspotify->artists[i]->popularity / numberTimes;
    }
}

// Function that creates a DataFrame
USPOTIFY* createDataFrame(USPOTIFY *uspotify){
    // Reading the CSV
    char *csvName;
    csvName = readLine(stdin);
    FILE *fp = fopen(csvName, "r");

    if (fp == NULL)
        printf("Arquivo inexistente\n");

    // Reading and discarding the line with the fields name of the CSV
    char *discard = readLine(fp);
    free(discard);

    uspotify = readCSV(uspotify, fp);

    artistPopularity(uspotify);

    free(csvName);
    fclose(fp);

    return uspotify;
}

// Auxiliar function for mergesort
void merge(USPOTIFY *uspotify, int start, int mid, int end){
    // Creating a auxiliar vector to sort the array
    ARTIST **merged_arr = (ARTIST**) malloc(((end - start) + 1) * sizeof(ARTIST*));

    int i = start; // Index of the first ordenated list (goes from start to mid)
    int j = mid + 1; // Index of the second ordenated list (goes from mid + 1 to end)
    int k = 0; // Index of the auxiliar array (goes from k to (end - start))

    // Merging the ordenated list in the merged array
    while (i <= mid && j <= end){
        if (uspotify->artists[i]->popularity >= uspotify->artists[j]->popularity){
            merged_arr[k] = uspotify->artists[i];
            i++;
        }
        else {
            merged_arr[k] = uspotify->artists[j];
            j++;
        }
        k++;
    }

    // Merging possible not merged artists in the first list
    while (i <= mid){
        merged_arr[k] = uspotify->artists[i];
        i++;
        k++;
    }

    while (j <= end){
        merged_arr[k] = uspotify->artists[j];
        j++;
        k++;
    }

    // Now copying the auxiliar ordenated array to the original array
    for (int i = start, k = 0; i <= end; i++, k++){
        uspotify->artists[i] = merged_arr[k];
    }

    // Deallocating the auxiliar array
    free(merged_arr);
}

// Function that ordenates the artists using mergesort
void ordenateDataFrame(USPOTIFY *uspotify, int start, int end){
    // Base case, array of size 1
    if (end <= start) return;

    // Calculating the actual vector size / 2
    int mid = start + (end - start) / 2;

    // Divide
    ordenateDataFrame(uspotify, start, mid); // Call for the left part
    ordenateDataFrame(uspotify, mid + 1, end); // Call for the right part

    // Conquer
    merge(uspotify, start, mid, end);
}

// Function that prints all the artists and it's informations
void printList(USPOTIFY *uspotify){
    printf("O Dataset contem %d Artistas e %d Musicas\n", uspotify->nArtist, uspotify->nTracks);
    printf("Os artistas mais populares sao:\n");
    for (int i = 0; i < uspotify->nArtist; i++){
        // Printing the results
        printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2lf, Link: https://open.spotify.com/artist/%s\n",
        i+1, uspotify->artists[i]->artistName, uspotify->artists[i]->nTracksArtist, uspotify->artists[i]->popularity,
        uspotify->artists[i]->artistID);
    }
}

// Function that deallocates all the heap memory
void deallocatesCSV(USPOTIFY *uspotify){
    // Deallocating the artists
    for (int i = 0; i < uspotify->nArtist; i++){
        // Deallocating the albums of given artist
        for (int j = 0; j < uspotify->artists[i]->nAlbums; j++){
            free(uspotify->artists[i]->albums[j]->albumName);
            free(uspotify->artists[i]->albums[j]->albumID);

            // Deallocating the tracks of given album
            for (int k = 0; k < uspotify->artists[i]->albums[j]->nTracks; k++){
                free(uspotify->artists[i]->albums[j]->tracks[k]->trackName);
                free(uspotify->artists[i]->albums[j]->tracks[k]->trackID);
                free(uspotify->artists[i]->albums[j]->tracks[k]->relaseDate);
                free(uspotify->artists[i]->albums[j]->tracks[k]);
            }
            free(uspotify->artists[i]->albums[j]->tracks);
            free(uspotify->artists[i]->albums[j]);
        }
        free(uspotify->artists[i]->albums);
        free(uspotify->artists[i]->artistName);
        free(uspotify->artists[i]->artistID);
        free(uspotify->artists[i]);
    }
    free(uspotify->artists);
    free(uspotify);
}
