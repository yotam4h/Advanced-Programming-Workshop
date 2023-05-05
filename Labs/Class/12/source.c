#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int updateCustomer(char *id, double cartSum, char *filename);

int main()
{
    if (updateCustomer("06842151", 200, "data.txt"))
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

int updateCustomer(char *id, double cartSum, char *filename)
{
    FILE *fd = NULL;
    int i;
    double sum = -1;
    char buffer[255];
    buffer[254] = '\0';

    fd = fopen(filename, "r+");
    // file didnt open
    if (fd == NULL)
    {
        perror("Error");
        return 0;
    }

    // dumpster
    fclose(fd);
    fd = NULL;

    return 1;
}
