SRCS=wordsorter.c
CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

ws: $(SRCS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ws
