# Compiler
CC = g++

# Compiler flags
# DOUBLEFLAGS = -DEED_USE_DOUBLE
DOUBLEFLAGS =
CFLAGS = -Wall -Wextra $(DOUBLEFLAGS)

all: testgen testscript

testgen: testgen.o
	$(CC) $(CFLAGS) -o testgen testgen.o

testgen.o: testgen.cpp
	$(CC) $(CFLAGS) -c testgen.cpp

testscript: testscript.o
	$(CC) $(CFLAGS) -o testscript testscript.o

testscript.o: testscript.cpp
	$(CC) $(CFLAGS) -c testscript.cpp

clean:
	rm -f testgen testgen.o testscript testscript.o