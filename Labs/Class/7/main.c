#include <stdio.h>
#include <stdlib.h>

void printMulDimArr(int **mulDimArr, int rows, int cols);
void fun1(void **mulDimArr, int idxROne, int idxRTwo);
void ptrSwap(void **a, void **b);
void fun2(int **mulDimArr, int rows, int IdxCOne, int IdxCTwo);
void intSwap(int *a, int *b);

int main()
{
    int **test, i, j, k,
        rows = 4, cols = 4;

    // allocate dynamic multi-dimension-array test[4][4]
    test = (int **)calloc(rows, sizeof(int));
    for (i = 0; i < 4; i++)
    {
        test[i] = (int *)calloc(cols, sizeof(int));
    }

    for (i = k = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            test[i][j] = k++;
        }
    }

    printMulDimArr(test, rows, cols);

    fun1((void**)test, 0, 1);

    printMulDimArr(test, rows, cols);

    fun1((void**)test, 0, 1);

    printMulDimArr(test, rows, cols);

    fun2(test, rows, 0, 1);

    printMulDimArr(test, rows, cols);

    freeMulDimArr(test);

    test = NULL;

    return 0;
}

void freeMulDimArr(int **mulDimArr, int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        free(mulDimArr[i]);
        mulDimArr[i] = NULL;
    }
    free(mulDimArr);
    mulDimArr = NULL;
}

void printMulDimArr(int **mulDimArr, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%12d", mulDimArr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void fun1(void **mulDimArr, int idxROne, int idxRTwo)
{
    ptrSwap(mulDimArr[idxROne], mulDimArr[idxRTwo]);
}

void ptrSwap(void **a, void **b)
{
    void *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void fun2(int **mulDimArr, int rows, int IdxCOne, int IdxCTwo)
{
    int i;
    for (i = 0; i < rows; i++)
    {
        intSwap(&mulDimArr[i][IdxCOne], &mulDimArr[i][IdxCTwo]);
    }
}

void intSwap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}