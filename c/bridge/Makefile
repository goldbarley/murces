CC=gcc
CFLAGS=-Wall -g

all: test_bridge

test_bridge: main.c communciate.c cJSON.c
	$(CC) $(CFLAGS) -o test_bridge main.c communciate.c cJSON.c

clean:
	rm -f test_bridge
