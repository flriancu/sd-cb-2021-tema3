#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>


typedef struct book_info_t
{
    char *title;
    char *author;
    float rating;
    int nb_pages;
} book_info_t;


void PrintBookInfo(const book_info_t *book_info, FILE *fo);


void AllocBookInfo(book_info_t **b, char *title, char *author, float rating, int nb_pages);


void FreeBookInfo(book_info_t **e);


#endif
