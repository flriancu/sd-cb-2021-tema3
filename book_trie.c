#include "book_trie.h"
#include "utils.h"

#include <stdlib.h>


void AllocBookTrieNode(book_trie_t **t)
{
    int alphabet_size = GetAlphabetSize();

    MALLOC(*t, sizeof(book_trie_t));

    (*t)->value = NULL;
    CALLOC((*t)->children, alphabet_size, sizeof(book_trie_t *));
}


void FreeBookTrieNode(book_trie_t **t, int hard_free)
{
    if ((*t)->children)
    {
        FREE((*t)->children);
    }

    if ((*t)->value)
    {
        if (hard_free)
        {
            FreeBookInfo(&(*t)->value);
        }
    }

    FREE(*t);
    *t = NULL;
}


void FreeBookTrie(book_trie_t **t, int hard_free)
{
    int i;
    int alphabet_size = GetAlphabetSize();

    if (*t == NULL)
    {
        return;
    }

    for (i = 0; i < alphabet_size; ++i)
    {
        FreeBookTrie(&(*t)->children[i], hard_free);
    }

    FreeBookTrieNode(t, hard_free);
}
