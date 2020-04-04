#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/*
    The exercise was about fixing the given program for computing
    the area of a Mandelbrot set. 
    
    The biggest issue was global and common j variable for
    every thread. I put it to the private section — i variable 
    was private by default because of parallel for.

    The second issue was only initiating private variable eps
    without getting value from global eps. Without firstprivate 
    reading that would work fine too but the time of code execution
    would be a way longer.

    Another issue was testpoint() method which didn't require
    any parameter. As result, it completely ignored values computed
    in parallel sections and didn't update the final result correctly. 

    The last problem was incrementing numoutside. Because method
    testpoint() was running by many threads there was a problem that 
    many of them tried to increment at in the same time. omp criticial
    remove the problem allowing only one thread at the time to increment 
    the value. 
    
    You can find the video with given exercise here:
    https://www.youtube.com/watch?v=dlrbD0mMMcQ#t=13m44s
*/

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

