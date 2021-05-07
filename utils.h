#ifndef UTILS_H
#define UTILS_H


#define AC_MARKER           '~'


// Debug goodies
#define VERBOSE             0
#define MALLOC(p, sz)       do { (p) = malloc(sz); VERBOSE && printf("* malloc %p %d\n", (p), (int)(sz)); } while ((void)0,0)
#define CALLOC(p, n, sz)    do { (p) = calloc((n), (sz)); VERBOSE && printf("* calloc %p %d*%d=%d\n", (p), (int)(n), (int)(sz), (int)(n*sz)); } while ((void)0,0)
#define FREE(p)             do { free(p); VERBOSE && printf("* free %p\n", (p)); } while ((void)0,0)


const char * GetAlphabet();


const int GetAlphabetSize();


int GetIndexOf(char c);


#endif