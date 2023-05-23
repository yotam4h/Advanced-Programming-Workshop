// Course: Advanced C programming
// exercise 2, question 4
// file name: ex2_q3.c

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
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define scanf_s scanf
// #define PATH1 "c:\\temp\\file1.txt"
// #define PATH2 "c:\\temp\\file2.txt"
// #define PATH3 "c:\\temp\\file3.txt"
#define PATH1 "file1.txt"
#define PATH2 "file2.txt"
#define PATH3 "file3.txt"

// enum for switch case
enum
{
	ENDDECLERATION = ';',
	NEXTVAR = ',',
	POINTER = '*',
	BRACKET = '['
};
// enum for switch case
enum
{
	CHAR = 'c',
	DOUBLE = 'd',
	FLOAT = 'f',
	UINT = 'u',
	INT = 'i',
	LONG = 'l',
	SHORT = 's'
};

// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

int memoryReport(char *filename);
int dataType(char input, FILE *fd);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	int total1, total2, total3;
	int mytotal;
	// Start Program:
	printf("Start Program\n");
	// int mytotal;
	mytotal = memoryReport("edgecases.txt");
	// call functions:
	// total1 = memoryReport(PATH1);
	// total2 = memoryReport(PATH2);
	// total3 = memoryReport(PATH3);

	// write output:
	printf("Output:\n");

	printf("File required %d bytes\n", mytotal);
	// printf("First file required %d bytes\n", total1);
	// printf("Second file required %d bytes\n", total2);
	// printf("Third file required %d bytes\n", total3);

	return 0;
}
// --------------------------- //

/// <summary>
/// The function receives a pointer to a string, representing a path to a file.
/// The function output all varibles declerations and their size input byte.
/// </summary>
/// <param>char *filename - valid path to a file</param>
/// <returns>total bytes required</returns>
int memoryReport(char *filename)
{
	// your code:

	// --------------------------------------- //
	// Variables declration:
	// --------------------------------------- //
	FILE *fd = NULL;
	char input;
	int memory = 0, num = 0;
	// for each variable report
	struct
	{
		int size;  // sizeof(var)
		int times; // how many (if array)
		bool isptr;
	} var = {-1, 1, false};

	// --------------------------------------- //
	// Edgecases.
	// --------------------------------------- //
	if (filename == NULL)
		return -1;

	fd = fopen(filename, "r");
	if (fd == NULL)
	{
		perror("Error");
		return -1;
	}

	// --------------------------------------- //
	// Iterate file.
	// --------------------------------------- //
	while ((input = fgetc(fd)) != EOF)
	{
		// --------------------------------------- //
		// Skip whitespace.
		// --------------------------------------- //
		if (isspace(input))
			continue;
		// --------------------------------------- //
		// Parse data type.
		// --------------------------------------- //
		else if (var.size == -1)
		{
			var.size = dataType(input, fd);
			if(var.size == -2)
			{
				printf("! Error: data type not found\n");
				return -1;
			}
		}
		// --------------------------------------- //
		// Parse name, pointer, array/matrix, next line.
		// --------------------------------------- //
		else
		{
			switch (input)
			{
			case ENDDECLERATION:
			{
				// add var memory to total memory sum
				memory += var.times * (var.isptr ? 4 : var.size);
				// output var memory
				printf(" requires %d bytes\n", var.times * (var.isptr ? 4 : var.size));
				// reset var
				var.isptr = false;
				var.size = -1;
				var.times = 1;
			}
			break;
			case NEXTVAR:
			{
				// add var memory to total memory sum
				memory += var.times * (var.isptr ? 4 : var.size);
				// output var memory
				printf(" requires %d bytes\n", var.times * (var.isptr ? 4 : var.size));
				// new var of same type
				var.isptr = false;
				var.times = 1;
			}
			break;
			case POINTER:
			{
				var.isptr = true;
			}
			break;
			case BRACKET:
			{
				// get num in [BRACKETS]
				while ((input = fgetc(fd)) != EOF && input != ']')
				{
					if (isdigit(input))
					{
						num = (num * 10) + (input - '0');
					}
				}
				// multiply var.times
				if (num > 0)
				{
					var.times *= num;
					num = 0;
				}
			}
			break;
			default:
			{
				// print var name
				putchar(input);
			}
			break;
			}
		}
	}
	printf("\n");

	// Dumpster
	fclose(fd);
	fd = NULL;
	return memory;
}

int dataType(char input, FILE *fd)
{
	char checkll[5];
	int size = -2;

	switch (input)
	{
	case CHAR:
	{
		fseek(fd, 3, SEEK_CUR);
		size = sizeof(char);
	}
	break;
	case DOUBLE:
	{
		fseek(fd, 5, SEEK_CUR);
		size = sizeof(double);
	}
	break;
	case FLOAT:
	{
		fseek(fd, 4, SEEK_CUR);
		size = sizeof(float);
	}
	break;
	case UINT:
	{
		fseek(fd, 9, SEEK_CUR);
	} // notice there is no break;
	case INT:
	{
		fseek(fd, 2, SEEK_CUR);
		size = sizeof(int);
	}
	break;
	case LONG:
	{
		fseek(fd, 4, SEEK_CUR);

		// LONG LONG
		fgets(checkll, 5, fd);
		if (strstr(checkll, "long"))
		{
			size = sizeof(long long);
		}
		else
		{
			fseek(fd, -5, SEEK_CUR);
			size = sizeof(long);
		}
	}
	break;
	case SHORT:
	{
		fseek(fd, 4, SEEK_CUR);
		size = sizeof(short);
	}
	break;
	default:
	{
		size = -2;
	}
	break;
	}

	return size;
}

// --------------------------- //
