#include "book_trie.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void AllocBookTrieNode(book_trie_t **t)
{
    int alphabet_size = GetAlphabetSize();

    MALLOC(*t, sizeof(book_trie_t));

    (*t)->value = NULL;
    CALLOC((*t)->children, alphabet_size, sizeof(book_trie_t *));
}


void FreeBookTrieNode(book_trie_t **t, int is_view)
{
    if ((*t)->children)
    {
        FREE((*t)->children);
    }

    if ((*t)->value)
    {
        if (!is_view)
        {
            FreeBookInfo(&(*t)->value);
        }
    }

    FREE(*t);
    *t = NULL;
}


void FreeBookTrie(book_trie_t **t, int is_view)
{
    int i;
    int alphabet_size = GetAlphabetSize();

    if (*t == NULL)
    {
        return;
    }

    for (i = 0; i < alphabet_size; ++i)
    {
        FreeBookTrie(&(*t)->children[i], is_view);
    }

    FreeBookTrieNode(t, is_view);
}


void PrintBookTrie(book_trie_t *t, int *nb_found, int limit, FILE *fo)
{
    if (t == NULL || (limit >= 0 && *nb_found >= limit))
    {
        return;
    }

    if (t->value)
    {
        PrintBookInfo(t->value, fo);
        (*nb_found)++;
    }

    int alphabet_sz = GetAlphabetSize();
    for (int i = 0; i < alphabet_sz; ++i)
    {
        PrintBookTrie(t->children[i], nb_found, limit, fo);
    }
}


void AddBook(book_trie_t *t, const char *key, book_info_t *value)
{
    int i;
    int len = strlen(key);
    book_trie_t *node = t;

    for (i = 0; i < len; ++i)
    {
        int index = GetIndexOf(key[i]);

        if (node->children[index] == NULL)
        {
            AllocBookTrieNode(&node->children[index]);
        }

        node = node->children[index];
    }

    node->value = value;
}


void SearchBook(book_trie_t *t, const char *key, book_trie_t **out_node)
{
    int i;
    int len = strlen(key);
    book_trie_t *node = t;

    for (i = 0; i < len; ++i)
    {
        int index = GetIndexOf(key[i]);

        if (node->children[index] == NULL)
        {
            // Prefix not in tree
            *out_node = NULL;
            return;
        }

        node = node->children[index];
    }

    // If prefix in tree and is word, node->value is not null.
    // If prefix in tree but is not word, node->value is null.
    *out_node = node;
}
