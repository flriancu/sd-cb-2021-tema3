#include "author.h"


void PrintAuthorInfo(const book_info_t *book_info, FILE *fo)
{
    if (book_info)
    {
        fprintf(fo, "%s\n",
            book_info->author);
    }
    else
    {
        fprintf(fo, "-\n");
    }
}
