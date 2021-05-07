#ifndef COMMANDS_H
#define COMMANDS_H

#include "book_trie.h"
#include "author_trie.h"
#include "utils.h"

#include <string.h>


void AddBook(book_trie_t *t, const char *key, book_info_t *value);


int SearchBook(book_trie_t *t, const char *key, book_info_t **out_value, book_trie_t **out_node);


void ListBooks(book_trie_t *t, int *nb_found, int limit);


#endif