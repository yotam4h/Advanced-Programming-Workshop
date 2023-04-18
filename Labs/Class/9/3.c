#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void reduceWhiteSpace(char *toProc);
void squeezeSpaces(char *s);

int main()
{
    char test[50];

    printf("please enter a string: ");
    scanf("%49[^\n]", test);
    rewind(stdin);

    puts(test);
    squeezeSpaces(test);
    puts(test);

    return 0;
}

void reduceWhiteSpace(char *s)
{
    char *back = NULL, *front = NULL;

    if (s == NULL || *s == '\0')
        return;

    back = s;
    front = s + 1;

    while (*front)
    {
        if (*front != ' ' || *back != ' ')
            *(++back) = *front;
        front++;
    }
    *(back + 1) = '\0';
}

void squeezeSpaces(char *s)
{
    char *read = s, *write=s;
    bool space = false;

    if (s == NULL || *s == '\0')
        return;
    // while (*read != '\0')
    // {
    //     if (*read != ' ')
    //     {
    //         *write++ = *read++;
    //         space = false;
    //     }
    //     else if (*read == ' ' && space == false)
    //     {
    //         *write++ = ' ';
    //         space = true;
    //     }
    //     else
    //     {
    //         read++;
    //     }
    // }

    // *write = '\0';

    while (*read != '\0')
    {
        if (!isspace(*read))
        {
            *write++ = *read++;
            space = false;
        }
        else if (isspace(*read) && space == false)
        {
            *write++ = ' ';
            space = true;
        }
        else
        {
            read++;
        }
    }

    *write = '\0';

    write = NULL;
    read = NULL;
}
