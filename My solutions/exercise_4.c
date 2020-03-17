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
    int i; double x, pi, sum = 0.0;

    step = 1.0/(double) num_steps;

    double start_time = omp_get_wtime();

    int threads = 4;

    //omp_set_num_threads(4);
 
    #pragma omp parallel for
    for(i=0;i<num_steps;i++){
        printf("\nIteracja nr %d wykonana prze watek nr %d.",i,omp_get_thread_num());
        
        //x = (i+0.5)*step;
        //sum += 4.0/(1.0+((i+0.5)*step)*((i+0.5)*step));
    }
    pi = step * sum;

    double end_time = omp_get_wtime();

    printf("\nResult for parraled code is: %f and it was counted in %f seconds.\n",pi,end_time-start_time);
} 
