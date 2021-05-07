#ifndef BOOK_TRIE_H
#define BOOK_TRIE_H

#include "book.h"


typedef struct book_trie_t
{
    book_info_t *value;
    struct book_trie_t **children;
} book_trie_t;


void AllocBookTrieNode(book_trie_t **t);


void FreeBookTrieNode(book_trie_t **t, int is_view);


void FreeBookTrie(book_trie_t **t, int is_view);


void PrintBookTrie(book_trie_t *t, int *nb_found, int limit, FILE *fo);


void AddBook(book_trie_t *t, const char *key, book_info_t *value);


void SearchBook(book_trie_t *t, const char *key, book_trie_t **out_node);


#endif
