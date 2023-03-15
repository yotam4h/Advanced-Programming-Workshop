#include <stdio.h>
#include <stdlib.h>

typedef struct student_init_data
{
    int _id,
        *_grade,
        _gsize;
} StudentData;

typedef struct student_processed_data
{
    int _id;
    double _average;
} StudentProcData;

typedef struct statistics
{
    StudentProcData *_abveq, *_under;
} Statistics;


// TODO: classifiction, print, free
int main()
{
    StudentData db[3];
    int size = sizeof(db) / sizeof(StudentData),
        i;

    for (i = 0; i < size; i++)
        db[i]._grade = NULL;

    // ! move to a function
    /* double totalavg = 0;
    double *avgarray = (double *)malloc(size * sizeof(double));
    if (!avgarray)
        return 404;
    for (i = 0; i < size; i++)
    {
        *(avgarray + i) = arrayaverage((db + i)->_grade, (db + i)->_gsize);
        totalavg += *(avgarray + i);
    }
    totalavg /= size; */

    return 0;
}

void inputstudents(StudentData *const list, const int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        fputs("enter id:", stdout);
        scanf("%d", &((list + i)->_id));
        fputs("enter how many grades to input: ", stdout);
        scanf("%d", &((list + i)->_gsize));
        inputgrades((list + i)->_grade, (list + i)->_gsize);
    }
}

void inputgrades(int **arr, const int n)
{
    int i;
    (*arr) = (int *)malloc(n * sizeof(int));
    if (!(*arr))
        return;

    for (i = 0; i < n; i++)
    {
        printf("grade [%d]: ", i + 1);
        scanf("%d", (*arr) + i);
    }
}

double arrayaverage(double *arr, const int n)
{
    int i;
    double avg;
    for (i = 0; i < n; i++)
    {
        avg += *(arr + i);
    }
    avg /= n;
    return avg;
}
