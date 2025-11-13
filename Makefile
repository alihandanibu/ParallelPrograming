CC = gcc
CFLAGS = -g -O3 -march=native -fopenmp
SOURCES = timer.c malloc2D.c
HEADERS = timer.h malloc2D.h

all: stencil_base stencil_opt4 stencil_opt6

stencil_base: stencil_base.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $< $(SOURCES)

stencil_opt4: stencil_opt4.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $< $(SOURCES)

stencil_opt6: stencil_opt6.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $< $(SOURCES)

run: all
	@echo "=== Running stencil_base ===" > results.txt
	./stencil_base >> results.txt 2>&1
	@echo "" >> results.txt
	@echo "=== Running stencil_opt4 ===" >> results.txt
	./stencil_opt4 >> results.txt 2>&1
	@echo "" >> results.txt
	@echo "=== Running stencil_opt6 ===" >> results.txt
	./stencil_opt6 >> results.txt 2>&1
	@echo "=== RESULTS ==="
	@cat results.txt

clean:
	rm -f stencil_base stencil_opt4 stencil_opt6 results.txt

.PHONY: all run clean
