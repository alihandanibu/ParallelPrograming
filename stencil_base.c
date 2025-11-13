#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "malloc2D.h"
#include "timer.h"

#define SWAP_PTR(xnew,xold,xtmp) (xtmp=xnew, xnew=xold, xold=xtmp)

int main(int argc, char *argv[])
{
    #pragma omp parallel
    if (omp_get_thread_num() == 0) printf("Running with %d thread(s)\n",omp_get_num_threads());

    struct timespec tstart;
    double total_time = 0.0;
    int imax=2002, jmax = 2002;

    double** xtmp;
    double** x = malloc2D(jmax, imax);
    double** xnew = malloc2D(jmax, imax);

    // Serial initialization (no first-touch)
    for (int j = 0; j < jmax; j++){
        for (int i = 0; i < imax; i++){
            xnew[j][i] = 0.0;
            x[j][i] = 5.0;
        }
    }

    for (int j = jmax/2 - 5; j < jmax/2 + 5; j++){
        for (int i = imax/2 - 5; i < imax/2 -1; i++){
            x[j][i] = 400.0;
        }
    }

    cpu_timer_start(&tstart);
    for (int iter = 0; iter < 1000; iter++){  // Fewer iterations for testing
        #pragma omp parallel for
        for (int j = 1; j < jmax-1; j++){
            for (int i = 1; i < imax-1; i++){
                xnew[j][i] = ( x[j][i] + x[j][i-1] + x[j][i+1] + x[j-1][i] + x[j+1][i] )/5.0;
            }
        }
        SWAP_PTR(xnew, x, xtmp);
        if (iter%100 == 0) printf("Iter %d\n",iter);
    }
    total_time = cpu_timer_stop(tstart);

    printf("Total time: %f seconds\n", total_time);

    free(x);
    free(xnew);
}
