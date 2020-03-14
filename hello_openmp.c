#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*
    Default program for verifying if OpenMP works.

    Mac OS Terminal command to compile it with gcc:
    gcc-9 -fopenmp your_open_mp_program_name.c -o output_name

    For more details about compilation process check the README.me 
    file for this repository.
*/

int main(int argc, char **argv)
{ 
    #pragma omp parallel 
    { 
        printf("Hello from thread = %d\n", omp_get_thread_num()); 
    } 
} 
