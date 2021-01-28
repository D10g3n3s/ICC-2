#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <uspotify.h>

// Function that allocates and start the uspotify struct for each of the struct needed
USPOTIFY* createUSPOTIFY(){
    USPOTIFY *uspotify = (USPOTIFY*) malloc(sizeof(USPOTIFY));
    uspotify->infos = malloc(sizeof(INFO*));
    uspotify->nTracks = 0;

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

// Function that creates a new info struct
INFO* createInfo(){
    INFO* newInfo = malloc(sizeof(INFO));

    newInfo->artists = NULL;
    newInfo->albums = NULL;
    newInfo->tracks = NULL;

    return newInfo;
}

// Function that creates a new artist
ARTIST* createArtist(CSVWORDS *wordList){
    ARTIST *newArtist = (ARTIST*) malloc(sizeof(ARTIST));
    newArtist->artistName = strdup(wordList->words[4] + 1);
    newArtist->artistID = strdup(wordList->words[5] + 1);

    return newArtist;
}

// Function that creates a new album
ALBUM* createAlbum(CSVWORDS *wordList){
    ALBUM *newAlbum = (ALBUM*) malloc(sizeof(ALBUM));
    newAlbum->albumName = strdup(wordList->words[2] + 1);
    newAlbum->albumID = strdup(wordList->words[3] + 1);

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

// Function that sets artists, albums and tracks for the struct
USPOTIFY* setDataFrame(USPOTIFY *uspotify, CSVWORDS *wordList){
    // Reallocating the uspotify struct to allocate another artist, album and track
    uspotify->infos = realloc(uspotify->infos, (uspotify->nTracks + 1) * sizeof(INFO*));
    uspotify->infos[uspotify->nTracks] = createInfo();
    
    // Creating a new artist in the list of all artists
    uspotify->infos[uspotify->nTracks]->artists = createArtist(wordList);
    
    // Creating a new album for the artist and saving a track
    uspotify->infos[uspotify->nTracks]->albums = createAlbum(wordList);

    // Adding a new track to the album and increasing the count of the tracks
    uspotify->infos[uspotify->nTracks++]->tracks = createTrack(wordList);

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
        }
    }

    return uspotify;
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

    free(csvName);
    fclose(fp);

    return uspotify;
}

// Function that deallocates all the heap memory
void deallocatesCSV(USPOTIFY *uspotify){
    // Deallocating artists, albums and tracks
    for (int i = 0; i < uspotify->nTracks; i++){
        // Deallocating the artists
        free(uspotify->infos[i]->artists->artistName);
        free(uspotify->infos[i]->artists->artistID);
        free(uspotify->infos[i]->artists);

        // Deallocating the albums
        free(uspotify->infos[i]->albums->albumName);
        free(uspotify->infos[i]->albums->albumID);
        free(uspotify->infos[i]->albums);

        // Deallocating the tracks
        free(uspotify->infos[i]->tracks->relaseDate);
        free(uspotify->infos[i]->tracks->trackName);
        free(uspotify->infos[i]->tracks->trackID);
        free(uspotify->infos[i]->tracks);

        free(uspotify->infos[i]);
    }
    free(uspotify->infos);
    free(uspotify);
}

double euclidianDistance(TRACK *musicAInfo, TRACK *musicBInfo){
    // Every info sum

    double distance = 0;
    distance += pow(musicAInfo->acousticness - musicBInfo->acousticness, 2);
    distance += pow(musicAInfo->danceability - musicBInfo->danceability, 2);
    distance += pow(musicAInfo->energy - musicBInfo->energy, 2);
    distance += pow(musicAInfo->instrumentalness - musicBInfo->instrumentalness, 2);
    distance += pow(musicAInfo->liveness - musicBInfo->liveness, 2);
    distance += pow(musicAInfo->loudness - musicBInfo->loudness, 2);
    distance += pow(musicAInfo->speechiness - musicBInfo->speechiness, 2);
    distance += pow(musicAInfo->time - musicBInfo->time, 2);
    distance += pow(musicAInfo->timeSignature - musicBInfo->timeSignature, 2);

    return sqrt(distance);
}

