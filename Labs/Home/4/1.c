#include <stdio.h>
#include <stdlib.h>
#define SIZE 2

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
    int _abveqSize, _underSize;
    double _totalavg;
} Statistics;

double arrayaverage(int *arr, const int n);
int *inputgrades(const int n);
void inputstudents(StudentData *const list, const int size);
void classification(const StudentData *const init, int const initSize, Statistics *const stats);
void printstats(const Statistics *const stats);
void freeResources(StudentData *const init, int const initSize, Statistics *const stats);

int main()
{
    StudentData db[SIZE];
    Statistics stats;
    int size = sizeof(db) / sizeof(StudentData),
        i;

    stats._abveq = NULL;
    stats._under = NULL;
    for (i = 0; i < size; i++)
        db[i]._grade = NULL;

    inputstudents(db, size);
    classification(db, size, &stats);
    printstats(&stats);

    freeResources(db, size, &stats);
    return 0;
}

void freeResources(StudentData *const init, int const initSize, Statistics *const stats)
{
    int i;
    for (i = 0; i < initSize; i++)
    {
        free(((init+i)->_grade));
    }

    free(stats->_abveq);
    stats->_abveq = NULL;
    free(stats->_under);
    stats->_under = NULL;
}

void printstats(const Statistics *const stats)
{
    int i;

    printf("\n\nTotal Average: %.3lf \n", (stats->_totalavg));

    printf("Students above or equal to average: ");
    for (i = 0; i < stats->_abveqSize; i++)
    {
        printf("Id: %d, Average: %.3lf.    ", (stats->(_abveq + i)->_id), (stats->(_abveq + i)->_average));
    }
    printf("\n");
    if (0 < stats->_underSize)
    {
        printf("Students under average: ");
        for (i = 0; i < stats->_underSize; i++)
        {
            printf("Id: %d, Average: %.3lf.    ", (stats->(_under + i)->_id), (stats->(_under + i)->_average));
        }
        printf("\n");
    }
}

void classification(const StudentData *const init, int const initSize, Statistics *const stats)
{
    int i, j, k;
    double *avgarray = NULL;

    /**
     *  store average of every student grades in 'avgarray',
     *  store average of all averages in 'totalavg'.
     */
    avgarray = (double *)malloc(initSize * sizeof(double));
    if (!avgarray)
        return; // ! needs to change
    for (i = 0; i < initSize; i++)
    {
        *(avgarray + i) = arrayaverage(((init + i)->_grade), ((init + i)->_gsize));
        //
        // printf("i%d avg%.3lf\n", i, *(avgarray + i));
        //
        stats->_totalavg += *(avgarray + i);
    }
    stats->_totalavg /= initSize;

    /**
     * store number of students with average under and above or equal
     */
    stats->_underSize = 0;
    for (i = 0; i < initSize; i++)
    {
        if (*(avgarray + i) < (stats->_totalavg))
        {
            stats->_underSize++;
        }
    }
    (stats->_abveqSize) = initSize - (stats->_underSize);

    stats->_abveq = (StudentProcData *)malloc((stats->_abveqSize) * sizeof(StudentProcData));
    if (!(stats->_abveq))
        return; // ! needs to change
    stats->_under = (StudentProcData *)malloc((stats->_underSize) * sizeof(StudentProcData));
    if (!(stats->_under))
        return; // ! needs to change

    /**
     *  organize students in two groups: under, above or equal averages
     */
    for (i = j = k = 0; i < initSize; i++)
    {
        if (*(avgarray + i) < (stats->_totalavg)) // average under
        {
            ((stats->_under + j)->_id) = ((init + i)->_id);
            ((stats->_under + j)->_average) = *(avgarray + i);
            j++;
        }
        else // average above or equal
        {
            ((stats->_abveq + k)->_id) = ((init + i)->_id);
            ((stats->_abveq + k)->_average) = *(avgarray + i);
            k++;
        }
    }

    /**
     *  free resources
     */
    free(avgarray);
    avgarray = NULL;
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
        (list + i)->_grade = inputgrades((list + i)->_gsize);
    }
}

int *inputgrades(const int n)
{
    int i, *arr = NULL;
    arr = (int *)malloc(n * sizeof(int));
    if (!arr)
        return;

    for (i = 0; i < n; i++)
    {
        printf("grade [%d]: ", i + 1);
        scanf("%d", arr + i);
    }
    return arr;
}

double arrayaverage(int *arr, const int n)
{
    int i;
    double avg = 0;
    for (i = 0; i < n; i++)
    {
        avg += *(arr + i);
    }
    avg /= n;
    return avg;
}
