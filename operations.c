#include "operations.h"
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
