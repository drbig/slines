# slines [![Build Status](https://travis-ci.org/drbig/slines.svg?branch=master)](https://travis-ci.org/drbig/slines)

This should have been there between `cat` and `grep` a long time ago.

## Manpage

<PRE>
SYNOPSIS
       slines [OPTION]...

DESCRIPTION
       slines  reads from standard input and looks for path:line strings (e.g.
       /home/user/hello.c:15) and by default prints  the  file  path  and  the
       indicated  line from that file, with one line before and after that for
       context.

       Note that it will ignore any syntactically valid path:line  strings  if
       the path does not point to an existing file.

OPTIONS
       -h     Display help message and exit.

       -v     Print version and copyright message and exit.

       -f     Just  print  the found path:line. Useful for saving for later or
              additional processing.

       -c LINES
              Set the number of context lines to LINES. This obviously has  no
              effect  if  you used the previous option. Zero is a valid number
              here. Defaults to 1.

              Note that the number of context  lines  is  applied  before  and
              after  the  particular  line, i.e. total number of lines printed
              per file is 2*LINES+1.

NOTES
       This utility is intended for use  with  common  compiler/runtime  error
       messages.  It  assumes  all  data it reads are text and does not bother
       with any defensive mechanisms.

       If for some reason you work with source files that  have  lines  longer
       than  4096  bytes  the  line  counting  may  not work properly. You can
       increase the limit by editing the  source  and  recompiling  (look  for
       LINESIZ).

       Some programs also report column position - this is ignored on purpose.

       Note  that  this  program  does not use heap of its own, nor any str*()
       functions.

AUTHOR
       Written by Piotr S. Staszewski.

COPYRIGHT
       Copyright © 2014 Piotr S. Staszewski. Licensed under a  BSD  two-clause
       license.

SEE ALSO
       <B>grep(1)</B>, <B>head(1)</B>, <B>tail(1)</B>
</PRE>

## Contributing

Follow the usual GitHub development model:

1. Clone the repository
2. Make your changes on a separate branch
3. Make sure you run `make analyze` and `make style` before committing
4. Make a pull request

See licensing for legalese.

## Licensing

Standard two-clause BSD license, see LICENSE.txt for details.

Copyright (c) 2014 Piotr S. Staszewski
