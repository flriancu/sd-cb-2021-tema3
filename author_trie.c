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
        FreeBookTrie(&(*t)->value);
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
