// Course: Advanced C programming
// exercise 1, question 3
// file name: ex1_q3.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>

// --------------------------- //
//
//	Assigned by:
//		Student1_Full_Name #ID
//		Student2_Full_Name #ID
//
// --------------------------- //

// structs and function declarations section:
typedef struct rectangle
{
	int xTopSmall;
	int yTopSmall;
	int xButtomRight;
	int yButtomRight;
} rectangle;

typedef struct recElement
{
	rectangle Rect;
	struct recElement *next;
} recElement;

int validateRectangle(rectangle *rec);
rectangle scanRectangle();
recElement *createElement();
recElement *createRectList();
rectangle findSmallest(recElement *head);
void printRectangle(rectangle *rec);
void printList(recElement *head);
void freeList(recElement *head);

// --------------------------- //

int main()
{
	rectangle rec;
	recElement *head = NULL;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	head = createRectList();

	printf("\n\nRectangle list:\n");
	printList(head);

	rec = findSmallest(head);

	printf("\n\nFilling rectangle:\n");
	printRectangle(&rec);

	freeList(head);
	head = NULL;

	printf("\n\n");

	return 0;
}
// --------------------------- //

/// <summary>
/// Function gets an address of a rectangle and check validity.
/// </summary>
/// <param>Address of rectangle</param>
/// <returns>0- if rectangle is not valid, 1-if rectangle is a valid, 2-if rectangle is a point</returns>
int validateRectangle(rectangle *rec)
{
	// your code:

	// ! IMPORTANT !
	// TODO : add more INVALID cases, top point is not top, bottom point is not bottom
	// ! IMPORTANT !

	enum State {Invalid, Valid, Point};

	// if co-ordinates make a point
	if (rec->xTopSmall == rec->xButtomRight && rec->yTopSmall == rec->yButtomRight)
	{
		return Point;
		//return 2;
	}

	// if co-ordinates make a line
	if (rec->xTopSmall == rec->xButtomRight || rec->yTopSmall == rec->yButtomRight)
	{
		return Invalid;
		//return 0;
	}

	// rectangle is valid
	return Valid;
	//return 1;
}
// --------------------------- //

/// <summary>
/// Function scan a rectangle in the plane,
/// Used as auxiliary function for createElement.
/// </summary>
/// <param>None</param>
/// <returns>a newly scanned rectangle</returns>
rectangle scanRectangle()
{
	// your code:

	enum State {Invalid, Valid, Point};
	rectangle newRec;

	// initialize the rectangle
	printf("Now entering rectangle: \n");
	do
	{
		printf("Please enter top left point x: ");
		scanf("%d", &newRec.xTopSmall);
		printf("Please enter top left point y: ");
		scanf("%d", &newRec.yTopSmall);
		printf("Please enter bottom right point x: ");
		scanf("%d", &newRec.xButtomRight);
		printf("Please enter bottom right point y: ");
		scanf("%d", &newRec.yButtomRight);
	} while (validateRectangle(&newRec) == Invalid);

	return newRec;
}
// --------------------------- //

/// <summary>
/// Function allocate a new recElement.
/// Calls scanRectangle during the process.
/// if the scanned rectangle is a point, returns NULL.
/// </summary>
/// <returns>New allocated recElement or NULL if rectangle is a point</returns>
recElement *createElement()
{
	// your code:
	
	enum State {Invalid, Valid, Point};
	recElement *newElement = NULL;

	// allocate memory for recElement
	newElement = (recElement *)malloc(sizeof(recElement));

	// if memory was allocated
	if (newElement != NULL)
	{
		newElement->next = NULL;
		newElement->Rect = scanRectangle();

		// if point, free allocated memory and nullify 'newElement'
		if (validateRectangle(&newElement->Rect) == Point)
		{
			free(newElement);
			newElement = NULL;
		}
	}

	return newElement; // NULL if malloc failed or recieved a point
}
// --------------------------- //

