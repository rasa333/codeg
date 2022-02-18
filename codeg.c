#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <time.h>

#include "defs.h"
#include "hash.h"

extern char *optarg;
extern int   optind;


static void usage(char *prefix, char *charset)
{
    printf("Usage: codeg [option(s)...] length count\n");
    printf(" -p prefix     set code prefix [%s]\n", prefix == NULL ? "" : prefix);
    printf(" -c charset    set charset-string [%s]\n", charset == NULL ? DEFAULT_CHARSET : charset);
    printf(" -r file       read code list from file\n");
    printf(" -h            this help\n");
}


static char *mkname(char *prefix, char *charset, int length)
{
  char *name;
  int i, charset_length;

  name = malloc(length + 1);        // get memory for the name
  charset_length = strlen(charset) - 1;
  if (prefix != NULL) {
    strcpy(name, prefix);
    i = strlen(prefix);
  } else {
    i = 0;
  }
  for ( ; i < length ; i++)
    name[i] = charset[RAND(0, charset_length)];
  name[i] = 0;

  return name;
}



int main(int argc, char **argv)
{
  int opt, count, n, length;
  char *prefix = NULL, *charset = NULL, *file = NULL, *code, buf[1024], *p;
  FILE *f;

  srand48(time(NULL));
  while((opt = getopt(argc, argv, "p:c:r:h")) != -1) {
    switch(opt) {
    case 'p':
      prefix = strdup(optarg);
      break;
    case 'c':
      charset = strdup(optarg);
      break;
    case 'r':
      file = strdup(optarg);
      break;
    case 'h':
      usage(prefix, charset);
      exit(0);
    default:
      usage(prefix, charset);
      exit(1);
    }
  }
  if (argc != optind + 2) {
    usage(prefix, charset);
    exit(1);
  }
  length = atoi(argv[optind]);
  count = atoi(argv[optind + 1]);

  if (charset == NULL)
    charset = strdup(DEFAULT_CHARSET);

  if (file != NULL) {
    f = fopen(file, "r");
    if (f == NULL) {
      fprintf(stderr, "%s: %s\n", file, strerror(errno));
      exit(1);
    }
    while(fgets(buf, sizeof(buf), f)) {
      p = trim(buf);
      if (!hash_lookup(p))
	hash_install(p);
    }
    fclose(f);
  }

  n = 0;
  do {
    code = mkname(prefix, charset, length);
    if (!hash_lookup(code)) {
      hash_install(code);
      printf("%s\n", code);
      n++;
    }
    free(code);
  } while(n < count);

  exit(0);
}
