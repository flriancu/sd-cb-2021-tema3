#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define COUNT_OF(arr) (sizeof(arr)/sizeof(arr[0]))


typedef struct book_info_t
{
    int year;
} book_info_t;


typedef struct book_trie_t
{
    int is_word;
    book_info_t *value;
    struct book_trie_t **children;
} book_trie_t;


void PrintBookInfo(const book_info_t *book_info, FILE *fo)
{
    fprintf(fo, "%d", book_info->year);
}


int GetAlphabetSize()
{
    int sz = 0;

    sz += 'z' - 'a' + 1;
    sz += 'Z' - 'A' + 1;
    sz += strlen(".,;:-() ");

    return sz;
}


void AllocTrieNode(book_trie_t **t, const book_info_t *value)
{
    int alphabet_size = GetAlphabetSize();

    *t = malloc(sizeof(book_trie_t));

    (*t)->is_word = 0;
    (*t)->value = NULL;
    (*t)->children = calloc(alphabet_size, sizeof(book_trie_t *));

    if (value)
    {
        (*t)->value = malloc(sizeof(book_info_t));
        memcpy((*t)->value, value, sizeof(book_info_t));
    }
}


void FreeTrieNode(book_trie_t **t)
{
    if ((*t)->children)
    {
        free((*t)->children);
    }

    if ((*t)->value)
    {
        free((*t)->value);
    }

    free(*t);
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


void AddBook(book_trie_t *t, const char *key, const book_info_t *value)
{
    int i;
    int len = strlen(key);
    book_trie_t *node = t;

    for (i = 0; i < len; ++i)
    {
        int index = key[i] - 'a';

        if (node->children[index] == NULL)
        {
            AllocTrieNode(&node->children[index], value);
        }

        node = node->children[index];
    }

    node->is_word = 1;
}


int SearchBook(book_trie_t *t, const char *key, book_info_t **out_value)
{
    int i;
    int len = strlen(key);
    book_trie_t *node = t;

    for (i = 0; i < len; ++i)
    {
        int index = key[i] - 'a';

        if (node->children[index] == NULL)
        {
            *out_value = NULL;
            return 0;
        }

        node = node->children[index];
    }

    if (node && node->is_word)
    {
        *out_value = malloc(sizeof(book_info_t));
        memcpy(*out_value, node->value, sizeof(book_info_t));
        return 1;
    }

    *out_value = NULL;
    return 0;
}


void Test(book_trie_t *books)
{
    char *keys[] = {
        "lorelei",
        "la lilieci",
        "la medeleni",
    };

    book_info_t values[COUNT_OF(keys)] = {
        { .year=1935 },
        { .year=1973 },
        { .year=1925 },
    };

    char *searches[] = {
        "l", 
        "la", 
        "la ", 
        "la medeleni", 
        "lo",
        "lorelei",
        "la lilieci"
    };

    // -------------------------------------------------------

    for (int i = 0; i < COUNT_OF(keys); ++i)
    {
        AddBook(books, keys[i], &values[i]);
    }

    for (int i = 0; i < COUNT_OF(searches); ++i)
    {
        book_info_t *book_info;
        int ret = SearchBook(books, searches[i], &book_info);
        
        printf("%20s: ", searches[i]);
        ret ? PrintBookInfo(book_info, stdout) : printf("-");
        printf("\n");

        free(book_info);
    }
}


int main()
{
    book_trie_t *books;

    AllocTrieNode(&books, NULL);

    Test(books);

    FreeTrie(&books);

    return 0;
}
