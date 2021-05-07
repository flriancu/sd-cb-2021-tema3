#ifndef COMMANDS_H
#define COMMANDS_H

#include "book_trie.h"
#include "author_trie.h"
#include "utils.h"


void AddBook(book_trie_t *t, const char *key, book_info_t *value);


void SearchBook(book_trie_t *t, const char *key, book_trie_t **out_node);


void ListBooks(book_trie_t *t, int *nb_found, int limit);


void AddAuthor(author_trie_t *t, const char *key, book_info_t *value);


void SearchAuthor(author_trie_t *t, const char *key, author_trie_t **out_node);


void ListAuthors(author_trie_t *t, int *nb_found, int limit);


#endif
