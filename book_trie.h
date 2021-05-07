#ifndef BOOK_TRIE_H
#define BOOK_TRIE_H

#include "book.h"


typedef struct book_trie_t
{
    book_info_t *value;
    struct book_trie_t **children;
} book_trie_t;


void AllocBookTrieNode(book_trie_t **t);


void FreeBookTrieNode(book_trie_t **t, int hard_free);


void FreeBookTrie(book_trie_t **t, int hard_free);


#endif
