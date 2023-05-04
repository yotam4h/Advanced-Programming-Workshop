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
#include <string.h>
#include <ctype.h>

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
int parseline(char const *line);
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
	total2 = memoryReport(PATH2);
	// total3 = memoryReport(PATH3);

	// write output:
	printf("Output:\n");
	// printf("First file required %d bytes\n", total1);
	printf("Second file required %d bytes\n", total2);
	// printf("Third file required %d bytes\n", total3);

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

	FILE *fd = NULL;
	int totalsize = 0, buffersize, typesize[] = {4, 8, 8, 4, 2, 1, 4, 4};
	char *buffer = NULL;

	// TODO: edgecases

	fd = fopen(filename, "r");
	// count buffer size (count the longest line)
	buffersize = flenLongestLine(fd);
	// allocate buffer
	buffer = (char *)malloc(buffersize * sizeof(char));
	// TODO: if NULL

	// read line
	fgets(buffer, buffersize, fd);
	while (!feof(fd))
	{
		// parse line
		totalsize += parseline(buffer);
		// read next line
		fgets(buffer, buffersize, fd);
	}

	// dumpster
	free(buffer);
	buffer = NULL;
	fclose(fd);
	fd = NULL;
	return totalsize;
}
// file: length of longest line
int flenLongestLine(FILE *fd)
{
	int count = 0, max = 0;
	char ch;

	// TODO: edgecases

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


// TODO implement: parse matrix, double spaces...
int parseline(char const *line)
{
	// var decleration
	int i, j, typesize[] = {4, 8, 8, 4, 2, 1, 4, 4}, totalsize = 0, currentsize;
	// ! move types and typesize to  memoryReport!!!!!!!
	char *types[8] = {"unsigned int",
					  "long long",
					  "double",
					  "float",
					  "short",
					  "char",
					  "long",
					  "int"};
	struct
	{
		int typeSize;
		int count;
		int isptr;
	} data = {-1, 1, 0};

	// TODO: edgecases

	// body
	for (i = 0; i < 8; i++)
	{
		if (strstr(line, types[i]))
		{
			data.typeSize = typesize[i];
			break;
		}
	}
	// TODO: edgecases for above loop
	// ! gotta make it better
	i = strlen(types[i]);
	while (line[i] != '\0')
	{
		if (line[i] == ';')
		{
			currentsize = data.count * (data.isptr == 0 ? data.typeSize : 4);
			totalsize += currentsize;
			printf(" requires %d bytes\n", currentsize);
			break;
		}
		else if (line[i] == ',')
		{
			currentsize = data.count * (data.isptr == 0 ? data.typeSize : 4);
			totalsize += currentsize;
			printf(" requires %d bytes\n", currentsize);
			data.count = 1;
			data.isptr = 0;
		}
		else if (line[i] == '*')
		{
			data.isptr = 1;
		}
		else if (line[i] == '[')
		{
			j = i + 1;
			data.count = line[j++] - '0';
			while (line[j] != ']')
			{
				data.count = (data.count * 10) + (line[j] - '0');
				j++;
			}
			i += j - i;
		}
		else if(isalnum(line[i])) //if (line[i] != ']')
		{
			putchar(line[i]);
		}
		i++;
	}
	return totalsize;
}

// --------------------------- //
