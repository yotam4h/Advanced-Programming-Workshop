#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int *removeDup(int *arr, size_t n, size_t *new);
void printarr(int *a, size_t n);
void fun1();
void fun2();

void splitevenodd(int *arr, size_t n, int *_even, size_t *_evensize, int *_odd, size_t *_oddsize)
{
    int i, j, k;
    int *even, *odd;
    even = (int *)malloc(n * sizeof(int));
    odd = (int *)malloc(n * sizeof(int));

    for (i = 0, j = 0, k = 0; i < (int)n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            even[j++] = arr[i];
        }
        else
        {
            odd[k++] = arr[i];
        }
    }
    *_evensize = (size_t)j;
    *_oddsize = (size_t)k;
    even = (int *)realloc(even, *_evensize);
    odd = (int *)realloc(odd, *_oddsize);
    *_even = even;
    *_odd = odd;
}

void fun2()
{
}

int main()
{
    fun2();
    return 0;
}

void fun1()
{
    int totest[] = {50, 60, 60, 72, 81, 81, 81, 81, 93, 93};
    size_t n = sizeof(totest) / sizeof(int), newsize;
    int *new = removeDup(totest, n, &newsize);
    printarr(new, newsize);
    free(new);
    new = NULL;
}

int *removeDup(int *arr, size_t n, size_t *new)
{
    int i, j, k, *aux;
    aux = (int *)malloc(n * sizeof(int));
    assert(aux);
    i = j = k = 0;
    while (i < (int)n)
    {
        if (arr[i] == arr[j])
        {
            j++;
        }
        else
        {
            aux[k++] = arr[i];
            i = j;
        }
    }
    *new = (size_t)k;
    aux = (int *)realloc(aux, *new);
    return aux;
}

void printarr(int *a, size_t n)
{
    int i;
    for (i = 0; i < (int)n; i++)
        printf("%3d", a[i]);
    putchar(10);
}
