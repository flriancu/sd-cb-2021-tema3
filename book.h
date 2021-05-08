#ifndef BOOK_H
#define BOOK_H

#include "utils.h"

#include <stdio.h>


typedef struct book_info_t
{
    char *title;
    char *author;
    float rating;
    int nb_pages;
} book_info_t;


void PrintBookInfo(
    IN  const book_info_t *info, 
    IN  int full_description,
    IN  FILE *fo);


void AllocBookInfo(
    OUT book_info_t **info, 
    IN  char *title, 
    IN  char *author, 
    IN  float rating, 
    IN  int nb_pages);


void FreeBookInfo(
    IN  book_info_t **info);


#endif
