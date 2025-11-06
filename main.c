#include <stdio.h>
#include <stdlib.h>
#include "timestep.h"

#define NCells 80000000
#define NTIMES 16

int main() {
    int* celltype = malloc(NCells * sizeof(int));
    double* H = malloc(NCells * sizeof(double));
    double* U = malloc(NCells * sizeof(double));
    double* V = malloc(NCells * sizeof(double));
    double* dx = malloc(NCells * sizeof(double));
    double* dy = malloc(NCells * sizeof(double));
    
    for (int i = 0; i < NCells; i++) {
        celltype[i] = (i % 10 != 0) ? 1 : 0;
        H[i] = 1.0 + (i % 100) * 0.01;
        U[i] = 0.1 + (i % 50) * 0.02;
        V[i] = 0.05 + (i % 70) * 0.015;
        dx[i] = 0.1;
        dy[i] = 0.1;
    }
    
    double total_time = 0.0;
    for (int k = 0; k < NTIMES; k++) {
        double dt = timestep(NCells, 9.81, 0.4, celltype, H, U, V, dx, dy);
        total_time += dt;
    }
    
    printf("Final result: %lf\n", total_time);
    
    free(celltype); free(H); free(U); free(V); free(dx); free(dy);
    return 0;
}
