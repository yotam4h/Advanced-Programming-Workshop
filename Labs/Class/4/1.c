#include <stdio.h>
#include <stdlib.h>

typedef struct complex
{
    double real, img;
} Complex;

void inCmplx(Complex * const num);
void printCmplx(const Complex * const num);
Complex sumCmplx(const Complex * const numOne, const Complex * const numTwo);
Complex subCmplx(const Complex * const numOne, const Complex * const numTwo);
Complex mulCmplx(const Complex * const numOne, const Complex * const numTwo);

int main()
{
    Complex a,b,c;
    inCmplx(&a);
    inCmplx(&b);
    printCmplx(&a);
    printCmplx(&b);
    c = sumCmplx(&a,&b);
    printCmplx(&c);
    c = mulCmplx(&c,&c);
    printCmplx(&c);
    
    return 0;
}

Complex mulCmplx(const Complex * const numOne, const Complex * const numTwo)
{
    Complex product;
    product.real = (numOne->real * numTwo->real) - (numOne->img * numTwo->img);
    product.img = (numOne->img * numTwo->real) + (numOne->real * numTwo->img);
    return product;
}

Complex subCmplx(const Complex * const numOne, const Complex * const numTwo)
{
    Complex product;
    product.real = numOne->real - numTwo->real;
    product.img = numOne->img - numTwo->img;
    return product;
}

Complex sumCmplx(const Complex * const numOne, const Complex * const numTwo)
{
    Complex product;
    product.real = numOne->real + numTwo->real;
    product.img = numOne->img + numTwo->img;
    return product;
}

void printCmplx(const Complex * const num)
{
    printf("%.3lf + %.3lfi\n", num->real, num->img);
}

void inCmplx(Complex * const num)
{
    puts("Please enter a complex number.");
    fputs("Real part: ", stdout);
    scanf("%lf", &(num->real));
    fputs("Imagine part: ", stdout);
    scanf("%lf", &(num->img));
}
