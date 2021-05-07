#include "commands.h"


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


int SearchBook(book_trie_t *t, const char *key, book_info_t **out_value, book_trie_t **out_node)
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
            *out_value = NULL;
            return 0;
        }

        node = node->children[index];
    }

    if (node->value)
    {
        // Prefix in tree and is word
        *out_node = node;
        *out_value = node->value;
        return 1;
    }

    // Prefix in tree but is not word
    *out_node = node;
    *out_value = NULL;
    return 0;
}


void ListBooks(book_trie_t *t, int *nb_found, int limit)
{
    if (t == NULL || *nb_found >= limit)
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
