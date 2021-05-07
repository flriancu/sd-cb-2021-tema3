#include "commands.h"
#include "author.h"

#include <string.h>


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


void ListBooks(book_trie_t *t, int *nb_found, int limit)
{
    if (t == NULL || (limit >= 0 && *nb_found >= limit))
    {
        return;
    }

    if (t->value)
    {
        printf("[?] ");                 // autocomplete marker
        PrintBookInfo(t->value, stdout);
        (*nb_found)++;
    }

    int alphabet_sz = GetAlphabetSize();
    for (int i = 0; i < alphabet_sz; ++i)
    {
        ListBooks(t->children[i], nb_found, limit);
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
        AllocBookTrieNode(&node->value);
    }

    AddBook(node->value, value->title, value);
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


void ListAuthors(author_trie_t *t, int *nb_found, int limit)
{
    if (t == NULL || (limit >= 0 && *nb_found >= limit))
    {
        return;
    }

    if (t->value)
    {
        printf("[?] ");                 // autocomplete marker
        PrintAuthorInfo(t->value ? t->value->value : NULL, stdout);
        (*nb_found)++;
    }

    int alphabet_sz = GetAlphabetSize();
    for (int i = 0; i < alphabet_sz; ++i)
    {
        ListAuthors(t->children[i], nb_found, limit);
    }
}
