#include "book_trie.h"
#include "author_trie.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void Test(book_trie_t **books, author_trie_t **authors, FILE *fi, FILE *fo)
{
    const int k_buffer_len = 255;
    char buffer[k_buffer_len];

    while (fgets(buffer, k_buffer_len, fi))
    {
        char *command = strtok(buffer, " ");

        if (0 == strcmp(command, "add_book"))
        {
            char *title = strtok(NULL, ":");
            char *author = strtok(NULL, ":");
            char *rating = strtok(NULL, ":");
            char *nb_pages = strtok(NULL, "\n");

            book_trie_t *book_node;

            SearchBook(*books, title, &book_node);
            if (book_node == NULL || book_node->value == NULL)
            {
                book_info_t *b;

                AllocBookInfo(&b, title, author, (float)atof(rating), atoi(nb_pages));
                AddBook(*books, title, b);
                AddAuthor(*authors, author, b);
            }
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
            SearchBook(*books, search_term, &book_node);
            
            DPRINTF("\n<%s>\n", search_term);
            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                int nb_found = 0;

                DPRINTF("%s\n", MARKER_PREFIX_MATCH);
                PrintBookTrie(book_node, &nb_found, 3, FALSE, fo);

                if (nb_found == 0)
                {
                    fprintf(fo, "Nicio carte gasita.\n");
                }
            }
            else
            {
                DPRINTF("%s\n", MARKER_EXACT_MATCH);

                if (book_node && book_node->value)
                {
                    fprintf(fo, "Informatii recomandare: ");
                    PrintBookInfo(book_node->value, TRUE, fo);
                }
                else
                {
                    fprintf(fo, "Cartea %s nu exista in recomandarile tale.\n", search_term);
                }
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
            SearchAuthor(*authors, search_term, &author_node);

            DPRINTF("\n<%s>\n", search_term);
            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                int nb_found = 0;

                DPRINTF("%s\n", MARKER_PREFIX_MATCH);
                PrintAuthorTrie(author_node, &nb_found, 3, fo);

                if (nb_found == 0)
                {
                    fprintf(fo, "Niciun autor gasit.\n");
                }
            }
            else
            {
                int nb_found = 0;

                DPRINTF("%s\n", MARKER_EXACT_MATCH);
                if (author_node)
                {
                    PrintBookTrie(author_node->value->books, &nb_found, -1, FALSE, fo);
                }
                else
                {
                    fprintf(fo, "Autorul %s nu face parte din recomandarile tale.\n", search_term);
                }
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
            SearchAuthor(*authors, search_term_author, &author_node);

            DPRINTF("\n<%s:%s>\n", search_term_author, search_term_book);
            if (last_char == TOKEN_AUTOCOMPLETE)
            {
                if (search_term_book == NULL)
                {
                    // `search_by_author <prefix_author>~`
                    // same as `list_author <prefix_author>~`
                    int nb_found = 0;

                    DPRINTF("%s\n", MARKER_PREFIX_MATCH);
                    PrintAuthorTrie(author_node, &nb_found, 3, fo);

                    if (nb_found == 0)
                    {
                        fprintf(fo, "Niciun autor gasit.\n");
                    }
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

                        DPRINTF("%s\n", MARKER_PREFIX_MATCH);
                        PrintBookTrie(book_node, &nb_found, 3, FALSE, fo);

                        if (nb_found == 0)
                        {
                            fprintf(fo, "Nicio carte gasita.\n");
                        }
                    }
                    else
                    {
                        DPRINTF("%s\n", MARKER_PREFIX_MATCH);
                        fprintf(fo, "Autorul %s nu face parte din recomandarile tale.\n", search_term_author);
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

                    DPRINTF("%s\n", MARKER_EXACT_MATCH);
                    if (book_node && book_node->value)
                    {
                        fprintf(fo, "Informatii recomandare: ");
                        PrintBookInfo(book_node->value, TRUE, fo);
                    }
                    else
                    {
                        fprintf(fo, "Cartea %s nu exista in recomandarile tale.\n", search_term_book);
                    }
                }
                else
                {
                    DPRINTF("%s\n", MARKER_EXACT_MATCH);
                    fprintf(fo, "Autorul %s nu face parte din recomandarile tale.\n", search_term_author);
                }
            }
        }
        else if (0 == strcmp(command, "delete_book"))
        {
            char *title = strtok(NULL, "\n");

            book_trie_t *book_node;
            SearchBook(*books, title, &book_node);

            if (book_node && book_node->value)
            {
                author_trie_t *author_node;
                SearchAuthor(*authors, book_node->value->author, &author_node);
                DeleteBook(&author_node->value->books, title, TRUE);

                if (author_node->value->books == NULL)
                {
                    DeleteAuthor(authors, author_node->value->name);
                }

                DeleteBook(books, title, FALSE);
            }
            else
            {
                fprintf(fo, "Cartea %s nu exista in recomandarile tale.\n", title);
            }
        }
    }
}


int main(const int argc, const char **argv)
{
    if (!USE_CUSTOM_ARGS)
    {
        if (argc != 3)
        {
            printf("Usage: <app> <input.txt> <output.txt>\n");
            return -1;
        }
    }

    FILE *fi = fopen(USE_CUSTOM_ARGS ? CUSTOM_ARG_INPUT : argv[1], "r");
    if (fi == NULL)
    {
        printf("Could not open input file\n");
        return -1;
    }

    FILE *fo = USE_CUSTOM_ARGS ? stdout : fopen(argv[2], "w");
    if (fo == NULL)
    {
        printf("Could not open output file\n");
        return -1;
    }

    book_trie_t *books;
    author_trie_t *authors;

    AllocBookTrieNode(&books);
    AllocAuthorTrieNode(&authors);

    Test(&books, &authors, fi, fo);

    fclose(fi);
    if (fo != stdout)
    {
        fclose(fo);
    }

    FreeBookTrie(&books, FALSE);
    FreeAuthorTrie(&authors);

    return 0;
}
