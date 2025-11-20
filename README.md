
# ParallelPrograming


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


# Week 8# Example_05 – MPI Partial Sum using Scatter/Reduce with Timing Analysis

This project implements a parallel partial-sum computation using **MPI (Message Passing Interface)**.  
The program distributes an array of 10,000 elements across multiple processes, computes local partial sums,  
and then aggregates the final result using `MPI_Reduce`.  

To evaluate performance, the execution time of:
- Data distribution (`MPI_Scatter`)
- Local computation on each rank
- Result aggregation (`MPI_Reduce`)

was measured across multiple process counts (1, 2, 4, 8 processes).

All tests were executed in **WSL2 (Ubuntu 24.04) using MPICH**, and the results reflect real runtime behavior on multi-core hardware.

## **Project Structure**

Example_05/
│── PartialSum.c # Main MPI implementation
│── timer.c # Timing utility
│── timer.h
│── Makefile # Build instructions
└── PartialSum # Compiled executable (after make)

## **Building the Project**

Inside the Example_05 directory:
cd Example_05
make
This generates the executable:

./PartialSum
Running the Program
1 Process

mpirun -n 1 ./PartialSum
2 Processes

mpirun -n 2 ./PartialSum
4 Processes

mpirun -n 4 ./PartialSum
8 Processes

mpirun -n 8 ./PartialSum
Performance Results
Below are the real execution results obtained during testing.

1 Process

Scatter: 0.001308 s
Reduce:  0.001396 s
Final sum: 50005000
2 Processes

Run 1:
Scatter: 0.000141 s
Reduce:  0.000007 s

Run 2:
Scatter: 0.000041 s
Reduce:  0.000004 s
4 Processes

Run 1:
Scatter: 0.000121 s
Reduce:  0.000025 s

Run 2:
Scatter: 0.000057 s
Reduce:  0.000006 s

Run 3:
Scatter: 0.000038 s
Reduce:  0.000004 s

Run 4:
Scatter: 0.000052 s
Reduce:  0.000005 s
8 Processes

Run 1:
Scatter: 0.000086 s
Reduce:  0.000006 s

Run 2:
Scatter: 0.000044 s
Reduce:  0.000005 s

Run 3:
Scatter: 0.000085 s
Reduce:  0.000006 s

Run 4:
Scatter: 0.000050 s
Reduce:  0.000006 s

Run 5:
Scatter: 0.000050 s
Reduce:  0.000005 s

Run 6:
Scatter: 0.000046 s
Reduce:  0.000005 s

Run 7:
Scatter: 0.000047 s
Reduce:  0.000004 s

Run 8:
Scatter: 0.000053 s
Reduce:  0.000003 s

Conclusion
As the number of processes increases:
MPI_Scatter time decreases significantly, due to better distribution across more ranks.
MPI_Reduce time also becomes faster, since more processes contribute smaller partial sums.
All executions produced the correct final sum: 50,005,000, confirming correctness of the implementation.
The results clearly show the benefit of parallelism and proper workload distribution in MPI applications.
This implementation follows the course structure, extends the original example with timing instrumentation,
and provides detailed analysis using real-world measurements.
# Screenshots – Execution Results

### 1 Process
![1 Process](screenshots/week8-1.png)

### 2 Processes
![2 Processes](screenshots/week8-2.png)

### 4 Processes
![4 Processes](screenshots/week8-3.png)

### 8 Processes
![8 Processes](screenshots/week8-4.png)

### Additional runs
![Run 5](screenshots/week8-5.png) test


Author
Parallel Computing – Week 8 Assignment
Ali Handan
International Burch University
