#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*
    Default program for computing integral given as an example
    to modify along the course 'Introduction to OpenMP' by Tim Morrison.
*/
  
static long num_steps = 100000;
double step; 

int main(int argc, char **argv)
{ 
    int i; double x, pi, sum = 0.0;

    step = 1.0/(double) num_steps;

    for(i=0;i<num_steps;i++){
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;

    printf("Result: %f.\n",pi);
} 
