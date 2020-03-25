#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int i;
   int result;
   //struct node* next;
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

void processwork(struct node* fibbonaci, int i) 
{
   fibbonaci->i = i;
   fibbonaci->result = fib(i);
}

// struct node* init_list(struct node* p) {
//     int i;
//     struct node* head = NULL;
//     struct node* temp = NULL;
    
//     head = malloc(sizeof(struct node));
//     p = head;
//     p->data = FS;
//     p->fibdata = 0;
//     for (i=0; i< N; i++) {
//        temp  =  malloc(sizeof(struct node));
//        p->next = temp;
//        p = temp;
//        p->data = FS + i + 1;
//        p->fibdata = i+1;
//     }
//     p->next = NULL;
//     return head;
// }

int main(int argc, char *argv[]) {
   double start, end;
   //   struct node *p=NULL;
   //   struct node *temp=NULL;
   //   struct node *head=NULL;
     
	//  printf("Process linked list\n");
   //   printf("  Each linked list node will be processed by function 'processwork()'\n");
   printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
   
   struct node fibbonaci[N];    
   //   p = init_list(p);
   //   head = p;

   int i;

     start = omp_get_wtime();
     {
        #pragma omp parallel for
        for(i=FS;i<=FS+N;i++)
        {
           printf("i=%d      dla watku %d\n",i,omp_get_thread_num());
           processwork(&fibbonaci[i],i);
           //#pragma omp barrier
        }
      //   while (p != NULL) {
      //      printf("\ndata: %d      | fibdata: %d\n",p->data,p->fibdata);
      //      printf("\ni = %d\n",p);
		//    processwork(p);
		//    p = p->next;
      //   }
     }

     

     end = omp_get_wtime();
   printf("\nResults: \n");

     for(i=FS;i<=FS+N;i++)
      {
         printf("For i value equal to %d fibbonaci result is %d.\n",fibbonaci->i,fibbonaci->result);
      }
   //   p = head;
	//  while (p != NULL) {
   //      printf("%d : %d\n",p->data, p->fibdata);
   //      temp = p->next;
   //      free (p);
   //      p = temp;
   //   }  
	//  free (p);

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}

