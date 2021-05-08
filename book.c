#include "book.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>


void PrintBookInfo(const book_info_t *info, FILE *fo)
{
    if (!fo)
    {
        return;
    }
    
    if (info)
    {
        fprintf(fo, "%s, %s, %.2f, %d\n",
            info->title,
            info->author,
            info->rating,
            info->nb_pages);
    }
    else
    {
        fprintf(fo, "-\n");
    }
}


void AllocBookInfo(book_info_t **info, char *title, char *author, float rating, int nb_pages)
{
    MALLOC(*info, sizeof(book_info_t));

    MALLOC((*info)->author, sizeof(char) * (strlen(author) + 1));
    MALLOC((*info)->title, sizeof(char) * (strlen(title) + 1));

    memcpy((*info)->author, author, sizeof(char) * (strlen(author) + 1));
    memcpy((*info)->title, title, sizeof(char) * (strlen(title) + 1));
    (*info)->rating = rating;
    (*info)->nb_pages = nb_pages;
}


void FreeBookInfo(book_info_t **info)
{
    FREE((*info)->author);
    FREE((*info)->title);
    FREE(*info);
    *info = NULL;
}
