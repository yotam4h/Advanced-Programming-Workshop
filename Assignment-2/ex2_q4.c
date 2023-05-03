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
int flenLongestLine(FILE *fd);

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	int total1, total2, total3;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	total1 = memoryReport(PATH1);
	total2 = memoryReport(PATH2);
	total3 = memoryReport(PATH3);

	// write output:
	printf("Output:\n");
	printf("First file required %d bytes\n", total1);
	printf("Second file required %d bytes\n", total2);
	printf("Third file required %d bytes\n", total3);

	return 0;
}
// --------------------------- //

/// <summary>
/// The function receives a pointer to a string, representing a path to a file.
/// The function output all varibles declerations and their size in byte.
/// </summary>
/// <param>char *filename - valid path to a file</param>
/// <returns>total bytes required</returns>
int memoryReport(char *filename)
{
	// your code:
	// data types: char, short, int, unsigned int, long, long long, float, double
	// calcVar: dataType*sizeof(dataType)*howMany

	FILE *fd = NULL;
	char *buffer = NULL;
	int buffersize;
	// TODO: edgecases

	fd = fopen(filename, "r");
	// count buffer size (count the longest line)
	buffersize = flenLongestLine(fd);
	// allocate buffer
	buffer = (char *)malloc(buffersize * sizeof(char));
	// TODO: if NULL

	fgets(buffer, buffersize, fd);
	fputs(buffer,stdout);

	// read line
	// memory report line
	fclose(fd);
	fd = NULL;
	// TODO: free and nullify buffer
	return 0;
}
// file: length of longest line
int flenLongestLine(FILE *fd)
{
	int count = 0, max = 0;
	char ch;

	if (fd == NULL)
		return -1;

	fseek(fd, 0, SEEK_SET);

	while ((ch = fgetc(fd)) != EOF)
	{
		if (ch == ';')
		{
			max = count > max ? count : max;
			count = 0;
		}
		count++;
	}

	fseek(fd, 0, SEEK_SET);

	return max + 1;
}
// --------------------------- //
