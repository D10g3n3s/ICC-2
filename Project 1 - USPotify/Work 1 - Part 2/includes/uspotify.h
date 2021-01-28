#ifndef USPOTIFY_H
    #define USPOTIFY_H

    #include <utils.h>

    typedef struct _track{
        char *trackName;
        char *trackID;
        char *relaseDate;
        int length;
        int popularity;
        double acousticness;
        double danceability;
        double energy;
        double instrumentalness;
        double liveness;
        double loudness;
        double speechiness;
        double time;
        int timeSignature;
    } TRACK;

    typedef struct _album{
        char *albumName;
        char *albumID;
    } ALBUM;

    typedef struct _artist{
        char *artistName;
        char *artistID;
    } ARTIST;

    typedef struct _info{
        ARTIST *artists;
        ALBUM *albums;
        TRACK *tracks;
    } INFO;

    typedef struct _uspotify{
        INFO **infos;
        int nTracks;
    } USPOTIFY;

    typedef struct _cell {
        int rowIndex;
        double distance;
    } CELL;

    USPOTIFY* createUSPOTIFY();
    USPOTIFY* createDataFrame(USPOTIFY *uspotify);
    void deallocatesCSV(USPOTIFY *uspotify);
    void printList(USPOTIFY *uspotify);
    CELL** createDissimilarityMatrix(USPOTIFY *uspotify);
    void deallocateMatrix(CELL **matrix, int length);
    void KNN(USPOTIFY *uspotify, CELL **matrix);

#endif