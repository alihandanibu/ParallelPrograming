//
// Created by hajro on 12. 11. 2025..
//

#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    #pragma omp parallel num_threads(2) //making parallel region code
    {
        int nthreads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        // if you set "masked" instead of "single", only main thread will print the message
        // also you can set conditional to check if thread_num is equal to 0
        #pragma omp single
        {
            printf("Goodbye slow serial world and Hello OpenMP world\n");
            printf("I have %d thread(s) and my thread id is %d\n",nthreads,thread_id);
        } // When block closes, implicit call to Barrier will be sent
    } // When block closes, implicit call to Barrier will be sent
}