#ifndef AUTHOR_TRIE_H
#define AUTHOR_TRIE_H

#include "author.h"
#include "utils.h"


typedef struct author_trie_t
{
    author_info_t *value;
    struct author_trie_t **children;
} author_trie_t;


void AllocAuthorTrieNode(
    OUT author_trie_t **t);


void FreeAuthorTrieNode(
    IN  author_trie_t **t);


void FreeAuthorTrie(
    IN  author_trie_t **t);


void PrintAuthorTrie(
    IN  author_trie_t *t, 
    OUT int *nb_found, 
    IN  int limit, 
    IN  FILE *fo);


void AddAuthor(
    IN  author_trie_t *t, 
    IN  const char *key, 
    IN  book_info_t *value);


void DeleteAuthor(
    IN author_trie_t **t, 
    IN const char *key);


void SearchAuthor(
    IN  author_trie_t *t, 
    IN  const char *key, 
    OUT author_trie_t **out_node);


#endif
