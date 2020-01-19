CC=gcc
CFLAGS=-std=c89 -Wall -Wextra -Wno-unused-parameter -g
CFLAGS+=$(shell pkg-config --cflags prs)
LDFLAGS=$(shell pkg-config --libs prs)

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:%.c=%.c.o)
TARGETS=$(SOURCES:%.c=%)

.PHONY: all clean
all: $(TARGETS)

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%: %.c.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f *~ *.o $(TARGETS)
