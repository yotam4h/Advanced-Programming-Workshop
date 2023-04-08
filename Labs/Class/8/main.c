#include <stdio.h>
#include <stdlib.h>

void freeMatrix(int **triMat, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free(triMat[i]);
        triMat[i] = NULL;
    }
    free(triMat);
    triMat = NULL;
}

int **triMatrixDown(int n)
{
    int i, j, k,
        **triMat = NULL;

    triMat = (int **)malloc(n * sizeof(int *));
    if (triMat == NULL)
        return NULL;

    for (i = 0, j = 1; i < n; i++)
    {
        triMat[i] = (int *)calloc(j++, sizeof(int));
        if (triMat[i] == NULL)
        {
            freeMatrix(triMat, i);
            return NULL;
        }
    }

    for (i = k = 0; i < n; i++)
    {
        for (j = 0; j < i + 1; j++)
        {
            triMat[i][j] = k++;
        }
    }

    return triMat;
}

int reachTriMatDown(int **triMat, int i, int j)
{
    if (j > i)
        return 0;

    return triMat[i][j];
}


void printTriMatDown(int **triMat, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%8d", reachTriMatDown(triMat, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

int **triMatrixUp(int n)
{
    int i, j, k,
        **triMat = NULL;

    triMat = (int **)malloc(n * sizeof(int *));
    if (triMat == NULL)
        return NULL;

    for (i = 0, j = n; i < n; i++)
    {
        triMat[i] = (int *)calloc(j--, sizeof(int));
        if(triMat[i] == NULL)
        {
            freeMatrix(triMat,i);
            return NULL;
        }
    }

    for (i = k = 0; i < n; i++)
    {
        for (j = 0; j < n - i; j++)
        {
            triMat[i][j] = k++;
        }
    }

    return triMat;
}

int reachTriMatUp(int **triMat, int i, int j)
{
    if (i > j)
        return 0;

    return triMat[i][j-i];
}

void printTriMatUp(int **triMat, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%8d", reachTriMatUp(triMat, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int **test;
    test = triMatrixUp(4);
    printTriMatUp(test, 4);
    freeMatrix(test, 4);
    test = NULL;
    return 0;
}
