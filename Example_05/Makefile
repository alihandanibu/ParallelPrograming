CC = gcc
CFLAGS = -fopenmp -Wall -std=c11 -march=native -O2

# Source files (excluding timer which is a utility)
SOURCES = vecadd.c vecadd_opt1.c vecadd_opt2.c

# Generate executable names (remove .c extension)
EXECUTABLES = $(SOURCES:.c=)

# Utility object file
TIMER_OBJ = timer.o

# Default target: build all executables
all: $(EXECUTABLES)
	@echo "All executables built successfully!"

# Rule to build each executable
# Each depends on its .c file and timer.o
vecadd: vecadd.c $(TIMER_OBJ)
	@echo "Building $@..."
	$(CC) $(CFLAGS) $< $(TIMER_OBJ) -o $@ $(LDFLAGS) -lm

vecadd_opt1: vecadd_opt1.c $(TIMER_OBJ)
	@echo "Building $@..."
	$(CC) $(CFLAGS) $< $(TIMER_OBJ) -o $@ $(LDFLAGS)

vecadd_opt2: vecadd_opt2.c $(TIMER_OBJ)
	@echo "Building $@..."
	$(CC) $(CFLAGS) $< $(TIMER_OBJ) -o $@ $(LDFLAGS)

# Compile timer.c into timer.o
$(TIMER_OBJ): timer.c timer.h
	@echo "Compiling timer..."
	$(CC) $(CFLAGS) -c timer.c -o $(TIMER_OBJ)

# Run targets (optional - for convenience)
run-vecadd: vecadd
	@echo "Running vecadd..."
	./vecadd

run-vecadd_opt1: vecadd_opt1
	@echo "Running vecadd_opt1..."
	./vecadd_opt1

run-vecadd_opt2: vecadd_opt2
	@echo "Running vecadd_opt2..."
	./vecadd_opt2

# Clean up
clean:
	@echo "Cleaning up..."
	rm -f $(EXECUTABLES) $(TIMER_OBJ)

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild run-vecadd run-vecadd_opt1 run-vecadd_opt2