# Variables
CC=gcc
CFLAGS="-Wall"
LDFLAGS="-lm"

# Filenames
EXEC = projet
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Main target
default: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

# Generic rule
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(EXEC) $(OBJECTS)
