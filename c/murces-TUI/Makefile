# Compiler
CC = gcc

# Compiler flags: 
# -Wall: show all warnings 
# -g: include debugging information
CFLAGS = -Wall -g

# Libraries to link
LIBS = -lncurses

# Target executable name
TARGET = main

# Build the target
all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LIBS)

# Clean up build files
clean:
	rm -f $(TARGET)

# Run the program
run: all
	./$(TARGET)
