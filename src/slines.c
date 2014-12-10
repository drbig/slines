// See LICENSE.txt for licensing information.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "lib.h"
#include "version.h"

void usage(char *name) {
  fprintf(stderr, "Usage: %s [options]\n\n", name);
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "\t-h       - print this message and exit\n");
  fprintf(stderr, "\t-v       - print version and exit\n");
  fprintf(stderr, "\t-f       - just print file paths\n");
  fprintf(stderr, "\t-c LINES - number of context lines (default: 1)\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  match_t m;
  bool f, s, ok;
  int c, o;

  f = ok = true;
  s = false;
  c = 1;

  while ((o = getopt(argc, argv, "hvfc:")) != -1) {
    switch (o) {
      case 'c':
        c = atoi(optarg);
        if (c < 0)
          c = 0;
        break;
      case 'f':
        s = true;
        break;
      case 'v':
        printf("slines %s (c) 2014 Piotr S. Staszewski. See LICENSE.txt\n", VERSION);
        exit(EXIT_SUCCESS);
      case 'h':
      default:
        usage(argv[0]);
        break;
    }
  }

  while (true) {
    m = find_next(stdin);
    if (m.ok) {
      if (s) {
        printf("%s:%d\n", m.path, m.line);
        continue;
      }

      if (f)
        f = false;
      else
        printf("\n");

      ok &= print_match(m, c);
      continue;
    }
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
  }
}
