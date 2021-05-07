#include "author_trie.h"
#include "utils.h"

#include <stdlib.h>


void AllocAuthorTrieNode(author_trie_t **t)
{
    int alphabet_size = GetAlphabetSize();

    MALLOC(*t, sizeof(author_trie_t));

    (*t)->value = NULL;
    CALLOC((*t)->children, alphabet_size, sizeof(author_trie_t *));
}


void FreeAuthorTrieNode(author_trie_t **t)
{
    if ((*t)->children)
    {
        FREE((*t)->children);
    }

    if ((*t)->value)
    {
        FreeAuthorInfo(&(*t)->value);
    }

    FREE(*t);
    *t = NULL;
}


void FreeAuthorTrie(author_trie_t **t)
{
    int i;
    int alphabet_size = GetAlphabetSize();

    if (*t == NULL)
    {
        return;
    }

    for (i = 0; i < alphabet_size; ++i)
    {
        FreeAuthorTrie(&(*t)->children[i]);
    }

    FreeAuthorTrieNode(t);
}


void PrintAuthorTrie(author_trie_t *t, int *nb_found, int limit, FILE *fo)
{
    if (t == NULL || (limit >= 0 && *nb_found >= limit))
    {
        return;
    }

    if (t->value)
    {
        PrintAuthorInfo(t->value, stdout);
        (*nb_found)++;
    }

    int alphabet_sz = GetAlphabetSize();
    for (int i = 0; i < alphabet_sz; ++i)
    {
        PrintAuthorTrie(t->children[i], nb_found, limit, fo);
    }
}
