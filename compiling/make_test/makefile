CC      = gcc
CFLAGS  = -g -lstdc++
LDFLAGS = -g -lstdc++
all: m

m: foo.o main.cpp
# Commands start with TAB not spaces
		$(CC) $(LDFLAGS) -o $@ $^

foo.o: foo.cpp
		$(CC) $(CFLAGS) -c -o $@ $<

clean: FRC
		rm -f m foo.o

# This pseudo target causes all targets that depend on FRC
# to be remade even in case a file with the name of the target exists.
# This works with any make implementation under the assumption that
# there is no file FRC in the current directory.
FRC:

