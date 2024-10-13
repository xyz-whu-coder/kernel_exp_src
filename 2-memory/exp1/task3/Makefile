CC=gcc
CCFLAGS=-fPIC -c -Wall
LDFLAGS=-shared -Wl,-soname,libmalloc.so

all: libmalloc.so test
.PHONY: all

libmalloc.so: emalloc.c
	$(CC) $(CCFLAGS) emalloc.c
	$(CC) $(LDFLAGS) -o libmalloc.so

test: test.c
	gcc -o test test.c

clean:
	rm -f *.o test libmalloc.so
.PHONY: clean
