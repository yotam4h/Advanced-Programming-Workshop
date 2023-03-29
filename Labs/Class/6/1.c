#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct node_template
{
    struct node_template *next;
    char data;
} nodeDefault = {NULL};

typedef struct node_template Node; */

typedef struct nodeTemplate{
    struct nodeTemplate *next;
    char data;
} NodeTemplate;

typedef NodeTemplate Node = {NULL};


void printList(const Node *current);
void insertToSorted(Node **head, char charToInsert);
void createSortedList(Node **head);
void reverseList(Node **head);

    int main()
{
    Node *head;

    /* Node a, b, c;
    a.next = &b;
    b.next = &c;
    c.next = NULL;
    a.data = 'b';
    b.data = 'c';
    c.data = 'd';


    a b c d


    head = &a;
    printList(head);

    char charToInsert = 'a';
    if ((temp = insertToSorted(head, charToInsert)))
    {
        head = temp;
        temp = NULL;
        printList(head);
    } */

    createSortedList(&head);
    printList(head);
    reverseList(&head);
    printList(head);

    return 0;
}

void reverseList(Node **head)
{
    Node *before = NULL,
         *current = *head,
         *after = current->next;

    while (current != NULL && after != NULL)
    {
        // reverse
        current->next = before;

        // advance
        before = current;
        current = after;
        after = after->next;
    }
    
    // reverse last node
    current->next = before;
    
    // update head of list
    *head = current;

    // nullify
    before = NULL;
    current = NULL;
    after = NULL;
}

void createSortedList(Node **head)
{
    char input;

    printf("Creating list. Enter letters or 0 to stop.\n");

    // first element
    (*head) = (Node *)malloc(sizeof(Node));

    // if memory allocated
    if ((*head) != NULL)
    {
        input = getchar();
        (*head)->data = input;
        (*head)->next = NULL;

        // loop new elements
        while ((input = getchar()) != '\n')
        {
            if (input == ' ')
                continue;

            insertToSorted(head, input);
        }
    }
}

/**
 * @brief
 * insert new node to sorted linked-list at the right place
 * @return Node *
 */
void insertToSorted(Node **head, char charToInsert)
{
    Node *current = *head, *newNode = (Node *)malloc(sizeof(Node));

    // if linked-list exists and memory allocated
    if (current != NULL && newNode != NULL)
    {
        // initiallize 'newNode'
        newNode->next = NULL;
        newNode->data = charToInsert;

        // 'newNode' needs to be the first Node
        if (strcmp(&current->data, &newNode->data) > 0)
        {
            newNode->next = current;
            *head = newNode;
            return;
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