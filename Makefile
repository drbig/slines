CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=
STYLE=-nA2s2SHxC100xj
BINDIR=bin
PRG=slines
DEPS=src/lib.o
VERSION=$(shell git describe --tags --always --dirty --match "[0-9A-Z]*.[0-9A-Z]*" || echo unknown)

.PHONY: all version clean style analyze

all: version $(BINDIR)/$(PRG)

version:
	echo "#define VERSION \"$(VERSION)\"" > src/version.h

clean:
	rm -f src/*.o $(BINDIR)/$(PRG)

debug: CFLAGS+=-DDEBUG -g
debug: all

style:
	astyle $(STYLE) src/*.c src/*.h

analyze:
	scan-build --status-bugs make BINDIR=/tmp

$(BINDIR)/$(PRG): $(DEPS)
	mkdir -p $(BINDIR)/
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/$(PRG).c $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
