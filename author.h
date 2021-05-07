#ifndef AUTHOR_H
#define AUTHOR_H

#include "book_trie.h"
#include "utils.h"

#include <stdio.h>


typedef struct author_info_t
{
    char *name;
    book_trie_t *books;
} author_info_t;


void PrintAuthorInfo(
    IN  const author_info_t *info, 
    IN  FILE *fo);


void AllocAuthorInfo(
    OUT author_info_t **info, 
    IN  const char *name);


void FreeAuthorInfo(
    IN  author_info_t **info);


#endif
