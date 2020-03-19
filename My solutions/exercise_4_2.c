#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

/*
    You can find the video with given exercise here:
    
*/
  
static long num_steps = 100000;
double step; 

omp_sched_t get_schema_of_loop();
int get_amount_of(char *picked_item);

int main(int argc, char *argv)
{ 
    int i;
    double pi, sum = 0.0;
    step = 1.0/(double) num_steps;

    char operation[8];
    strcpy(operation, "threads");
    int threads_amount = get_amount_of(operation);

    omp_sched_t loop_schema = get_schema_of_loop();

    strcpy(operation, "chunks");
    int chunks_amount = get_amount_of(operation);

    omp_set_num_threads(threads_amount);
    omp_set_schedule(loop_schema,chunks_amount);

   double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+ : sum)
    for(i=0;i<num_steps;i++){
        sum += 4.0/(1.0+((i+0.5)*step)*((i+0.5)*step));
    }
    pi = step * sum;
    double end_time = omp_get_wtime();

    omp_get_schedule(&loop_schema,&chunks_amount);

    char str_used_schema_type[20];

    switch(loop_schema)
    {
        case omp_sched_static:
            strcpy(str_used_schema_type, "static");  
            break;
        case omp_sched_dynamic:
            strcpy(str_used_schema_type, "dynamic");  
            break;
        case omp_sched_guided:
            strcpy(str_used_schema_type, "guided"); 
            break;
        case omp_sched_auto:
            strcpy(str_used_schema_type, "auto"); 
            break;
        default:
            strcpy(str_used_schema_type, "not defined");
            break;
    }

    printf("\nResult  is: %f. \nAnd it was counted in %f seconds.\n",pi,end_time-start_time);
    printf("It was computed with %d threads, %s schema and %d chunks. \n\n",threads_amount,str_used_schema_type,chunks_amount);
} 

omp_sched_t get_schema_of_loop()
{
    int user_pick = 0;

    while(user_pick<1 || user_pick>4)
    {
        system("@cls||clear");

        printf("\nPick schema type: \n  ");
        printf("    1) static");
        printf("    2) dynamic");
        printf("    3) guided");
        printf("    4) auto\n\n");

        printf("Your pick: ");
        scanf("%d",&user_pick);
    }

    switch(user_pick) 
        {
            case 1:
                return omp_sched_static;
                break;
            case 2: 
                return omp_sched_dynamic;
                break;
            case 3: 
                return omp_sched_guided;
                break;
            case 4: 
                return omp_sched_auto;
                break;
            default:
                system("pause");
                break;
        }
}

int get_amount_of(char *picked_item)
{
    int user_pick = 0;

    while(user_pick<1)
    {
        system("@cls||clear");

        printf("\nPick number of %s",picked_item);
        if(strcmp(picked_item,"threads")==0)
            printf("(suggested %d)",omp_get_max_threads());
        printf(": ",picked_item);

        scanf("%d",&user_pick);
    }

    return user_pick;
}