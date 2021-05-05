#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define COUNT_OF(arr) (sizeof(arr)/sizeof(arr[0]))


typedef struct book_info_t
{
    char *author;
    float rating;
    int nb_pages;
} book_info_t;


typedef struct book_trie_t
{
    int is_word;
    book_info_t *value;
    struct book_trie_t **children;
} book_trie_t;


#define MALLOC(p, sz)       do { (p) = malloc(sz); 0 && printf("* malloc %p %d\n", (p), (int)(sz)); } while ((void)0,0)
#define CALLOC(p, n, sz)    do { (p) = calloc((n), (sz)); 0 && printf("* calloc %p %d*%d=%d\n", (p), (int)(n), (int)(sz), (int)(n*sz)); } while ((void)0,0)
#define FREE(p)             do { free(p); 0 && printf("* free %p\n", (p)); } while ((void)0,0)


void PrintBookInfo(const book_info_t *book_info, FILE *fo)
{
    fprintf(fo, "[%s] [%d pg.] %.2f",
        book_info->author,
        book_info->nb_pages,
        book_info->rating);
}


const char * GetAlphabet()
{
    static const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ";

    return alphabet;
}


const int GetAlphabetSize()
{
    const char *alphabet = GetAlphabet();

    return (int)strlen(alphabet);
}


int GetIndexOf(char c)
{
    const char *alphabet = GetAlphabet();
    const int alphabet_sz = GetAlphabetSize();
    int pos = 0;

    for (int i = 0; i < alphabet_sz; ++i)
    {
        if (c == alphabet[i])
        {
            pos = i;
            break;
        }
    }

    return pos;
}


void AllocBookInfo(book_info_t **b, char *author, float rating, int nb_pages)
{
    MALLOC(*b, sizeof(book_info_t));
    MALLOC((*b)->author, sizeof(char) * (strlen(author) + 1));

    memcpy((*b)->author, author, sizeof(char) * (strlen(author) + 1));
    (*b)->rating = rating;
    (*b)->nb_pages = nb_pages;
}


void FreeBookInfo(book_info_t **b)
{
    FREE((*b)->author);
    FREE(*b);
    *b = NULL;
}


void AllocTrieNode(book_trie_t **t)
{
    int alphabet_size = GetAlphabetSize();

    MALLOC(*t, sizeof(book_trie_t));

    (*t)->is_word = 0;
    (*t)->value = NULL;
    CALLOC((*t)->children, alphabet_size, sizeof(book_trie_t *));
}


void FreeTrieNode(book_trie_t **t)
{
    if ((*t)->children)
    {
        FREE((*t)->children);
    }

    if ((*t)->value)
    {
        FreeBookInfo(&(*t)->value);
    }

    FREE(*t);
    *t = NULL;
}


void FreeTrie(book_trie_t **t)
{
    int i;
    int alphabet_size = GetAlphabetSize();

    if (*t == NULL)
    {
        return;
    }

    for (i = 0; i < alphabet_size; ++i)
    {
        FreeTrie(&(*t)->children[i]);
    }

    FreeTrieNode(t);
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
            AllocTrieNode(&node->children[index]);
        }

        node = node->children[index];
    }

    node->value = value;
    node->is_word = 1;
}


int SearchBook(book_trie_t *t, const char *key, book_info_t **out_value)
{
    int i;
    int len = strlen(key);
    book_trie_t *node = t;

    for (i = 0; i < len; ++i)
    {
        int index = GetIndexOf(key[i]);

        if (node->children[index] == NULL)
        {
            *out_value = NULL;
            return 0;
        }

        node = node->children[index];
    }

    if (node && node->is_word)
    {
        *out_value = node->value;
        return 1;
    }

    *out_value = NULL;
    return 0;
}


void Test(book_trie_t *books)
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

            AllocBookInfo(&b, author, (float)atof(rating), atoi(nb_pages));
            AddBook(books, title, b);
        }
        else if (0 == strcmp(command, "search_book"))
        {
            char *search_term = strtok(NULL, "\n");
            char last_char = search_term[strlen(search_term) - 1];

            if (last_char == '~')
            {
                // TODO
                search_term[strlen(search_term) - 1] = 0;
            }
            else
            {
                // TODO
            }

            book_info_t *book_info;
            int ret = SearchBook(books, search_term, &book_info);
            
            printf("%20s: ", search_term);
            ret ? PrintBookInfo(book_info, stdout) : printf("-");
            printf("\n");
        }
        else if (0 == strcmp(command, "list_author"))
        {
            // TODO
        }
    }

    fclose(fi);
}


int main()
{
    book_trie_t *books;

    AllocTrieNode(&books);

    Test(books);

    FreeTrie(&books);

    return 0;
}
