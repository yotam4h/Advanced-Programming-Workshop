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
int toSeries(char *);
void eraseChar(char *);

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
    //strcpy(test, "A");
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
    int i;
    if (string == NULL)
        return;

    while (*string)
    {
        i = convertChar(string);
        string += i;
    }
}

/**
 *
 * @param string A pointer to a character array (string) that will be modified by the function.
 *
 * @return offset index.
 */
int convertChar(char *string)
{
    int length = 0;

    if (inSegment(*string, 'a', 'f') || inSegment(*string, 'A', 'F') || inSegment(*string, '0', '9')) // [a-f] or [A-F] or [1-9]
    {
        length = toSeries(string);
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
        eraseChar(string);
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

int toSeries(char *org)
{
    char num[] = "123456789",
         xlower[] = "abcdef",
         xupper[] = "ABCDEF",
         series[30],
         buffer[BUFFER];

    series[0] = '\0';
    buffer[0] = '\0';
    buffer[sizeof(buffer) - 1] = '\0';

    if (org == NULL || !(*org))
    {
        return 0;
    }

    if (inSegment(*org, '1', '9'))
    {
        strncpy(series, num, *org - '0');
        series[*org - '0'] = '\0';
    }
    else if (inSegment(*org, 'a', 'f'))
    {
        strcpy(series, num);
        strncat(series, xlower, *org - 'a' + 1);
        series[10 + *org - 'a'] = '\0';
    }
    else if (inSegment(*org, 'A', 'F'))
    {
        strcpy(series, num);
        strncat(series, xupper, *org - 'A' + 1);
        series[10 + *org - 'A'] = '\0';
    }

    if (*series)
    {
        strcpy(buffer,series);
        strcat(buffer, org + 1);
        strcpy(org, buffer);
    }

    return strlen(buffer);
}

void eraseChar(char *org)
{
    char buffer[BUFFER];
    buffer[0] = '\0';
    buffer[sizeof(buffer) - 1] = '\0';
    if (org == NULL || *org)
    {
        return;
    }

    strcpy(buffer, org + 1);
    strcpy(org, buffer);
    buffer[0] = '\0';
}
