#ifndef AUTHOR_H
#define AUTHOR_H

#include "book_trie.h"

#include <stdio.h>


typedef struct author_info_t
{
    char *name;
    book_trie_t *books;
} author_info_t;


void PrintAuthorInfo(const author_info_t *info, FILE *fo);


void AllocAuthorInfo(author_info_t **info, const char *name);


void FreeAuthorInfo(author_info_t **info);


#endif
