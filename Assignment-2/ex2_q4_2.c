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

// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

int memoryReport(char *filename);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	int total1, total2, total3;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	// total1 = memoryReport(PATH1);
	// total2 = memoryReport(PATH2);
	total3 = memoryReport(PATH3);

	// write output:
	printf("Output:\n");
	// printf("First file required %d bytes\n", total1);
	// printf("Second file required %d bytes\n", total2);
	printf("Third file required %d bytes\n", total3);

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

	FILE *fd = NULL;
	char input, checkll[5];
	int memory = 0, num = 0;
	// for each variable report
	struct
	{
		int size;  // sizeof(var)
		int times; // how many (if array)
		bool isptr;
	} var = {-1, 1, false};
	bool unknowntype = true;

	if (filename == NULL)
		return -1;

	fd = fopen(filename, "r");
	if (fd == NULL)
		return -1;

	while ((input = fgetc(fd)) != EOF)
	{
		if (input == ';')
		{
			unknowntype = true;

			memory += var.times * (var.isptr ? 4 : var.size);
			printf(" requires %d bytes\n", var.times * (var.isptr ? 4 : var.size));
			// reset var
			var.isptr = false;
			var.size = -1;
			var.times = 1;
		}
		else if (unknowntype && !isspace(input))
		{
			switch (input)
			{
			case 'c': // char
				var.size = sizeof(char);
				fseek(fd, 3, SEEK_CUR);
				break;
			case 'd': // double
				var.size = sizeof(double);
				fseek(fd, 5, SEEK_CUR);
				break;
			case 'f': // float
				var.size = sizeof(float);
				fseek(fd, 4, SEEK_CUR);
				break;
			case 'i': // int
				var.size = sizeof(int);
				fseek(fd, 2, SEEK_CUR);
				break;
			case 'l':		  // long // TODO: long long
				var.size = sizeof(long);
				fseek(fd, 4, SEEK_CUR);

				fgets(checkll, 5, fd);

				if (strstr(checkll, "long"))
				{
					var.size = sizeof(long long);
				}
				else
				{
					fseek(fd, -5, SEEK_CUR);
				}

				break;
			case 's': // short
				var.size = sizeof(short);
				fseek(fd, 4, SEEK_CUR);
				break;
			case 'u': // unsigned int
				var.size = sizeof(unsigned int);
				fseek(fd, 11, SEEK_CUR);
				break;
			default:
				return -1;
				break;
			}
			unknowntype = false;
		}
		else if (input == ',')
		{
			memory += var.times * (var.isptr ? 4 : var.size);
			printf(" requires %d bytes\n", var.times * (var.isptr ? 4 : var.size));
			// new var of same type
			var.isptr = false;
			var.times = 1;
		}
		else if (input == '*')
		{
			var.isptr = true;
		}
		else if (input == '[')
		{
			while ((input = fgetc(fd)) != EOF && input != ']')
			{
				if (isdigit(input))
				{
					num = (num * 10) + (input - '0');
				}
			}
			if (num > 0)
			{
				var.times *= num;
				num = 0;
			}
		}
		else if (!isspace(input))
		{
			putchar(input);
		}
	}
	printf("\n");

	// dumpster
	fclose(fd);
	fd = NULL;
	return memory;
}

// --------------------------- //
