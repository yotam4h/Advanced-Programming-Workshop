#include <stdio.h>
#include <stdlib.h>

int countLines(char *filename);
void letterFrequency(char *filename, int *counts);
void removeSpaces(char *infile, char *outfile);
void createFile(char *filename);

void f1()
{
    int lines;
    lines = countLines("in.txt");
    if (lines != -1)
        printf("%d", lines);
}
void f2()
{
    int counter[26] = {0};
    letterFrequency("in.txt", counter);
}
void f3()
{
    removeSpaces("in.txt", "out.txt");
}
int main()
{
    createFile("in.txt");
    f3();
    return EXIT_SUCCESS;
}

int countLines(char *filename)
{
    int count = 1;
    char ch;
    FILE *fd = NULL;
    fd = fopen(filename, "r");

    if (fd == NULL)
    {
        perror("fml");
        return -1;
    }
    do
    {
        ch = fgetc(fd);
        if (ch == '\n')
            count++;
    } while (!feof(fd));

    fclose(fd);
    fd = NULL;

    return count;
}

void letterFrequency(char *filename, int *counts)
{
    FILE *fd = NULL;
    char ch;
    int i;
    // wipe counts;
    for (i = 0; i < 26; i++)
        counts[i] = 0;

    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        perror("fml");
        return;
    }

    do
    {
        ch = fgetc(fd);
        if ('a' <= ch && ch <= 'z')
            counts[ch - 'a']++;
        if ('A' <= ch && ch <= 'Z')
            counts[ch - 'A']++;

    } while (!feof(fd));

    fclose(fd);
    fd = NULL;

    for (i = 0; i < 26; i++)
    {
        printf("%-4c", i + 'A');
    }
    printf("\n");
    for (i = 0; i < 26; i++)
    {
        printf("%-4d", counts[i]);
    }
}

void removeSpaces(char *infile, char *outfile)
{
    FILE *in = NULL, *out = NULL;
    char ch;

    in = fopen(infile, "r");
    if (in == NULL)
    {
        perror("fml");
        return;
    }
    out = fopen(outfile, "w");

    // do
    // {
    //     ch = fgetc(in);
    //     if (ch == ' ' || ch == EOF)
    //         continue;
    //     fputc(ch, out);

    // } while (!feof(in));

    ch = fgetc(in);
    while (!feof(in))
    {
        if (ch == ' ')
        {
            ch = fgetc(in);
            continue;
        }
        fputc(ch, out);
        ch = fgetc(in);
    }

    fclose(out);
    out = NULL;
    fclose(in);
    in = NULL;
}

void createFile(char *filename)
{
    FILE *fd = NULL;
    char ch;

    fd = fopen(filename, "w");
    printf("Created file: %s\n", filename);

    printf("Scanning input to file: %s, EOF to stop.\n", filename);
    while ((ch = getchar()) != EOF)
    {
        fputc(ch, fd);
    }

    fclose(fd);
    fd = NULL;
}