/// <summary>
/// Function creates a list of rectangles.
/// Calls function createElement in a loop.
/// Scan stops when createElement returns null.
/// </summary>
/// <param>None</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
recElement *createRectList()
{
	// your code:

	recElement *head = NULL, *current = NULL;

	// deal with 'head' element
	head = createElement();

	// if memory was allocated
	if (head != NULL)
	{
		// starting to work with 'current' pointer
		current = head;

		// loop new elements
		while (current != NULL)
		{
			current->next = createElement();

			// if memory was allocated
			if (current != NULL)
			{
				// advance 'current'
				current = current->next;
			}
		}
		// no need to nullify 'current', will nullify itself
	}

	return head; // NULL if malloc failed on 'head' element
}
// --------------------------- //

/// <summary>
/// Function gets a list and returns the filling rectangle
/// </summary>
/// <param>recElement* head - the list of rectangles</param>
/// <returns>The filling rectangle. if the list is empty return rectangle with (0,0,0,0)</returns>
rectangle findSmallest(recElement *head)
{
	// your code:

	// ? can just advance 'head' because its a copy of the original pointer ?
	// ? will not discard linked-list original head address ?
	// ! using new pointer 'current' for readability (can't change function paramaters) !

	rectangle smallest = {0, 0, 0, 0};
	recElement *current = NULL;

	// if linked-list exists, re-initiallize 'smallest' rectangle
	if (head != NULL)
	{
		smallest.yButtomRight = head->Rect.yButtomRight;
		smallest.xButtomRight = head->Rect.xButtomRight;
		smallest.yTopSmall = head->Rect.yTopSmall;
		smallest.xTopSmall = head->Rect.xTopSmall;

		// advance 'current'
		current = head->next;
	}

	// iterate linked-list
	while (current != NULL)
	{
		// update leftest x
		if (current->Rect.xTopSmall < smallest.xTopSmall)
			smallest.xTopSmall = current->Rect.xTopSmall;

		// update leftest highest y
		if (current->Rect.yTopSmall > smallest.yTopSmall)
			smallest.yTopSmall = current->Rect.yTopSmall;

		// update rightest x
		if (current->Rect.xButtomRight > smallest.xButtomRight)
			smallest.xButtomRight = current->Rect.xButtomRight;

		// update rightest lowest y
		if (current->Rect.yButtomRight < smallest.yButtomRight)
			smallest.yButtomRight = current->Rect.yButtomRight;

		// advance 'current'
		current = current->next;
	}
	// no need to nullify 'current', will nullify itself

	return smallest;
}
// --------------------------- //

/// <summary>
/// Function print rectangle cordinates on screen. (not drawing the rectangle!)
/// </summary>
/// <param>rectangle* rec - pointer to rectangle</param>
/// <returns>None</returns>
void printRectangle(rectangle *rec)
{
	// if rectangle exists
	if (rec != NULL)
	{
		printf("[(%d,%d)(%d,%d)]", rec->xTopSmall, rec->yTopSmall, rec->xButtomRight, rec->yButtomRight);
	}
}
// --------------------------- //

/// <summary>
/// Function print list on screen.
/// </summary>
/// <param>recElement* head - list address</param>
/// <returns>None</returns>
void printList(recElement *head)
{
	// your code:

	// ? can just advance 'head' because its a copy of the original pointer ?
	// ? will not discard linked-list original head address ?
	// ! using new pointer 'current' for readability (can't change function paramaters) !

	recElement *current = head;

	// iterate linked-list
	while (current != NULL)
	{
		printRectangle(&current->Rect);
		printf(" -> ");

		// advance 'current'
		current = current->next;
	}
	// no need to nullify 'current', will nullify itself

	printf("NULL\n");
}
// --------------------------- //

/// <summary>
/// Function free alocated memory of list
/// </summary>
/// <param>recElement* head - pointer to head of the list</param>
/// <returns>None</returns>
void freeList(recElement *head)
{
	// your code:

	recElement *temp = NULL;

	// if linked-list exists
	while (head != NULL)
	{
		// 'temp' points to first element of the list
		temp = head;

		// advance 'head'
		head = head->next;

		// release first element memory
		free(temp);
	}
	// no need to nullify 'head', will nullify itself
	// nullify 'temp'
	temp = NULL;
}
// --------------------------- //
