
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
For this lab I worked on understanding computer hardware performance and system architecture. Here's what I did:

First I installed all the needed tools and libraries. I downloaded and compiled everything from source code.

For the Cairo graphics library I used these commands:
wget https://www.cairographics.org/releases/cairo-1.16.0.tar.xz
tar -xf cairo-1.16.0.tar.xz
cd cairo-1.16.0
./configure --with-x --prefix=/usr/local
make
sudo make install
sudo ldconfig

For the hwloc hardware discovery tools I did:
git clone https://github.com/open-mpi/hwloc.git
cd hwloc
sudo apt install -y autoconf automake libtool
./autogen.sh
./configure --prefix=/usr/local --enable-cairo
make
sudo make install

The installation set up multiple hwloc tools in /usr/local/bin/ like hwloc-info, hwloc-calc, lstopo, and others.

I tested that hwloc worked:
lstopo --version
lstopo

Next I ran the STREAM benchmark to test memory bandwidth performance:
cd ~/parallel_programming/STREAM
make
./stream_c.exe

I got these memory speed results:
Copy: 14,754.7 MB/s
Scale: 10,049.7 MB/s
Add: 10,900.1 MB/s
Triad: 10,711.8 MB/s

Then I set up the Roofline performance analysis tool:
cd ~/ParallelPrograming
git clone https://bitbucket.org/berkeleylab/cs-roofline-toolkit.git
cd cs-roofline-toolkit/Empirical_Roofline_Tool-1.1.0
cp Config/config.madonna.lbl.gov.01 Config/my_config

I installed MPI support and configured the tool:
sudo apt install -y libopenmpi-dev openmpi-bin
nano Config/my_config

Then I ran the Roofline analysis:
./ert Config/my_config

The tool completed successfully and generated these results:
Empirical roofline graph: 'Results.my_computer/Run.002/roofline.ps'
Empirical roofline database: 'Results.my_computer/Run.002/roofline.json'

I also installed additional profiling tools:
sudo apt install -y kcachegrind valgrind
git clone --recursive https://github.com/UK-MAC/CloverLeaf.git

All the work was done on Ubuntu Linux with GCC compiler. I installed various development packages and got all the tools configured properly.

From this lab I learned how to measure real memory bandwidth, how to analyze computer hardware for parallel programming, why cache organization matters for performance, how to use performance profiling tools, and how to work with complex software tools and benchmarks.

The repository has screenshots showing my installation steps, benchmark results, hardware analysis, and the roofline performance graph.
## Screenshots

![STREAM Benchmark Results](Screenshot%20from%202025-10-16%2015-22-15.png)
![Hardware Topology](Screenshot%20from%202025-10-16%2015-25-28.png)
![Roofline Performance Graph](Screenshot%20from%202025-10-16%2016-38-26.png)
