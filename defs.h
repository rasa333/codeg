#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DEFAULT_CHARSET  "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define RAND(x, y)  (lrand48() % ((y) + 1 - (x)) + (x))

#define TRUE   1
#define FALSE  0
#define INVALID -1

#define DEBUG_MSG_FILE   "./htools.debug"
#define _DEBUG_MSG_ 1

#if _DEBUG_MSG_ == 0
#define DEBUG_MSG(x)        fprintf(stderr, "  %s\n", x)
#define DEBUG_MSG_INT(x, y) fprintf(stderr, "  %s: %d\n", x, y)
#define DEBUG_MSG_FLOAT(x, y) fprintf(stderr, "  %s: %f\n", x, y)
#define DEBUG_MSG_STR(x, y) fprintf(stderr, "  %s: \"%s\"\n", x, y)
#define DEBUG_MSG_ARRAY(x, y) {int I; fprintf(stderr, "  %s:\n", x); \
			       if (y == NULL) \
                                 fprintf(stderr, "    NULL\n"); \
			       else \
				 for (I = 0 ; y[I] != NULL ; I++) \
				   fprintf(stderr, "    %d: \"%s\"\n", I, y[I]); \
                               }
#endif

#if _DEBUG_MSG_ == 1
#define DEBUG_MSG(x)          {FILE *F;F = fopen(DEBUG_MSG_FILE, "a");fprintf(F, "[%s] %s\n", stamp(), x);fclose(F);}
#define DEBUG_MSG_INT(x, y)   {FILE *F;F = fopen(DEBUG_MSG_FILE, "a");fprintf(F, "[%s] %s: %d\n", stamp(), x, y);fclose(F);}
#define DEBUG_MSG_STR(x, y)   {FILE *F;F = fopen(DEBUG_MSG_FILE, "a");fprintf(F, "[%s] %s: \"%s\"\n", stamp(), x, y);fclose(F);}
#define DEBUG_MSG_FLOAT(x, y)   {FILE *F;F = fopen(DEBUG_MSG_FILE, "a");fprintf(F, "[%s] %s: \"%f\"\n", stamp(), x, y);fclose(F);}
#define DEBUG_MSG_ARRAY(x, y) {FILE *F;int I;F = fopen(DEBUG_MSG_FILE, "a");fprintf(F, "[%s] %s:\n", stamp(), x); \
			       if (y == NULL) \
                                 fprintf(F, "    NULL\n"); \
			       else \
				 for (I = 0 ; y[I] != NULL ; I++) \
				   fprintf(F, "    %d: \"%s\"\n", I, y[I]); \
                               fclose(F);}
#endif

#ifndef _DEBUG_MSG_
#define DEBUG_MSG(x)          {}
#define DEBUG_MSG_INT(x, y)   {}
#define DEBUG_MSG_STR(x, y)   {}
#define DEBUG_MSG_ARRAY(x, y) {}
#endif

#define max(a, b)   (a > b ? a : b)
#define min(a, b)   (a < b ? a : b)

extern char *trim(char *s);
extern int is_slash(char c);
extern char **split_quoted_words(char *str, char **arg, int *cnt, int (*trunc)(char c));

// file.c

extern int mkdirs(char *dname, int mode);
extern int fget_logline(char *buf, size_t size, FILE *f, int follow_flag);
extern int fget_logline_return(char *buf, size_t size, FILE *f, int follow_flag);
extern char *dirname(char *path);
