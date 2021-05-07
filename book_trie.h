#ifndef BOOK_TRIE_H
#define BOOK_TRIE_H

#include "book.h"
#include "utils.h"


typedef struct book_trie_t
{
    book_info_t *value;
    struct book_trie_t **children;
} book_trie_t;


void AllocBookTrieNode(
    OUT book_trie_t **t);


void FreeBookTrieNode(
    IN  book_trie_t **t, 
    IN  int is_view);


void FreeBookTrie(
    IN  book_trie_t **t, 
    IN  int is_view);


void PrintBookTrie(
    IN  book_trie_t *t, 
    IN  int *nb_found, 
    IN  int limit, 
    IN  FILE *fo);


void AddBook(
    IN  book_trie_t *t, 
    IN  const char *key, 
    IN  book_info_t *value);


void SearchBook(
    IN  book_trie_t *t, 
    IN  const char *key, 
    OUT book_trie_t **out_node);


#endif
