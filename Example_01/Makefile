CC = gcc
CFLAGS = -fopenmp -Wall -std=c17 -march=native

TARGET = hello_world_openmp

SOURCES = hello_world_openmp.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Compiling $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lm

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./hello_world_openmp.o ./hello_world_openmp