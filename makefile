CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = memory_demo
SOURCE = main.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)   

valgrind-simple: $(TARGET)
	valgrind --tool=memcheck --leak-check=yes ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all debug valgrind valgrind-simple clean

