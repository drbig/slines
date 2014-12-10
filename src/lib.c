// See LICENSE.txt for licensing information.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#include "lib.h"
#define LINESIZ 4096

typedef enum {LOOK, PATH, LINE} state_t;
char buffer[LINESIZ];

match_t find_next(FILE *input) {
  match_t m;
  state_t state;
  int c, p, lp;

  state = LOOK;

  while ((c = fgetc(input)) != EOF) {
    switch (state) {
      case LOOK:
        if (c == '/') {
          m.path[0] = '/';
          p = 1;
          state = PATH;
        }
        break;
      case PATH:
        if (c == ':') {
          m.path[p] = '\0';
          if (access(m.path, F_OK) == -1) {
            state = LOOK;
            break;
          }
          lp = p;
          state = LINE;
          break;
        }
        if ((p < PATH_MAX-1) && isprint(c)) {
          m.path[p] = (char)c;
          p++;
          break;
        }
        state = LOOK;
        break;
      case LINE:
        if ((p < PATH_MAX-1) && isdigit(c)) {
          m.path[p] = (char)c;
          p++;
          break;
        }
        if (p == lp) {
          state = LOOK;
          break;
        }
        m.path[p] = '\0';
        m.line = atoi(&m.path[lp]);
        if (m.line < 0) {
          state = LOOK;
          break;
        }
        m.path[lp] = '\0';
        m.ok = true;
        return m;
    }
  }

  m.ok = false;
  return m;
}

bool print_match(match_t m, int c) {
  FILE *f;
  bool ok;
  int l, s, e;

  ok = true;
  l = 0;
  s = m.line - c;
  e = m.line + c;

  if (s < 1)
    s = 1;

  printf("%s\n", m.path);
  if ((f = fopen(m.path, "r")) == NULL) {
    perror("fopen");
    return false;
  }
  errno = 0;
  while (fgets(buffer, LINESIZ, f) != NULL) {
    l++;
    if ((l >= s) && (l <= e)) {
      if (l == m.line)
        printf("> %4d: %s", l, buffer);
      else
        printf("  %4d: %s", l, buffer);
    }
    if (l > e)
      break;
    errno = 0;
  }
  if (errno != 0) {
    perror("fgets");
    ok = false;
  }
  fclose(f);
  return ok;
}
