#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv) {
    double globalSum = 0.0;
    int N = 1000000, THREAD = 64;
    omp_set_num_threads(THREAD);
    double start = omp_get_wtime();
    #pragma omp parallel num_threads(THREAD)
    {
        double localSum = 0.0;
        int localHead = (N / THREAD) * omp_get_thread_num();
        int localTail = (N / THREAD) * (omp_get_thread_num() + 1);
        double factor = 1.0;
        for (int i = localHead; i < localTail; i++) {
            localSum += factor / (2 * i + 1);
            factor = -factor;
        }
        localSum *= 4.0;
        #pragma omp critical 
        {
            globalSum += localSum;
        }
        printf("Processor %d out of %d sum: %f\n", omp_get_thread_num(), THREAD, localSum);
    }
    double end = omp_get_wtime() - start;
    printf("Final estimated results with n = %d : %f\n", N, globalSum);
    printf("Time: %f\n", end);
    printf("Author: B0829002 廖洺玄(Ming-Hsuan Liao)\n");
    return 0;
}