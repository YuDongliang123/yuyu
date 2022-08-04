CC := gcc

all:
	$(CC) client*.c sqlite.c -o cli -l sqlite3
	$(CC) client*.c sqlite.c -o cli_2 -l sqlite3
	$(CC) server*.c sqlite.c -o ser -l sqlite3
clean:
	rm cli
	rm cli_2
	rm ser