// Function that creates the dissimilarity matrix
CELL** createDissimilarityMatrix(USPOTIFY *uspotify){
    // Creating the matrix
    CELL **matrix = malloc(uspotify->nTracks * sizeof(CELL*));
    for (int i = 0; i < uspotify->nTracks; i++){
        matrix[i] = malloc(uspotify->nTracks * sizeof(CELL));
    }

    // Calculating the euclidean's distance
    for (int i = 0; i < uspotify->nTracks; i++){
        for (int j = 0; j < uspotify->nTracks; j++){
            matrix[i][j].distance = euclidianDistance(uspotify->infos[i]->tracks, uspotify->infos[j]->tracks);
            matrix[i][j].rowIndex = j;
        }
    }

    return matrix;
}

// String binary search
int binarySearch(USPOTIFY* uspotify, int start, int end, char *musicToFind){
    if (end >= start){
        int mid = start + (end - start) / 2;

        // If the string to found is in the mid index, return mid
        if (strcmp(uspotify->infos[mid]->tracks->trackID, musicToFind) == 0)
            return mid;

        // If the element is lower than the middle term then the element is in the left subconjunt
        if (strcmp(uspotify->infos[mid]->tracks->trackID, musicToFind) > 0)
            return binarySearch(uspotify, start, mid - 1, musicToFind);
        
        // The element needs to be in the right subconjunt
        return binarySearch(uspotify, mid + 1, end, musicToFind);
    }

    // If we don't found the element in the dataset return error
    return -1;
}

// Function that prints the K nearest neighbors of a music
void printNeighbors(USPOTIFY *uspotify, CELL **matrix, int Q, int K, int *indexArray){
    for (int i = 0; i < Q; i++){
        printf("----As %d musicas mais parecidas com %s sao:\n", K, uspotify->infos[indexArray[i]]->tracks->trackName);
        for (int j = 0; j < K; j++){
            printf("\t(%d)Artista: %s\n", j, uspotify->infos[matrix[indexArray[i]][j].rowIndex]->artists->artistName);
            printf("\t\tMusica: %s\n", uspotify->infos[matrix[indexArray[i]][j].rowIndex]->tracks->trackName);
            printf("\t\tDissimilaridade: %lf\n", matrix[indexArray[i]][j].distance);
            printf("\t\tLink: https://open.spotify.com/track/%s\n", uspotify->infos[matrix[indexArray[i]][j].rowIndex]->tracks->trackID);
        }
        printf("\n");
    }
}

// Function that prints out the K nearest neighbors
void KNN(USPOTIFY *uspotify, CELL **matrix){
    // Discovering the K neighbors to find and the number of musics to be search
    int Q, K;
    scanf("%d %d\r\n", &Q, &K);

    char **musics = malloc(Q * sizeof(char*));

    // Discovering which are the musics to check the similarity
    for (int i = 0; i < Q; i++)
        musics[i] = readLine(stdin);

    // Searching the musics into the dataset and saving it in a array of index's
    int *indexArray = malloc(Q * sizeof(int));
    for (int i = 0; i < Q; i++)
        indexArray[i] = binarySearch(uspotify, 0, uspotify->nTracks - 1, musics[i]);

    // Printing the K nearest neighbors of each music
    printNeighbors(uspotify, matrix, Q, K, indexArray);

    // Deallocating the heap memory
    free(indexArray);
    for (int i = 0; i < Q; i++){
        free(musics[i]);
    }
    free(musics);
}

// Function that deallocates the memory of the dissimilarity matrix
void deallocateMatrix(CELL **matrix, int length){
    for (int i = 0; i < length; i++){
        free(matrix[i]);
    }
    free(matrix);
}