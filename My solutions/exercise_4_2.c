#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

/*

    

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

    omp_set_num_threads(4);

    omp_sched_t loop_schema = omp_sched_dynamic;
    int chunks = 4;
    omp_set_schedule(loop_schema,chunks);
    /*
        Avaiable schedule types for omp_set_schedule:
            - omp_sched_static;
            - omp_sched_dynamic; 
            - omp_sched_guided; 
            - omp_sched_auto;

        Chunks is amount of subgroups...
    */

    #pragma omp parallel for schedule(static, 4) reduction(+ : sum)
    for(i=0;i<num_steps;i++){
        sum += 4.0/(1.0+((i+0.5)*step)*((i+0.5)*step));
    }
    pi = step * sum;

    double end_time = omp_get_wtime();

    //loop_schema = omp_get_schedule();

    printf("\n");

    //printf(omp_get_schedule());

    printf("\n");

    printf("\nResult for parraled code is: %f with  and it was counted in %f seconds.\n",pi,end_time-start_time);
} 
