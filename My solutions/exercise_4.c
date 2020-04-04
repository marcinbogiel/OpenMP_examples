#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*

    The exercise was about taking written serial code for
    numerical integral computing and making it parallel 
    with a 'parallel for' construct. The main purpose of the 
    task itself was to use instructions covered in two previous 
    lessons of the course:
        - schedule clauses(with parameters);
        - reduction (picked in right place);

    You can find the video with given exercise here:
    https://www.youtube.com/watch?v=iPb6OLhDEmM#t=6m11s
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
        sum += 4.0/(1.0+((i+0.5)*step)*((i+0.5)*step));
    }
    pi = step * sum;

    double end_time = omp_get_wtime();

    printf("\nResult for parraled code is: %f and it was counted in %f seconds.\n",pi,end_time-start_time);
} 
