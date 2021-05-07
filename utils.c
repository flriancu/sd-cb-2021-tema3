#include "utils.h"

#include <string.h>


const char * GetAlphabet()
{
    static const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ";

    return alphabet;
}


int GetAlphabetSize()
{
    const char *alphabet = GetAlphabet();

    return (int)strlen(alphabet);
}


int GetIndexOf(char c)
{
    const char *alphabet = GetAlphabet();
    int alphabet_sz = GetAlphabetSize();
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
