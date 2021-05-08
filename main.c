#include "book_trie.h"
#include "author_trie.h"
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
            AddAuthor(authors, author, b);
        }
        else if (0 == strcmp(command, "search_book"))
        {
            char *search_term = strtok(NULL, "\n");
            char last_char = search_term[strlen(search_term) - 1];

            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                search_term[strlen(search_term) - 1] = 0;
            }

            book_trie_t *book_node;
            SearchBook(books, search_term, &book_node);
            
            printf("\n<%s>\n", search_term);
            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                int nb_found = 0;

                printf("%s\n", MARKER_PREFIX_MATCH);
                PrintBookTrie(book_node, &nb_found, 3, stdout);
            }
            else
            {
                printf("%s\n", MARKER_EXACT_MATCH);
                PrintBookInfo(book_node ? book_node->value : NULL, stdout);
            }
        }
        else if (0 == strcmp(command, "list_author"))
        {
            char *search_term = strtok(NULL, "\n");
            char last_char = search_term[strlen(search_term) - 1];

            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                search_term[strlen(search_term) - 1] = 0;
            }

            author_trie_t *author_node;
            SearchAuthor(authors, search_term, &author_node);

            printf("\n<%s>\n", search_term);
            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                int nb_found = 0;

                printf("%s\n", MARKER_PREFIX_MATCH);
                PrintAuthorTrie(author_node, &nb_found, 3, stdout);
            }
            else
            {
                int nb_found = 0;

                printf("%s\n", MARKER_EXACT_MATCH);
                PrintBookTrie(author_node ? author_node->value->books : NULL, &nb_found, -1, stdout);
            }
        }
        else if (0 == strcmp(command, "search_by_author"))
        {
            char *search_term_author = strtok(NULL, ":\n");
            char *search_term_book = strtok(NULL, "\n");
            char *last_search_term;
            
            if (search_term_book == NULL)
            {
                last_search_term = search_term_author;
            }
            else
            {
                last_search_term = search_term_book;
            }

            char last_char = last_search_term[strlen(last_search_term) - 1];

            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                last_search_term[strlen(last_search_term) - 1] = 0;
            }

            author_trie_t *author_node;
            SearchAuthor(authors, search_term_author, &author_node);

            printf("\n<%s:%s>\n", search_term_author, search_term_book);
            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                if (search_term_book == NULL)
                {
                    // `search_by_author <prefix_author>~`
                    // same as `list_author <prefix_author>~`
                    int nb_found = 0;

                    printf("%s\n", MARKER_PREFIX_MATCH);
                    PrintAuthorTrie(author_node, &nb_found, 3, stdout);
                }
                else
                {
                    // `search_by_author <author>:<prefix_title>~`
                    // similar to `search_book <prefix_title>~`
                    if (author_node)
                    {
                        book_trie_t *book_node;
                        SearchBook(author_node->value->books, search_term_book, &book_node);

                        int nb_found = 0;

                        printf("%s\n", MARKER_PREFIX_MATCH);
                        PrintBookTrie(book_node, &nb_found, 3, stdout);
                    }
                    else
                    {
                        printf("%s\n", MARKER_PREFIX_MATCH);
                        printf("-\n");
                    }
                }
            }
            else
            {
                // `search_by_author <author>:<title>`
                if (author_node)
                {
                    book_trie_t *book_node;
                    SearchBook(author_node->value->books, search_term_book, &book_node);

                    printf("%s\n", MARKER_EXACT_MATCH);
                    PrintBookInfo(book_node ? book_node->value : NULL, stdout);
                }
                else
                {
                    printf("%s\n", MARKER_EXACT_MATCH);
                    printf("-\n");
                }
            }
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

    FreeBookTrie(&books, FALSE);
    FreeAuthorTrie(&authors);

    return 0;
}
