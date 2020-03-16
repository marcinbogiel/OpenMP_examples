#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*
    The exercise was about uprgrading code of exercise_2.c
    and improving its synchrosnisation between variables
    with constructs covered in given lesson:
        - critical;
        - atomic;
        - barrier;

    I realise that it should be written with parallel for
    instruction but the part of this exercise was to write 
    the code only with instructions already covered in the course. 
*/
  
static long num_steps = 100000;
double step; 

int main(int argc, char **argv)
{ 
    double pi;

    step = 1.0/(double) num_steps;

    double start_time = omp_get_wtime();
    
    #pragma omp parallel num_threads(4)
    {
        int i;
        double parallel_x, parallel_sum = 0;
        int parallel_begin = num_steps/omp_get_num_threads()*omp_get_thread_num();
        int parallel_end = num_steps/omp_get_num_threads()*(omp_get_thread_num()+1);
        
        for(i=parallel_begin;i<parallel_end;i++){
            parallel_x = (i+0.5)*step;
            parallel_sum = parallel_sum + 4.0/(1.0+parallel_x*parallel_x);
        }

        #pragma omp atomic update
            pi += step * parallel_sum;
        
        
    }
    double end_time = omp_get_wtime();

    printf("\nResult for parraled code is: %f and it was counted in %f seconds.\n",pi,end_time-start_time);
} 

