#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

typedef struct _numbers {
   int n;
   int result;
} numbers;

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

int main(int argc, char *argv[]) {

   int i;
   numbers fibbonaci[N]; 
   double start, end;
   
   printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      

   start = omp_get_wtime();
   {
      #pragma omp parallel for
      for(i=0;i<=N;i++)
      {
         fibbonaci[i].n = FS+i;
         fibbonaci[i].result = fib(FS+i);
      }
   }

   end = omp_get_wtime();
   printf("\nResults: \n");

   for(i=0;i<=N;i++)
   {
      printf("For i value equal to %d fibbonaci result is %d.\n",fibbonaci[i].n,fibbonaci[i].result);
   }

   printf("Compute Time: %f seconds\n", end - start);
   return 0;
}

