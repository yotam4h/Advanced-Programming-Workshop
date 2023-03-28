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
//		Student1_Full_Name #ID
//		Student2_Full_Name #ID
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
	printf("Sorted array:\n");
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

	printf("Enter array size: ");
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

	// ? best practice: temp pointer to array, to avoid dereferencing twice ?

	int i, k, *array = *arr, *temp = NULL;

	// find size of first group (k)
	for (i = 1; i < n; i++)
	{
		if (array[i] < array[i - 1])
		{
			k = i;
			break;
		}
	}

	// realloce 'array' and add size k to the end of the 'array'
	temp = (int *)realloc(array, sizeof(int) * (n + k));

	// incase realloc fails
	if (temp != NULL)
	{
		array = temp;
		temp = NULL;

		// copy the first group to the end of the 'array'
		memcpy(array + n, array, sizeof(int) * k);

		// copy from 'array[k]' to 'array[n+1]' into the start of 'array'
		memcpy(array, array + k, sizeof(int) * (n + k));

		// reallocate 'array' to the original size
		array = (int *)realloc(array, sizeof(int) * n);
	}

	// input 'array' address to 'arr', and nullify 'array';
	*arr = array; // return by reference: original 'array' if realloc failed, else sorted 'array'
	array = NULL;

	// return size of first group
	return k;
}
// --------------------------- //
