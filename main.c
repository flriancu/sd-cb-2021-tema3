#include "book_trie.h"
#include "author_trie.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
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
        printf("[?] ");                     // autocomplete marker
        PrintBookInfo(t->value, stdout);
        (*nb_found)++;
    }

    int alphabet_sz = GetAlphabetSize();
    for (int i = 0; i < alphabet_sz; ++i)
    {
        ListBooks(t->children[i], nb_found, limit);
    }
}


void Test(book_trie_t *books, author_trie_t *authors)
{
    FILE *fi;
    const int k_buffer_len = 255;
    char buffer[k_buffer_len];

    fi = fopen("commands.txt", "r");
    if (fi == NULL)
    {
        return;
    }

    while (fgets(buffer, k_buffer_len, fi))
    {
        char *command = strtok(buffer, " ");

        if (0 == strcmp(command, "add_book"))
        {
            char *title = strtok(NULL, ":");
            char *author = strtok(NULL, ":");
            char *rating = strtok(NULL, ":");
            char *nb_pages = strtok(NULL, "\n");

            book_info_t *b;

            AllocBookInfo(&b, title, author, (float)atof(rating), atoi(nb_pages));
            AddBook(books, title, b);
        }
        else if (0 == strcmp(command, "search_book"))
        {
            char *search_term = strtok(NULL, "\n");
            char last_char = search_term[strlen(search_term) - 1];

            if (last_char == AC_MARKER)
            {
                search_term[strlen(search_term) - 1] = 0;
            }

            book_info_t *book_info;
            book_trie_t *book_node;
            int ret = SearchBook(books, search_term, &book_info, &book_node);
            
            printf("\n%s:\n", search_term);
            printf("[*] ");                 // exact match marker
            PrintBookInfo(book_info, stdout);

            if (last_char == AC_MARKER)
            {
                int nb_found = 0;
                ListBooks(book_node, &nb_found, 3);
            }
        }
        else if (0 == strcmp(command, "list_author"))
        {
            // TODO
        }
        else if (0 == strcmp(command, "search_by_author"))
        {
            // TODO
        }
        else if (0 == strcmp(command, "delete_book"))
        {
            // TODO
        }
    }

    fclose(fi);
}


int main()
{
    book_trie_t *books;
    author_trie_t *authors;

    AllocBookTrieNode(&books);
    AllocAuthorTrieNode(&authors);

    Test(books, authors);

    FreeBookTrie(&books);
    FreeAuthorTrie(&authors);

    return 0;
}
