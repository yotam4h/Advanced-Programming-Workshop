// Course: Advanced C programming
// exercise 2, question 2
// file name: ex2_q2.c

// --------------------------- //
//
//	Assigned by:
//		Student1_Full_Name #ID
//		Student2_Full_Name #ID
//
// --------------------------- //

// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define ROWS 4
#define COLS 5
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct four
{
	int i, j, d, value;
} four;

typedef struct list
{
	four data;
	struct list *next;
} list;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
int createArrayAndList(int A[][COLS], list **lst, four **arr, int rows, int cols);
four createFour(int i, int j, int d, int value);
list *createElement(four data);
void printArray(four *arr, int n);
void printList(list *lst);
void freeDynamic(list **lst, four **arr);

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	int n;
	list *lst = NULL;
	four *arr = NULL;
	int A[ROWS][COLS] = {
		{0, 6, 5, 6, 6},
		{8, 9, 5, 6, 7},
		{7, 6, 5, 4, 7},
		{9, 8, 1, 6, 7},
	};

	// Start Program:
	printf("Start Program\n");

	// call functions:
	n = createArrayAndList(A, &lst, &arr, ROWS, COLS);

	// write output:
	printf("Output:\n");
	printArray(arr, n);
	printList(lst);

	// free dynamic:
	freeDynamic(&lst, &arr);

	return 0;
}
// --------------------------- //

/// <summary>
/// This function allocate a dynamic array and list,
/// from elements found at matrix A
/// </summary>
/// <param>int A[][] - The static matrix</param>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <param>four** arr - Pointer to the pointer of the head of the array</param>
/// <param>int rows - The number of rows in the matrix</param>
/// <param>int cols - The number of colums in the matrix</param>
/// <returns>Number of requested elements in found in A</returns>
int createArrayAndList(int A[][COLS], list **lst, four **arr, int rows, int cols)
{
	// your code:

	// variable declaration
	int i, j, k, count = 0;
	list *current = NULL;
	// edgecases
	if (**A == NULL || lst == NULL || arr == NULL || rows < 0 || cols < 0)
		return -1;

	// count requested elements, O(n)
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if ((A[i][j] - j) == (j - i))
			{
				count++;
			}
		}
	}
	if (count == 0)
		return 0;

	// allocate array
	(*arr) = (four *)malloc(count * sizeof(four));
	if ((*arr) == NULL)
		return 0;

	// populate array
	k = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if ((A[i][j] - j) == (j - i))
			{
				(*arr)[k++] = createFour(i, j, j - i, A[i][j]);
			}
		}
	}

	// allocate list
	(*lst) = createElement(**arr);
	current = (*lst);
	if (current == NULL)
	{
		freeDynamic(lst, arr);
		return 0;
	}
	for (i = 1; i < count; i++)
	{
		current->next = createElement((*arr)[i]);
		if (current->next == NULL)
		{
			freeDynamic(lst, arr);
			return 0;
		}
		current = current->next;
	}

	return count;
}
// --------------------------- //

/// <summary>
/// The function receives 4 integer values
/// and returns a value from type four.
/// </summary>
/// <param>int i - The cell row number in matrix</param>
/// <param>int j - The cell colum number in the matrix</param>
/// <param>int d - The difference between the consecutive values</param>
/// <param>int value - The value at position [i,j] in matrix</param>
/// <returns>value from type four</returns>
four createFour(int i, int j, int d, int value)
{
	// your code:
	return (four){i, j, d, value};
}
// --------------------------- //

/// <summary>
/// The function receives a value from type four
/// and returns a dynamic element from type list
/// </summary>
/// <param>four data - value from type four</param>
/// <returns>dynamic value from type list</returns>
list *createElement(four data)
{
	// your code:
	list *element = NULL;
	// TODO: edgecases (data.i/j<0)

	element = (list *)malloc(sizeof(list));
	if (element == NULL)
		return NULL;
	element->next = NULL;
	element->data = data;

	return element;
}
// --------------------------- //

/// <summary>
/// The function receives an array from type four,
/// and print its values.
/// </summary>
/// <param>four* arr - the array</param>
/// <param>int n - number of elements</param>
/// <returns>None</returns>
void printArray(four *arr, int n)
{
	// your code:
	int i;
	for (i = 0; i < n - 1; i++)
	{
		printf("[%d,%d,%d,%d], ", arr[i].i, arr[i].j, arr[i].d, arr[i].value);
	}
	printf("[%d,%d,%d,%d]\n", arr[n - 1].i, arr[n - 1].j, arr[n - 1].d, arr[n - 1].value);
}
// --------------------------- //

/// <summary>
/// The function receives a list,
/// and print its values.
/// </summary>
/// <param>list* lst - the list</param>
/// <returns>None</returns>
void printList(list *lst)
{
	// your code:
	while (lst != NULL)
	{
		printf("[%d,%d,%d,%d] -> ", lst->data.i, lst->data.j, lst->data.d, lst->data.value);
		lst = lst->next;
	}
	printf("[NULL]\n");
}
// --------------------------- //

/// <summary>
/// The function free all allocated memory of the program.
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <param>four** arr - Pointer to the pointer of the head of the array</param>
/// <returns>None</returns>
void freeDynamic(list **lst, four **arr)
{
	// your code:
	list *current = NULL, *forward = NULL;
	
	// edgecases
	if (lst == NULL || arr == NULL)
		return;

	// free and nullify array
	free(*arr);
	*arr = NULL;

	// free and nullify list
	current = (*lst);
	while (current != NULL)
	{
		forward = current->next;
		free(current);
		current = forward;
	}
	// current will nullify itself
	(*lst) = NULL;
}
// --------------------------- //
