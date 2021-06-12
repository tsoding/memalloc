CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -ggdb

heap: main.c
	$(CC) $(CFLAGS) -o heap main.c
