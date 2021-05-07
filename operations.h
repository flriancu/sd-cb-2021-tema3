#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "book_trie.h"
#include "author_trie.h"
#include "utils.h"


void AddBook(book_trie_t *t, const char *key, book_info_t *value);


void SearchBook(book_trie_t *t, const char *key, book_trie_t **out_node);


void AddAuthor(author_trie_t *t, const char *key, book_info_t *value);


void SearchAuthor(author_trie_t *t, const char *key, author_trie_t **out_node);


#endif
