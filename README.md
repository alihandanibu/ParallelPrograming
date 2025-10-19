# ParallelPrograming
using this rep for assingments


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
