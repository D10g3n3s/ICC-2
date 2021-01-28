#ifndef TRIE_H
    #define TRIE_H

    #include <boolean.h>

    #define NWORDS 26

    typedef struct _trie TRIE;

    TRIE* createTrie();
    void deleteTrie(TRIE*);
    void insertIntoTrie(TRIE*, char*);
    void printNotFound(TRIE*, char*);

#endif