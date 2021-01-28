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
        TRACK **tracks;
        char *albumName;
        char *albumID;
        int nTracks;
    } ALBUM;

    typedef struct _artist{
        ALBUM **albums;
        char *artistName;
        char *artistID;
        int nAlbums;
        int nTracksArtist;
        float popularity;
    } ARTIST;

    typedef struct _uspotify{
        ARTIST **artists;
        int nArtist;
        int nTracks;
    } USPOTIFY;

    USPOTIFY* createUSPOTIFY();
    USPOTIFY* createDataFrame(USPOTIFY *uspotify);
    void deallocatesCSV(USPOTIFY *uspotify);
    void printList(USPOTIFY *uspotify);
    void ordenateDataFrame(USPOTIFY *uspotify, int start, int end);

#endif