#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*
    bbbb
*/
  
static long num_steps = 100000;
double step; 

int main(int argc, char **argv)
{ 
    int i;
    double pi, sum = 0.0;

    step = 1.0/(double) num_steps;

    double start_time = omp_get_wtime();

    #pragma omp parallel for schedule(static, 4) reduction(+ : sum)
    for(i=0;i<num_steps;i++){
        //printf("\nIteracja nr %d wykonana prze watek nr %d.",i,omp_get_thread_num());
        
        sum += 4.0/(1.0+((i+0.5)*step)*((i+0.5)*step));
    }
    pi = step * sum;

    double end_time = omp_get_wtime();

    printf("\nResult for parraled code is: %f and it was counted in %f seconds.\n",pi,end_time-start_time);
} 
