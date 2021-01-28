#ifndef DICT_H
    #define DICT_H

    #include <trie.h>
    #include <tweets.h>

    void addDict(TRIE*);
    void findWrongWords(TRIE*, TWEETS*);

#endif