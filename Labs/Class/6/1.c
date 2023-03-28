#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_template
{
    struct node_template *next;
    char data;
} nodeDefault = {NULL};

typedef struct node_template Node;

void printList(const Node *current);
Node *insertToSorted(Node *head, char charToInsert);
Node *createSortedList(Node *head);

int main()
{
    Node *head = NULL, *temp = NULL;
    /* Node a, b, c;
    a.next = &b;
    b.next = &c;
    c.next = NULL;
    a.data = 'b';
    b.data = 'c';
    c.data = 'd';

    head = &a;
    printList(head);

    char charToInsert = 'a';
    if ((temp = insertToSorted(head, charToInsert)))
    {
        head = temp;
        temp = NULL;
        printList(head);
    } */

    createSortedList(head);
    printList(head);

    return 0;
}

Node *createSortedList(Node *head)
{
    char input;
    
}

/**
 * @brief
 * insert new node to sorted linked-list at the right place
 * @return Node *
 */
Node *insertToSorted(Node *head, char charToInsert)
{
    Node *current = NULL, *newNode = (Node *)malloc(sizeof(Node));

    // if linked-list exists and memory allocated
    if (head != NULL && newNode != NULL)
    {
        // initiallize 'newNode'
        *newNode = nodeDefault;
        newNode->data = charToInsert;

        // initiallize 'current'
        current = head;

        // 'newNode' needs to be the first Node
        if (strcmp(&current->data, &newNode->data) > 0)
        {
            newNode->next = current;
            return newNode;
        }

        // reach Node to enter 'newNode' after
        while (current->next != NULL && strcmp(&current->next->data, &newNode->data) < 0)
        {
            current = current->next;
        }

        // insert 'newNode'
        newNode->next = current->next;
        current->next = newNode;
    }

    return head;
}

void printList(const Node *current)
{
    while (current != NULL)
    {
        printf("[%c] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}