#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*
    The exercise was about taking written code for
    computing numerical integral and make it parallel 
    with instructions covered in the Module 2 :

        - int omp_get_num_threads();
        - int omp_get_thread_num();
        - double omp_get_wtime();

    I kept original serial code to compare its execution 
    with paralleled one. In 9/10 cases, paralleled one worked
    a bit faster in my environment.

    I realise that it should be written with parallel for
    instruction but the part of this exercise was to write 
    the code only with instructions already covered in the course. 
*/
  
static long num_steps = 100000;
double step; 

int main(int argc, char **argv)
{ 
    int i; double x, pi, sum = 0.0;

    step = 1.0/(double) num_steps;

    double start_time = omp_get_wtime();
    
        for(i=0;i<num_steps;i++){
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
        pi = step * sum;
    
    double end_time = omp_get_wtime();
    
    printf("\nResult for structured code is: %f and it was counted in %f seconds.\n",pi,end_time-start_time);

    pi = 0.0;
    start_time,end_time = 0;   

    start_time = omp_get_wtime();
    
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
        pi += step * parallel_sum;
    }
    end_time = omp_get_wtime();

    printf("\nResult for parraled code is: %f and it was counted in %f seconds.\n",pi,end_time-start_time);
} 
