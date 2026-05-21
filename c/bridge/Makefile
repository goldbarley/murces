CC=gcc
CFLAGS=-Wall -g -lpthread

all: test_bridge

test_bridge: main.c communciate.c cJSON.c router.c log.c
	$(CC) $(CFLAGS) -o test_bridge main.c communciate.c cJSON.c router.c log.c

clean:
	rm -f test_bridge
