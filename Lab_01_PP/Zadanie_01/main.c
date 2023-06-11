#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sumaCiaguArytmetycznego(int a, int n, int r);
double sumaCiaguGeometrycznego(double a, double q, int n);

int main(){
    int a;
    int n;
    int r;
    double q;
    printf("Podaj a1: ");
    scanf("%d", &a);
    printf("Podaj n: ");
    scanf("%d", &n);
    printf("Podaj roznice: ");
    scanf("%d", &r);
    printf("Podaj q: ");
    scanf("%lf", &q);

    //printf("%d, %d, %d, %lf\n\n", a, n, r, q);
    puts(" ");
    int (*sumaCiaguArytmetycznego_ptr)(int, int, int) = sumaCiaguArytmetycznego;
    printf("suma ciagu arytm - %d\n", sumaCiaguArytmetycznego_ptr(a, n, r));

    double (*sumaCiaguGeometrycznego_ptr)(double, double, int) = sumaCiaguGeometrycznego;
    printf("suma ciagu geo - %lf\n", sumaCiaguGeometrycznego_ptr(a, q, n));

    return 0;
}

int sumaCiaguArytmetycznego(int a, int n, int r){
    return (((2*a)+(n-1)*r)/2)*n;
}

double sumaCiaguGeometrycznego(double a, double q, int n){
    //printf("%lf, %lf, %d", a, q, n);
    puts(" ");
    if (q == 1)
        return a*n;
    else
        return (a*(1-pow(q, n))/(1-q));
}
