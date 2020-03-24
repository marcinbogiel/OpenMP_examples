#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NPOINTS 1000
#define MAXITER 1000

struct d_complex{
    double real;
    double imaginary;
};

void testpoint(struct d_complex);

struct d_complex complex;
int numoutside = 0;

int main(){
   int i, j;
   double area, error, eps  = 1.0e-5;

#pragma omp parallel for default(shared) firstprivate(eps) private(complex,j)
    for (i=0; i<NPOINTS; i++) 
    {
        for (j=0; j<NPOINTS; j++) 
        {
            complex.real = -2.0+2.5*(double)(i)/(double)(NPOINTS)+eps;
            complex.imaginary = 1.125*(double)(j)/(double)(NPOINTS)+eps;
            testpoint(complex);
        }
   }
   
  area=2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
  error=area/(double)NPOINTS;

  printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
}

void testpoint(struct d_complex complex)
{
    struct d_complex z;
    int iter;
    double temp;

    z=complex;
    for (iter=0; iter<MAXITER; iter++){
        temp = (z.real*z.real)-(z.imaginary*z.imaginary)+complex.real;
        z.imaginary = z.real*z.imaginary*2+complex.imaginary;
        z.real = temp;

        if ((z.real*z.real+z.imaginary*z.imaginary)>4.0) {
           #pragma omp critical
           numoutside++;
           break;
        }
    }
}

