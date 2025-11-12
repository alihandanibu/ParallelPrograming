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
        printf("Goodbye slow serial world and Hello OpenMP world\n");
        printf("I have %d thread(s) and my thread id is %d\n",nthreads,thread_id);
    } // When block closes, implicit call to Barrier will be sent
}