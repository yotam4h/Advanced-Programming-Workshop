#include <stdio.h>
#include <stdlib.h>

void *realloc1(void *const memblock, size_t size_old, size_t size_new);
void printarr(int *print, int size);
void tryrealloc1();
int *arrcat(int *arr1, size_t size1, int *arr2, size_t size2);

int main()
{
    return 0;
}

int *arrcat(int *arr1, size_t size1, int *arr2, size_t size2)
{
    size_t i;
    arr1 = (int *)realloc1(arr1, size1, (size1 + size2) * ((size_t)(sizeof(int))));
    if (!arr1)
        return NULL;

    for (i = size1; i < (size1 + size2); i++)
    {
        *(arr1 + i) = *(arr2 + i - size1);
    }

    return arr1;
}

void tryrealloc1()
{
    int i;
    int oldsize = 2;
    int *old = (int *)malloc(oldsize * sizeof(int));
    int *new, newsize = 4;
    for (i = 0; i < oldsize; i++)
    {
        *(old + i) = i;
    }
    printarr(old, oldsize);
    new = (int *)realloc1(old, oldsize, newsize);
    for (i = oldsize - 1; i < newsize; i++)
    {
        *(new + i) = i;
    }
    printarr(new, newsize);
}

void *realloc1(void *const memblock, size_t size_old, size_t size_new)
{
    int i;
    int realoc_size = size_old < size_new ? size_old : size_new;
    // allocate new memblock
    char *newmemblock = (char *)malloc(size_new);
    if (!newmemblock)
        return NULL;
    if (memblock)
    {
        // copy mem;
        for (i = 0; i < realoc_size; i++)
        {
            *(newmemblock + i) = *((char *)memblock + i);
        }
        // release old memblock
        free(memblock);
        if (size_new == 0)
            return NULL;
    }
    // return new memblock address
    return newmemblock;
}

void printarr(int *print, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%3d", *(print + i));
    }
    putchar(10);
}