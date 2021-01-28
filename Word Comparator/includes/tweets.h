#ifndef TWEETS_H
    #define TWEETS_H

    #include <utils.h>

    typedef struct _jsonwords{
        char **words;
        int nWords;
    } JSONWORDS;

    typedef struct _tweets{
        JSONWORDS **tweets;
        int nTweets;
    } TWEETS;

    TWEETS* startTweets();
    TWEETS* addTweets(bool*);
    void deleteTweets(TWEETS*);

#endif