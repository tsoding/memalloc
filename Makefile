CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -ggdb

heap: main.c heap.c heap.h
	$(CC) $(CFLAGS) -o heap main.c heap.c
