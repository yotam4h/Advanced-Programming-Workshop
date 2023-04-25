#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stringWhat
{
    int lowercase;
    int uppercase;
    int numbers;
    int other;
} stringWhatDefault = {0, 0, 0, 0};

typedef struct stringWhat StringWhat;

StringWhat countString(char *toProc);

int main()
{
    char test[50];
    StringWhat what;
    strcpy(test, "Isr 1");
    what = countString(test);
    printf("lower = %i, upper = %i, numbers = %i, other %i\n", what.lowercase, what.uppercase, what.numbers, what.other);
    return 0;
}

StringWhat countString(char *toProc)
{
    StringWhat what;

    while (*toProc != '\0')
    {
        if ('a' <= *toProc && *toProc <= 'z')
        {
            what.lowercase++;
        }
        else if ('A' <= *toProc && *toProc <= 'Z')
        {
            what.uppercase++;
        }
        else if ('0' <= *toProc && *toProc <= '9')
        {
            what.numbers++;
        }
        else
        {
            what.other++;
        }

        toProc++;
    }

    return what;
}