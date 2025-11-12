CC = gcc
CFLAGS = -fopenmp -Wall -std=c11 -march=native

TARGET = openmp_parallel_region_fix2

SOURCES = openmp_parallel_region_fix2.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lm

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)

.PHONY: all clean