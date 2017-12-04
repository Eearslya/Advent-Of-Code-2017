CC=c99
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
BINARY=solution

all: $(SOURCES) $(BINARY) cleanobj
valgrind: CFLAGS += -g
coverage: CFLAGS += -coverage
coverage: LDFLAGS += -coverage

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.c.o:
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
