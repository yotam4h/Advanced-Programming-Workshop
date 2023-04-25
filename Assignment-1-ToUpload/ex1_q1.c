// Course: Advanced C programming
// exercise 1, question 1
// file name: ex1_q1.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------- //
//
//	Assigned by:
//		Shira Ayal #207916768
//		Yotam Haimovitch #207041393
//
// --------------------------- //

// function declarations section:
int *scanArray(int *);
void printArray(int *, int);
int arrangeArray(int **, int);

// --------------------------- //

// main section:
// DO NOT CHANGE the following function:
int main()
{
	int *arr, n, k;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	arr = scanArray(&n);
	k = arrangeArray(&arr, n);

	// write output:
	printf("Output:\n");
	printf("Size of k: %d\n", k);
	printf("Sorted arrayPtr:\n");
	printArray(arr, n);
	free(arr);

	return 0;
}
// --------------------------- //

// DO NOT CHANGE the following function:
int *scanArray(int *n)
{
	int i;
	int *arr;

	printf("Enter arrayPtr size: ");
	scanf("%d", n);

	arr = (int *)malloc(sizeof(int) * (*n));
	for (i = 0; i < *n; ++i)
	{
		printf("Enter value #%d: ", i + 1);
		scanf("%d", arr + i);
	}

	return arr;
}
// --------------------------- //

// DO NOT CHANGE the following function:
void printArray(int *arr, int n)
{
	int i;
	printf("{");
	for (i = 0; i < n; ++i)
		printf("%d%s", arr[i], i == n - 1 ? "" : ", ");
	printf("}\n");
}
// --------------------------- //

/// <summary>
/// Combine the two groups using realloc and memcpy only.
/// </summary>
/// <param>int **arr - Address of the array pointer</param>
/// <param>int n - Size of the array</param>
/// <returns>Size of the first group</returns>
int arrangeArray(int **arr, int n)
{
	// your code:

	int i, k, *arrayPtr = *arr;

	// find size of first group (k)
	for (i = 1, k = 0; i < n; i++)
	{
		if (arrayPtr[i] < arrayPtr[i - 1])
		{
			k = i;
			break;
		}
	}

	if (k == 0)
	{
		return 0;
	}

	// realloce 'arrayPtr' and add size k to the end of the 'arrayPtr'
	arrayPtr = (int *)realloc(arrayPtr, sizeof(int) * (n + k));

	// copy the first group to the end of the 'arrayPtr'
	memcpy(arrayPtr + n, arrayPtr, sizeof(int) * k);

	// copy from 'arrayPtr[k]' to 'arrayPtr[n+1]' into the start of 'arrayPtr'
	memcpy(arrayPtr, arrayPtr + k, sizeof(int) * (n + k));

	// reallocate 'arrayPtr' to the original size
	arrayPtr = (int *)realloc(arrayPtr, sizeof(int) * n);

	// input 'arrayPtr' address to 'arr', and nullify 'arrayPtr';
	*arr = arrayPtr; // return by reference: sorted 'arrayPtr'
	arrayPtr = NULL;

	// return size of first group
	return k;
}
// --------------------------- //
