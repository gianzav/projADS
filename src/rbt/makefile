CFLAGS=-std=c++11
OBJ=Node.o es21.o
DEPS=Node.h

all: $(OBJ)
	clang++ Node.o es21.o -o es21

.o: .cpp $(DEPS)
	clang++ -c -o %@ @<

debug:
	clang++ -g -c Node.cpp -o Node.o
	clang++ -g -c es21.cpp -o es21.o
	clang++ Node.o es21.o -o es21
