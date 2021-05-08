#ifndef UTILS_H
#define UTILS_H


#define TOKEN_AUTOCOMPLETE      '~'

#define TRUE                    (1)
#define FALSE                   (0)

#define IN
#define OUT


const char * GetAlphabet();


int GetAlphabetSize();


int GetIndexOf(char c);


// Debug goodies
#define VERBOSE_MEMORY          (0)
#define VERBOSE_DEBUG           (1)

#define MALLOC(p, sz)           do { (p) = malloc(sz); VERBOSE_MEMORY && printf("* malloc %p %d\n", (p), (int)(sz)); } while ((void)0,0)
#define CALLOC(p, n, sz)        do { (p) = calloc((n), (sz)); VERBOSE_MEMORY && printf("* calloc %p %d*%d=%d\n", (p), (int)(n), (int)(sz), (int)(n*sz)); } while ((void)0,0)
#define FREE(p)                 do { free(p); VERBOSE_MEMORY && printf("* free %p\n", (p)); } while ((void)0,0)

#define MARKER_EXACT_MATCH      "[*]"
#define MARKER_PREFIX_MATCH     "[?]"
#define MARKER_DELETE_MATCH     "[-]"

#define DPRINTF(...)            do { VERBOSE_DEBUG && printf(__VA_ARGS__); } while ((void)0,0)


#endif
