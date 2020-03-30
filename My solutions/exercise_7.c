#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/*
   The exercise was about taking given program for computing Fibonacci 
   numbers and make it parallel with using tasks mechanism built
   in OpenMP.

   This time I cannot call it 'my solution'. I made it compilable
   but I didn't increase performance of the program at all. I was
   able to solve it after taking a glance on course solution. My
   mistake was about not implementing #pragma omp single for while loop
   (when tasks are made). After adding missed tasking, everything 
   worked fine.

   After all, performance of exercise_6 which I made on my own
   was actually the same as this one after using tasks(although it
   required to completely rebuild the program).  

   You can find the video with given exercise here:
   https://www.youtube.com/watch?v=AioeS_Jo0Yg#t=10m02s
*/

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       temp  =  malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     

     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
 
     p = init_list(p);
     head = p;

     start = omp_get_wtime();
     {
        #pragma omp parallel
        #pragma omp single
        {
           while (p != NULL) 
            {
            #pragma omp task firstprivate(p)
            {
               processwork(p);
            }
		         p = p->next;
             
            }
        }
        
     }

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}

