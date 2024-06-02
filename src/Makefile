# Compiler
CC = g++

# Compiler flags
# DOUBLEFLAGS = -DEED_USE_DOUBLE
DOUBLEFLAGS =
CFLAGS = -Wall -Wextra $(DOUBLEFLAGS)

all: test

test: test.o
	$(CC) $(CFLAGS) -o test test.o

test.o: test.cpp Distance.h Vector.h
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f test test.o