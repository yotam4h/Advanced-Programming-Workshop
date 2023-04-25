#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100

void ex2();
void ex3();
int idxLastChar(const char *, const char);
void switchStrings(char *, char *);
void swapch(char *, char *);
void convert(char *);
int convertChar(char *);
int inSegment(int, int, int);
char toUpper(char);
char toLower(char);
char *toSeries(int);

int main()
{
    ex3();
    return EXIT_SUCCESS;
}

void ex2()
{
    char test1[50], test2[50];
    puts("Please enter string 1:");
    fgets(test1, 49, stdin);
    puts("Please enter string 2:");
    fgets(test2, 49, stdin);
    printf("String 1: %s", test1);
    printf("String 2: %s", test2);
    switchStrings(test1, test2);
    printf("String 1: %s", test1);
    printf("String 2: %s", test2);
}

void ex3()
{
    char test[100];
    strcpy(test, "B$q0#3Me");
    puts(test);
    convert(test);
    puts(test);
}

int idxLastChar(const char *string, const char findMe)
{
    char *lastOccurrence = strrchr(string, findMe);
    if (!lastOccurrence)
        return (-1);

    return lastOccurrence - string;
}

void switchStrings(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        swapch(str1++, str2++);
    }
    if (*str1)
    {
        swapch(str1++, str2++);
        while (*str1)
        {
            *str2++ = *str1++;
        }
    }
    if (*str2)
    {
        swapch(str1++, str2++);
        while (*str2)
        {
            *str1++ = *str2++;
        }
    }
}

void swapch(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void convert(char *string)
{
    if (string == NULL)
        return;

    while (*string)
    {
        string += convertChar(string);
    }
}

/**
 *
 * @param string A pointer to a character array (string) that will be modified by the function.
 *
 * @return integer value, length of added changes to the string.
 */
int convertChar(char *string)
{
    char *series = NULL;
    char buffer[BUFFER];
    int length = 0;

    if (inSegment(*string, 'a', 'f') || inSegment(*string, 'A', 'F') || inSegment(*string, '1', '9')) // [a-f] or [A-F] or [1-9]
    {
        series = toSeries(*string);
        strcpy(buffer, series);
        {
            length = strlen(series);
            free(series);
            series = NULL;
        }
        strcat(buffer, string + 1);
        strcpy(string, buffer);
        buffer[0] = '\0';
    }
    else if (inSegment(*string, 'g', 'z')) // [g-z]
    {
        *string = toUpper(*string);
        length = 1;
    }
    else if (inSegment(*string, 'G', 'Z')) // [G-Z]
    {
        *string = toLower(*string);
        length = 1;
    }
    else // any other char
    {
        strcpy(string, string + 1);
    }

    return length;
}

/**
 * The function checks if a given integer is within a specified closed range.
 *
 * @param x an integer value
 * @param begin The beginning of the interval.
 * @param end The end of the interval.
 *
 * @return boolean value.
 */
int inSegment(int x, int begin, int end)
{
    if (begin > end)
    {
        return 0;
    }
    return (begin <= x && x <= end);
}

char toUpper(char ch)
{
    if (!inSegment(ch, 'a', 'z'))
        return ch;
    return (char)(ch - 'a' + 'A');
}

char toLower(char ch)
{
    if (!inSegment(ch, 'A', 'Z'))
        return ch;
    return (char)(ch - 'A' + 'a');
}

/**
 * The function takes an integer input and returns a string representing a series of numbers or letters
 * based on the input value.
 *
 * @param ch The input parameter `ch` is an integer representing a hexadecimal digit.
 *
 * @return The function `toSeries` returns a dynamically allocated character array (`char*`) that
 * contains a series of characters based on the input `ch`.
 */
char *toSeries(int ch)
{
    char num[] = "123456789",
         xlower[] = "abcdef",
         xupper[] = "ABCDEF";

    char *dest = (char *)malloc(16 * sizeof(char));

    dest[0] = '\0';

    if (inSegment(ch, '1', '9'))
    {
        strncpy(dest, num, ch - '0');
        dest[ch - '0'] = '\0';
    }
    else if (inSegment(ch, 'a', 'f'))
    {
        strcpy(dest, num);
        strncat(dest, xlower, ch - 'a' + 1);
        dest[10 + ch - 'a'] = '\0';
    }
    else if (inSegment(ch, 'A', 'F'))
    {
        strcpy(dest, num);
        strncat(dest, xupper, ch - 'A' + 1);
        dest[10 + ch - 'A'] = '\0';
    }
    else
    {
        free(dest);
        dest = NULL;
    }

    return dest;
}