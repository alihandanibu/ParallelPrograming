# ParallelPrograming
using this rep for assingments
# ParallelPrograming
using this rep for assingments
assignment1 and 2 done 

student@itcenter-lab128:~/Desktop/parallel programing$ cat -A Makefile
CC = gcc$
CFLAGS = -Wall -Wextra -g -std=c99$
TARGET = memory_demo$
SOURCE = main.c$
$
all: $(TARGET)$
$
$(TARGET): $(SOURCE)$
    $(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)$
$
valgrind: $(TARGET)$
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)$
$
valgrind-simple: $(TARGET)$
    valgrind --tool=memcheck --leak-check=yes ./$(TARGET)$
$
clean:$
    rm -f $(TARGET)$
$
.PHONY: all debug valgrind valgrind-simple clean$

student@itcenter-lab128:~/Desktop/parallel programing$ ^C
student@itcenter-lab128:~/Desktop/parallel programing$ gcc -Wall -Wextra -g -std=c99 -o memory_demo main.c
student@itcenter-lab128:~/Desktop/parallel programing$ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_demo 10
==10059== Memcheck, a memory error detector
==10059== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10059== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==10059== Command: ./memory_demo 10
==10059== 
Value 10 not found in array.
==10059== 
==10059== HEAP SUMMARY:
==10059==     in use at exit: 0 bytes in 0 blocks
==10059==   total heap usage: 2 allocs, 2 frees, 1,064 bytes allocated
==10059== 
==10059== All heap blocks were freed -- no leaks are possible
==10059== 
==10059== For lists of detected and suppressed errors, rerun with: -s
==10059== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) this is when i fixed bugs.
first step is checking for memory is allocated.  for (int i = 0; i <= n; i++) {   // <= n is wrong, should be < n
        arr[i] = i * 10;
    }
this is failed because we have space for 10 elemns by this sintax 11 items are used beacuse it is used = sign so i rewrite it to i<10. that is solution for 2. probllem. 
    free(iarray);
     and solution is so obvious for the last task we use to free space that is allocated. here i provide full snippet of code:
     #include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int ipos = 1, ival;
    int *iarray = (int *) malloc(10 * sizeof(int));
    
    if (iarray == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    if (argc == 2) {
        ival = atoi(argv[1]);
    }

    for (int i = 0; i < 10; i++) {
        iarray[i] = ipos;
    }

    for (int i = 0; i < 10; i++) {
        if (ival == iarray[i]) {
            ipos = i;
        }
    }

    if (ipos != 1) {
        printf("Found ival at index %d\n", ipos);
    } else {
        printf("Value %d not found in array.\n", ival);
    }

    free(iarray);
    
    return 0;
}
## Assignment 2: Performance Limits and Profiling

In this lab I worked on understanding computer hardware performance and system architecture. Here's everything I did step by step:

### Installation and Setup Process

First I installed all the necessary tools and libraries. I downloaded and compiled everything from source:

For Cairo graphics library:
wget https://www.cairographics.org/releases/cairo-1.16.0.tar.xz
tar -xf cairo-1.16.0.tar.xz
cd cairo-1.16.0
./configure --with-x --prefix=/usr/local
make
sudo make install
sudo ldconfig

text

For hwloc hardware discovery tools:
git clone https://github.com/open-mpi/hwloc.git
cd hwloc
sudo apt install -y autoconf automake libtool
./autogen.sh
./configure --prefix=/usr/local --enable-cairo
make
sudo make install

text

The installation created multiple hwloc tools in /usr/local/bin/ including hwloc-info, hwloc-calc, lstopo, and others.

### STREAM Benchmark - Memory Performance

I compiled and ran the STREAM benchmark to measure real-world memory bandwidth:
cd ~/parallel_programming/STREAM
make
./stream_c.exe

text

Got these memory speed results:
- Copy: 14,754.7 MB/s
- Scale: 10,049.7 MB/s
- Add: 10,900.1 MB/s
- Triad: 10,711.8 MB/s

### Hardware Topology Analysis

I used the hwloc tools to analyze my system architecture:
lstopo --version
lstopo

text

I examined the CPU cores, cache hierarchy, and processor layout. The tools showed me how L1, L2, and L3 caches are shared between cores and how the processor organization affects parallel program performance.

### Technical Setup Details
- Used Ubuntu Linux with GCC compiler
- Installed development packages: build-essential, libcairo2-dev, libpng-dev, libx11-dev, libxext-dev
- Configured all tools with proper dependencies
- Successfully built everything from source code

### What I Learned
- How to measure actual memory bandwidth vs theoretical limits
- How to analyze hardware architecture for optimizing parallel programs
- Why cache hierarchy and core connections matter for performance
- How to install and configure complex software tools from source
- How memory bandwidth affects parallel application performance

The repository includes screenshots of my installation process, benchmark results, and hardware analysis.
