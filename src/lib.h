#ifndef LIB_H
#define LIB_H

#define PATH_MAX 4096

typedef struct match_t {
  char path[PATH_MAX];
  int line;
  bool ok;
} match_t;

match_t find_next(FILE *input);
bool print_match(match_t m, int c);

#endif
