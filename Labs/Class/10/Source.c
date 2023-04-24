#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int idxLastChar(const char *const string, const char findMe);
void swapch(char *a, char *b);
void switchStrings(char *org, char *dst);

int main()
{
    char test1[50] = "abc";
    char test2[50] = "Hello!";
    printf("%i\n\n", idxLastChar(test1, 'a'));
    puts(test1);
    puts(test2);
    switchStrings(test1, test2);
    puts(test1);
    puts(test2);

    return 0;
}

int idxLastChar(const char *const string, const char findMe)
{
    char *lastOccurrence = strrchr(string, findMe);
    if (!lastOccurrence)
        return (-1);

    return lastOccurrence - string;
}

void switchStrings(char *org, char *dst)
{
    while (*org && *dst)
    {
        swapch(org++, dst++);
    }
    if (*org)
    {
        swapch(org++, dst++);
        while (*org)
        {
            *dst++ = *org++;
        }
    }
    if (*dst)
    {
        swapch(org++, dst++);
        while (*dst)
        {
            *org++ = *dst++;
        }
    }
}

void swapch(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}