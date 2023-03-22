#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
} List;

int buildOddEvenLists(List **even, List **odd);
void insert(List *const myList, int const input);
void printList(List *const myList);
void freeList(List **myList);
void clearList(List *myList);
int isEmpty(const List *const myList);
void deleteFirst(List *const myList);
int sumMinMaxOfList(const List *const myList, int *const min, int *const max);

int main()
{
    int count, sum, min, max;
    List *even = NULL, *odd = NULL;

    // * create lists
    count = buildOddEvenLists(&even, &odd);

    // * print
    printf("count = %d\n", count);
    printList(even);
    printList(odd);

    // * sum/min/max even
    sum = sumMinMaxOfList(even, &min, &max);
    printf("Even : sum = %d, min = %d, max = %d\n", sum, min, max);

    // * sum/min/max odd
    sum = sumMinMaxOfList(odd, &min, &max);
    printf("Odd : sum = %d, min = %d, max = %d\n", sum, min, max);

    // * free
    freeList(&even);
    freeList(&odd);

    return 0;
}

int buildOddEvenLists(List **even, List **odd)
{
    int input, count = 0;
    *even = (List *)malloc(sizeof(List));
    *odd = (List *)malloc(sizeof(List));
    (*even)->head = NULL;
    (*odd)->head = NULL;

    printf("Enter -1 to stop inputing data\n");
    scanf("%d", &input);
    while (input != (-1))
    {
        if (input % 2) // odd
        {
            insert(*odd, input);
            count++;
        }
        else // even
        {
            insert(*even, input);
            count++;
        }
        scanf("%d", &input);
    }

    return count;
}

void insert(List *const myList, int const input)
{
    Node *current = NULL;
    // if myList->next != NULL
    if (!isEmpty(myList))
    {
        current = myList->head;
        // reach last node
        while (current->next)
        {
            current = current->next;
        }
        // allocate memory for new node
        current->next = (Node *)malloc(sizeof(Node));
        // input data if allocation works
        if (current->next)
        {
            current = current->next;
            current->data = input;
            current->next = NULL;
        }
    }
    else
    {
        myList->head = (Node *)malloc(sizeof(Node));
        // input data if allocation works
        if (!isEmpty(myList))
        {
            current = myList->head;
            current->data = input;
            current->next = NULL;
        }
    }
}

void printList(List *const myList)
{
    Node *current = NULL;
    if (myList != NULL && !isEmpty(myList))
    {
        current = myList->head;
        while (current)
        {
            printf("[%d] -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void freeList(List **myList)
{
    clearList(*myList);
    free(*myList);
    *myList = NULL;
}

void clearList(List *myList)
{
    while (!isEmpty(myList))
    {
        deleteFirst(myList);
    }
}

int isEmpty(const List *const myList)
{
    return (myList->head == NULL);
}

void deleteFirst(List *const myList)
{
    Node *current = NULL;
    if (!isEmpty(myList))
    {
        current = myList->head;
        myList->head = current->next;
        free(current);
        current = NULL;
    }
}

int sumMinMaxOfList(const List *const myList, int *const min, int *const max)
{
    int sum = 0;
    Node *current = NULL;
    if (!(isEmpty(myList)))
    {
        current = myList->head;
        (*max) = current->data;
        (*min) = current->data;

        while (current)
        {
            sum += current->data;
            (*max) = ((current->data) > (*max) ? (current->data) : (*max));
            (*min) = ((current->data) < (*min) ? (current->data) : (*min));
            current = current->next;
        }
    }
    return sum;
}