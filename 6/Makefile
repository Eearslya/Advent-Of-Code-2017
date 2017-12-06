CC=g++
CFLAGS=-c -O3 -std=c++14 -Wall -Wextra -Wpedantic -pedantic -pedantic-errors
LDFLAGS=
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
BINARY=solution

all: $(SOURCES) $(BINARY) cleanobj
valgrind: CFLAGS += -g
coverage: CFLAGS += -coverage
coverage: LDFLAGS += -coverage

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

coverage: $(BINARY)

valgrind: $(BINARY)
	valgrind --tool=memcheck --leak-check=full -q ./$(BINARY)

clean: cleanobj cleanemacs cleancov
	rm -f $(BINARY)

cleancov:
	rm -f *.gcno *.gcda src/*.gcno src/*.gcda

cleanobj:
	rm -f $(OBJECTS)

cleanemacs:
	rm -f *~ src/*~
