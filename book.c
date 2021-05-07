#include "book.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>


void PrintBookInfo(const book_info_t *book_info, FILE *fo)
{
    if (book_info)
    {
        fprintf(fo, "%s, %s, %.2f, %d\n",
            book_info->title,
            book_info->author,
            book_info->rating,
            book_info->nb_pages);
    }
    else
    {
        fprintf(fo, "-\n");
    }
}


void AllocBookInfo(book_info_t **b, char *title, char *author, float rating, int nb_pages)
{
    MALLOC(*b, sizeof(book_info_t));

    MALLOC((*b)->author, sizeof(char) * (strlen(author) + 1));
    MALLOC((*b)->title, sizeof(char) * (strlen(title) + 1));

    memcpy((*b)->author, author, sizeof(char) * (strlen(author) + 1));
    memcpy((*b)->title, title, sizeof(char) * (strlen(title) + 1));
    (*b)->rating = rating;
    (*b)->nb_pages = nb_pages;
}


void FreeBookInfo(book_info_t **e)
{
    FREE((*e)->author);
    FREE((*e)->title);
    FREE(*e);
    *e = NULL;
}
