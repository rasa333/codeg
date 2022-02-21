#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "defs.h"


int is_slash(char c)
{
    return c == '/';
}

char **split_quoted_words(char *str, char **arg, int *cnt, int (*trunc)(char c))
{
    char *tmp = malloc(strlen(str) + 1);
    int i = 0, j = 0;

    if (arg == NULL) {
        arg = malloc(sizeof(char *));
        arg[0] = NULL;
    }

    while (*str) {
        while (*str && (*trunc)(*str) && *str != '"')
            str++;

        if (*str != 0) {
            while (*str && !(*trunc)(*str) && *str != '"')
                tmp[i++] = *str++;
            if (*str == '"') {
                str++;
                while (*str && *str != '"')
                    tmp[i++] = *str++;
                if (*str)
                    str++;
            }
            tmp[i] = 0;
            if (arg[j] == NULL)
                arg[j] = malloc(i + 1);
            else
                arg[j] = realloc(arg[j], i + 1);
            strcpy(arg[j++], tmp);
            i = 0;
        }

        if (j > (*cnt)) {
            arg = realloc(arg, sizeof(char *) * (j + 1));
            arg[j] = NULL;
        }
    }
    if (j < (*cnt)) {
        for (i = j; i < (*cnt); i++) {
            free(arg[i]);
            arg[i] = NULL;
        }
        arg = realloc(arg, sizeof(char *) * (j + 1));
    }
    (*cnt) = j;
    free(tmp);

    return arg;
}

/*
 * frees a char array (char **); last element must be NULL
 */

char **list_free(char **a)
{
    int i;

    if (a == NULL)
        return NULL;

    for (i = 0; a[i] != NULL; i++)
        free(a[i]);
    free(a);

    return NULL;
}

inline char *trim(char *s)
{
    char *p;

    while (isspace(*s))
        s++;

    if (!*s)
        return s;

    p = s;
    while (*p)
        p++;
    p--;
    while (isspace(*p))
        p--;
    *(p + 1) = 0;

    return s;
}