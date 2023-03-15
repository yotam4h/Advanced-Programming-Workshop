#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char name[30];
    int id_card, grade;

} Student;

int studentAvg(const Student *const data, const int size, double *const avg);

int main()
{
    Student db[3] = {{"A", 1, 100},
                     {"B", 2, 95},
                     {"C", 3, 90}};
    int dbSize = sizeof(db) / sizeof(Student);
    double avg;
    studentAvg(db, dbSize, &avg);
    printf("Average is: %.3lf\n", avg);
    return 0;
}

/*
    return number of students under average
    return by reference the average
    print name and id of every student above average
*/
int studentAvg(const Student *const data, const int size, double *const avg)
{
    int i, abvAvg = 0;
    for (i = 0; i < size; i++)
    {
        (*avg) += ((data + i)->grade);
    }
    (*avg) /= size;
    for (i = 0; i < size; i++)
    {
        if ((data + i)->grade >= (*avg))
        {
            printf("Name: %s, ID: %d\n", (data + i)->name, (data + i)->id_card);
            abvAvg++;
        }
    }
    return size - abvAvg;

    return 0;
}
