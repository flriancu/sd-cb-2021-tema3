#ifndef AUTHOR_TRIE_H
#define AUTHOR_TRIE_H

#include "author.h"


typedef struct author_trie_t
{
    author_info_t *value;
    struct author_trie_t **children;
} author_trie_t;


void AllocAuthorTrieNode(author_trie_t **t);


void FreeAuthorTrieNode(author_trie_t **t);


void FreeAuthorTrie(author_trie_t **t);


void PrintAuthorTrie(author_trie_t *t, int *nb_found, int limit, FILE *fo);


void AddAuthor(author_trie_t *t, const char *key, book_info_t *value);


void SearchAuthor(author_trie_t *t, const char *key, author_trie_t **out_node);


#endif
