#include "book_trie.h"
#include "author_trie.h"
#include "commands.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
