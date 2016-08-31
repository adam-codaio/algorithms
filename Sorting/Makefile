#
# A makefile for running the sorting test harness.
# Adapted from Keith Schwarz's Makefile for CS166.
#

CC = gcc
CFLAGS = -Wall -Wpedantic -std=gnu99 -O0 -g
OBJECTS = harness.o algorithms.o

default: harness

harness: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

harness.o: harness.c algorithms.h

algorithms.o: algorithms.c algorithms.h

clean:
	rm -f harness *.o *~
