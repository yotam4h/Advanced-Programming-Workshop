// Course: Advanced C programming
// exercise 2, question 1
// file name: ex2_q1.c

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
#define COLS 4
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct fraction
{
	int num, numerator, denominator;
} fraction;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

fraction **createMatrix(int rows, int cols);
fraction **matrixAverageNeighbor(int A[][COLS], int rows, int cols);
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols);
void printMatrix(fraction **B, int rows, int cols);
void freeMatrix(fraction **B, int rows);
/** DECLARE HERE ONE FUNCTION ACCORDING TO YOUR NEEDS **/
int greatestCommonDivisor(int a, int b);

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	fraction **B;
	int A[ROWS][COLS] = {
		{5, 12, 6, 8},
		{4, 7, 0, 9},
		{13, 20, 8, 2},
		{18, 0, 2, 6}};

	// Start Program:
	printf("Start Program\n");

	// call functions:
	B = matrixAverageNeighbor(A, ROWS, COLS);

	// write output:
	printf("Output:\n");
	printMatrix(B, ROWS, COLS);

	// free matrix:
	freeMatrix(B, ROWS);

	return 0;
}
// --------------------------- //

/// <summary>
/// This code required one extra important function.
/// Think hard about what it should be.
/// </summary>
/// <params>You decide</params>
/// <returns>You decide</returns>

// your code:
int greatestCommonDivisor(int a, int b)
{
	if (a == 0 && b == 0)
		return -1;

	if (a < 0)
		a *= (-1);
	if (b < 0)
		b *= (-1);

	while (a > 0 && b > 0)
	{
		if (a > b)
			a %= b;
		else
			b %= a;
	}

	return a + b;
}
// --------------------------- //

/// <summary>
/// This function allocate a dynamic matrix from type fraction.
/// </summary>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>allocated empty matrix B from type fraction</returns>
fraction **createMatrix(int rows, int cols)
{
	// your code:
	int i;
	fraction **matrix = NULL;

	if (rows < 1 || cols < 1)
		return NULL;

	matrix = (fraction **)malloc(rows * sizeof(fraction *));
	if (matrix == NULL)
		return NULL;

	for (i = 0; i < rows; i++)
	{
		matrix[i] = (fraction *)malloc(cols * sizeof(fraction));
		if (matrix[i] == NULL)
		{
			freeMatrix(matrix, i);
			matrix = NULL;
			return NULL;
		}
	}

	return matrix;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix
/// and for each cell in the matrix calculates
/// the average of its neighbors.
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>matrix B from type fraction</returns>
fraction **matrixAverageNeighbor(int A[][COLS], int rows, int cols)
{
	// your code:
	int i, j;
	fraction **B = NULL;

	if (rows < 0 || cols < 0)
		return NULL;

	B = createMatrix(rows, cols);
	if (B == NULL)
		return NULL;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			B[i][j] = neighborFractionAverage(A, i, j, rows, cols);
		}
	}

	return B;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix, and a cell value,
/// and calculates the average of its neighbors.
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int i - the cell row number in matrix</param>
/// <param>int j - the cell colum number in the matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>value from type fraction</returns>
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols)
{
	// your code:
	fraction avg = {0, 0, 1};
	int sum = 0, neighbours = 0, gcd;

	if (i < 0 || j < 0 || rows < 0 || cols < 0)
	{
		// should have some error flag
	}

	// up
	if (i - 1 > -1)
	{
		sum += A[i - 1][j];
		neighbours++;
		// left up
		if (j - 1 > -1)
		{
			sum += A[i - 1][j - 1];
			neighbours++;
		}
		// right up
		if (j + 1 < cols)
		{
			sum += A[i - 1][j + 1];
			neighbours++;
		}
	}
	// down
	if (i + 1 < rows)
	{
		sum += A[i + 1][j];
		neighbours++;
		// left down
		if (j - 1 > -1)
		{
			sum += A[i + 1][j - 1];
			neighbours++;
		}
		// right down
		if (j + 1 < cols)
		{
			sum += A[i + 1][j + 1];
			neighbours++;
		}
	}
	// left
	if (j - 1 > -1)
	{
		sum += A[i][j - 1];
		neighbours++;
	}
	// right
	if (j + 1 < cols)
	{
		sum += A[i][j + 1];
		neighbours++;
	}

	// convert data into fraction 'avg'
	if (sum % neighbours == 0)
	{
		avg.num = sum / neighbours;
	}
	else
	{
		gcd = greatestCommonDivisor(sum, neighbours);
		avg.num = sum / neighbours;
		avg.numerator = (sum % neighbours) / gcd;
		avg.denominator = neighbours / gcd;
	}

	return avg;
}
// --------------------------- //

/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and print the matrix as double varibles.
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>None</returns>
void printMatrix(fraction **B, int rows, int cols)
{
	// your code:
	int i, j;

	if (B == NULL)
		return;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (B[i][j].numerator == 0)
				printf("(%d)\t\t", B[i][j].num);
			else
				printf("(%d+(%d/%d))\t", B[i][j].num, B[i][j].numerator, B[i][j].denominator);
		}
		printf("\n");
	}
	printf("\n");
}
// --------------------------- //

/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and free all allocated memory.
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <returns>None</returns>
void freeMatrix(fraction **B, int rows)
{
	// your code:
	int i;

	if (B == NULL)
		return;

	for (i = 0; i < rows; i++)
	{
		free(B[i]);
		B[i] = NULL;
	}
	free(B);
}
// --------------------------- //
