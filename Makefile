CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: circular2LL

circular2LL: circular2LL.c
	$(CC) $(CFLAGS) -o circular2LL circular2LL.c

clean:
	rm -f circular2LL