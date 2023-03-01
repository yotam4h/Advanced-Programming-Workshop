#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printarr(int *arr, int n);
void runf1();
int *f1(int *tosplit, int tosplitsize, int **odd, int *oddsize, int *evensize);
void runf3();
void f3(char *tosplit, char **lower, char **upper);
void runf4();
void f4(int *arr, int n, int **new, int *newsize);

int main()
{
    runf4();
    return 0;
}

void runf4()
{
    int dups[] = {1,2,3,3,4,4,4,5};
    int dupsize = sizeof(dups)/sizeof(int);
    int *nodups = NULL, nodupsize = 0;

    f4(dups,dupsize,&nodups,&nodupsize);
    printarr(dups,dupsize);
    printarr(nodups,nodupsize);
}

void f4(int *arr, int n, int **new, int *newsize)
{
    int i, j;
    for (i = *newsize = 1; i < n; i++)
    {
        if (arr[i] != arr[i - 1])
        {
            (*newsize)++;
        }
    }

    *new = (int *)malloc((size_t)(*newsize) * sizeof(int));

    **new = *arr;
    for (i = j = 1; i < n; i++)
    {
        if (arr[i] != (*new)[j - 1])
        {
            (*new)[j++] = arr[i];
        }
    }
}

void runf3()
{
    char *tosplit = "AaBbCcDd";
    char *lower = NULL, *upper = NULL;
    f3(tosplit, &lower, &upper);
    puts(tosplit);
    puts(lower);
    puts(upper);

    free(lower);
    free(upper);
    lower = upper = NULL;
}

void f3(char *tosplit, char **lower, char **upper)
{
    int i, j, k, lowsize = 0, upsize = 0;
    for (i = 0; tosplit[i]; i++)
    {
        if ('a' <= tosplit[i] && tosplit[i] <= 'z')
            lowsize++;
        if ('A' <= tosplit[i] && tosplit[i] <= 'Z')
            upsize++;
    }

    *lower = (char *)malloc(((size_t)lowsize + 1) * sizeof(char));
    *upper = (char *)malloc(((size_t)upsize + 1) * sizeof(char));

    for (i = j = k = 0; tosplit[i]; i++)
    {
        if ('a' <= tosplit[i] && tosplit[i] <= 'z')
        {
            (*lower)[j++] = tosplit[i];
        }
        if ('A' <= tosplit[i] && tosplit[i] <= 'Z')
        {
            (*upper)[k++] = tosplit[i];
        }
    }
    (*lower)[j] = (*upper)[k] = '\0';
}

void runf1()
{
    int A[] = {1, 2, 3, 4, 5};
    int Asize = sizeof(A) / sizeof(int);
    int *even = NULL, *odd = NULL;
    int evensize, oddsize;

    even = f1(A, Asize, &odd, &oddsize, &evensize);
    printarr(A, Asize);
    printarr(even, evensize);
    printarr(odd, oddsize);

    free(even);
    free(odd);
    even = odd = NULL;
}

int *f1(int *tosplit, int tosplitsize, int **odd, int *oddsize, int *evensize)
{
    int i, j, k, *even = NULL;
    *oddsize = *evensize = 0;

    for (i = 0; i < tosplitsize; i++)
    {
        if (tosplit[i] % 2)
            (*oddsize)++;
    }

    *evensize = tosplitsize - *oddsize;
    even = (int *)malloc((size_t)(*evensize) * sizeof(int));
    (*odd) = (int *)malloc((size_t)(*oddsize) * sizeof(int));

    for (i = j = k = 0; i < tosplitsize; i++)
    {
        if (tosplit[i] % 2)
        {
            (*odd)[j++] = tosplit[i];
        }
        else
        {
            even[k++] = tosplit[i];
        }
    }

    return even;
}

void printarr(int *arr, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%3d", arr[i]);
    }
    putchar(10);
}