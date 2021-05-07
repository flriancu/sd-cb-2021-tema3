#ifndef AUTHOR_TRIE_H
#define AUTHOR_TRIE_H

#include "book_trie.h"


typedef struct author_trie_t
{
    book_trie_t *value;
    struct author_trie_t **children;
} author_trie_t;


void AllocAuthorTrieNode(author_trie_t **t);


void FreeAuthorTrieNode(author_trie_t **t);


void FreeAuthorTrie(author_trie_t **t);


#endif
