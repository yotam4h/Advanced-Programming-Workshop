#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverseString(char *toRev);
void swap(char *a, char *b);

int main()
{
    char test[50];
    strcpy(test, "abcba");
    puts(test);
    printf("%d\n", reverseString(test));
    puts(test);
    putchar(10);

    strcpy(test, "abcdea");
    puts(test);
    printf("%d\n", reverseString(test));
    puts(test);
    return 0;
}

int reverseString(char *toRev)
{
    char *left = NULL,
         *right = NULL;

    int flag = 1, len = strlen(toRev);

    if (len == 0 || len == 1)
        return 1;

    left = toRev;
    right = toRev + len - 1;

    while (left < right)
    {
        if (*left != *right)
        {
            swap(left, right);
            flag = 0;
        }
        left++;
        right--;
    }
    return flag;
}

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}