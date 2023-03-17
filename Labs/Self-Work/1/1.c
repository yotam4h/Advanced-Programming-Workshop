#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int abundantsInClosedRange(int a, int b, int **abundants);
bool isAbundant(int num);
int sumofDivisors(int num);
bool isDivisor(const int *const a, const int *const b);

int main()
{
    int i, *abundants = NULL, _abundantsSize = 0;
    _abundantsSize = abundantsInClosedRange(10, 40, &abundants);

    if (abundants != NULL)
    {
        for (i = 0; i < _abundantsSize; i++)
        {
            printf("%3d ", abundants[i]);
        }
        printf("\n");

        free(abundants);
        abundants = NULL;
    }

    return 0;
}

int abundantsInClosedRange(int a, int b, int **abundants)
{
    int i, j, countAbundants = 0, *new = NULL;
    char *aux = (char *)malloc((size_t)(b + 1) * sizeof(char));
    for (i = 0; i <= b; i++)
        *(aux + i) = '0';

    for (i = a; i <= b; i++)
    {
        if (isAbundant(i))
        {
            *(aux + i) = '1';
            countAbundants++;
        }
    }
    if (countAbundants > 0)
    {
        new = (int *)malloc((size_t)countAbundants * sizeof(int));
        for (i = a, j = 0; i <= b; i++)
        {
            if (*(aux + i) == '1')
            {
                *(new + j) = i;
                j++;
            }
        }
        *abundants = new;
        new = NULL;
    }
    free(aux);
    aux = NULL;
    return countAbundants;
}

bool isAbundant(int num)
{
    return num < sumofDivisors(num);
}

int sumofDivisors(int num)
{
    int i, sum = 1;
    for (i = 2; i * i < num; i++)
    {
        if (isDivisor(&num, &i))
            sum += i + (num / i);
    }
    return sum;
}

bool isDivisor(const int *const a, const int *const b)
{
    return (*a % *b == 0);
}
