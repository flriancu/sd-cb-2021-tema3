#include "author_trie.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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


void AddAuthor(author_trie_t *t, const char *key, book_info_t *value)
{
    int i;
    int len = strlen(key);
    author_trie_t *node = t;

    for (i = 0; i < len; ++i)
    {
        int index = GetIndexOf(key[i]);

        if (node->children[index] == NULL)
        {
            AllocAuthorTrieNode(&node->children[index]);
        }

        node = node->children[index];
    }

    if (node->value == NULL)
    {
        AllocAuthorInfo(&node->value, key);
    }

    if (node->value->books == NULL)
    {
        AllocBookTrieNode(&node->value->books);
    }

    AddBook(node->value->books, value->title, value);
}


void SearchAuthor(author_trie_t *t, const char *key, author_trie_t **out_node)
{
    int i;
    int len = strlen(key);
    author_trie_t *node = t;

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
