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
