#include <omp.h>
#include <stdio.h>

#define NPOINTS 1000
#define MXITR 1000

void testpoint(void);

struct complex_number{
    double real;     double imaginary;
};

struct complex_number complex;
int numoutside = 0;

int main(){
    int i, j;
    double area, error, eps = 1.0e-5;

    #pragma omp parallel for default(shared) private(complex,eps)
    for (i=0; i<NPOINTS; i++) 
    {
        for (j=0; j<NPOINTS; j++) 
        {
            complex.real= -2.0+2.5*(double)(i)/(double)(NPOINTS)+eps;
            complex.imaginary= 1.125*(double)(j)/(double)(NPOINTS)+eps;
            testpoint();
        }
    }

    area=2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
    error=area/(double)NPOINTS;

    printf("\nRESULTS:\n");
    printf("complex_number(real,imaginary) = %f + %f\n",complex.real,complex.imaginary);
    printf("area = %f\n",area);
    printf("error = %f\n",error);
    printf("numoutside = %f\n",numoutside);
}

void testpoint(void){
    struct complex_number z;
    int iter;
    double temp;

    z=complex;

    for (iter=0; iter<MXITR; iter++){
        temp = (z.real*z.real)-(z.imaginary*z.imaginary)+complex.real;
        z.imaginary= z.real*z.imaginary*2+complex.imaginary;
        z.real= temp;

        if ((z.real*z.real+z.imaginary*z.imaginary)>4.0) {
            numoutside++;
            break;
        }
    }
}