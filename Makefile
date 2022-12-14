.PHONY: all
all: main

CC := gcc
override CFLAGS += -g -Wall -Wno-everything -pthread -lm

SRCS := $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS := $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

OBJS := $(SRCS:.c=.o)

src/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

main-debug: $(OBJS)
	$(CC) $(CFLAGS) -O0 $^ -o $@

.PHONY: clean
clean:
	rm -f main main-debug $(OBJS)
