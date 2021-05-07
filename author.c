#include "author.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>


void PrintAuthorInfo(const author_info_t *info, FILE *fo)
{
    if (info)
    {
        fprintf(fo, "%s\n",
            info->name);
    }
    else
    {
        fprintf(fo, "-\n");
    }
}


void AllocAuthorInfo(author_info_t **info, const char *name)
{
    MALLOC(*info, sizeof(author_info_t));

    MALLOC((*info)->name, sizeof(char) * (strlen(name) + 1));

    memcpy((*info)->name, name, sizeof(char) * (strlen(name) + 1));
    (*info)->books = NULL;
}


void FreeAuthorInfo(author_info_t **info)
{
    FREE((*info)->name);
    FreeBookTrie(&(*info)->books, TRUE);
    FREE(*info);
    *info = NULL;
}
