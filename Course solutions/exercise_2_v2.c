#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*
    Example solution for exercise 2 given in course 
    'Introduction to OpenMP' by Tim Morrison. 
    You can check my solutions in the separated
    catalog in this repository.
*/
  
static long num_steps = 100000;
double step; 
#define PAD 8
#define NUM_THREADS 2

int main(int argc, char **argv)
{ 
    int i, nthreads; 
    double x, pi, sum[NUM_THREADS][PAD];

    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if(id==0)
            nthreads = nthrds;
        
        for(i=id, sum[id][0]=0.0; i<num_steps; i=i+nthrds){
            x = (i+0.5)*step;
            sum[id][0] += 4.0/(1.0+x*x);
        }
    }

    for(i=0, pi=0.0; i<nthreads;i++)
        pi += sum[i][0] * step;

    double end_time = omp_get_wtime();

    printf("\nResult for structured code is: %f and it was counted in %f seconds.\n",pi,end_time-start_time);
} 
