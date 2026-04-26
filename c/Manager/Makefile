# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
BUILD_DIR = target
TARGET = $(BUILD_DIR)/my_program
SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: clean $(TARGET)

# Create the directory and link objects
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files (removes the entire target folder)
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(OBJS)

.PHONY: all clean
