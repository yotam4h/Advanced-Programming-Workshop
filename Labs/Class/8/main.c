#include <stdio.h>
#include <stdlib.h>

int **triMatrix(int n)
{
    int i, j,
        **triMat = NULL;

    triMat = (int **)malloc(n * sizeof(int *));
    if (triMat == NULL)
        return NULL;

    for (i = 0, j = 1; i < n; i++)
    {
        triMat[i] = (int *)calloc(j++, sizeof(int));
        
    }
}

int main()
{

    return 0;
}
