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

    struct timespec tstart_init, tstart_flush, tstart_stencil, tstart_total;
    double init_time = 0.0, flush_time = 0.0, stencil_time = 0.0, total_time = 0.0;
    int imax=2002, jmax = 2002;

    double** xtmp;
    double** x = malloc2D(jmax, imax);
    double** xnew = malloc2D(jmax, imax);
    int *flush = (int *)malloc(jmax*imax*sizeof(int)*4);

    cpu_timer_start(&tstart_total);
    
    // High-level OpenMP: Single parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        // Work distribution for first-touch
        int jstart = (jmax * thread_id) / nthreads;
        int jend = (jmax * (thread_id + 1)) / nthreads;

        if (thread_id == 0) cpu_timer_start(&tstart_init);
        
        // First-touch with work distribution
        for (int j = jstart; j < jend; j++){
            for (int i = 0; i < imax; i++){
                xnew[j][i] = 0.0;
                x[j][i] = 5.0;
            }
        }

        // Hot spot initialization
        int hot_jstart = jmax/2 - 5;
        int hot_jend = jmax/2 + 5;
        int hot_istart = imax/2 - 5;
        int hot_iend = imax/2 - 1;
        
        if (thread_id == 0) {
            for (int j = hot_jstart; j < hot_jend; j++){
                for (int i = hot_istart; i < hot_iend; i++){
                    x[j][i] = 400.0;
                }
            }
        }
        
        #pragma omp barrier
        if (thread_id == 0) init_time = cpu_timer_stop(tstart_init);

        // Main computation loop
        for (int iter = 0; iter < 1000; iter++){  // Fewer iterations for testing
            if (thread_id == 0) cpu_timer_start(&tstart_flush);
            
            // Flush with nowait
            #pragma omp for nowait
            for (int l = 1; l < jmax*imax*4; l++){
                flush[l] = 1.0;
            }
            
            if (thread_id == 0){
                flush_time += cpu_timer_stop(tstart_flush);
                cpu_timer_start(&tstart_stencil);
            }
            
            // Stencil computation with work distribution
            #pragma omp for nowait
            for (int j = 1; j < jmax-1; j++){
                for (int i = 1; i < imax-1; i++){
                    xnew[j][i] = ( x[j][i] + x[j][i-1] + x[j][i+1] + x[j-1][i] + x[j+1][i] )/5.0;
                }
            }
            
            #pragma omp barrier
            
            if (thread_id == 0){
                stencil_time += cpu_timer_stop(tstart_stencil);
                SWAP_PTR(xnew, x, xtmp);
                if (iter%100 == 0) printf("Iter %d\n",iter);
            }
            #pragma omp barrier
        }
    }
    total_time = cpu_timer_stop(tstart_total);

    printf("Timing: init %f flush %f stencil %f total %f\n",
           init_time,flush_time,stencil_time,total_time);

    free(x);
    free(xnew);
    free(flush);
}
