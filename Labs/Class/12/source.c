#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int updateCustomer(int id, double cartSum, char *filename);
int createFile(char *filename);

int main()
{
    char *name = "data.txt";
    // if (!createFile(name))
    // {
    //     return EXIT_FAILURE;
    // }
    // else
    // {
    if (!updateCustomer(212345678, 200, name))
    {
        return EXIT_FAILURE;
    }
    // }
    return EXIT_SUCCESS;
}

int createFile(char *filename)
{
    FILE *fout = NULL;
    int id;
    char name[31];
    double sum;
    int check;

    fout = fopen(filename, "a");
    if (fout == NULL)
    {
        perror("! Error");
        return 0;
    }
    else
    {
        printf("! Writing to file %s\n! Enter ID, Name, Sum by order. Spam EOF to stop.\n? ", filename);
        check = scanf(" %9i %30s %lf", &id, name, &sum);
        while (check == 3)
        {
            fprintf(fout, "%9i%30s%8.2lf\n", id, name, sum);
            printf("? ");
            check = scanf("  %9i %30s %lf", &id, name, &sum);
        }
    }
    fclose(fout);
    fout = NULL;
    return 1;
}

int updateCustomer(int id, double cartSum, char *filename)
{
    // declerations
    FILE *fin = NULL, *fout = NULL;
    int getid = 0;
    char getname[31];
    double sum = -1;

    // char line[255], getid[9], getname[31];
    // // --

    // edgecases
    // --

    // initialize
    // memset(line, '\0', 255);
    // memset(getid, '\0', 9);
    memset(getname, '\0', 31);

    fin = fopen(filename, "r");
    // file didnt open
    if (fin == NULL)
    {
        perror("Error");
        return 0;
    }
    else
    {
        fout = fopen("temp.txt", "w");
        if (fout == NULL)
        {
            perror("Error");
            return 0;
        }
        else
        {
            fscanf(fin, " %9i %30s %lf", &getid, getname, &sum);
            while (!feof(fin))
            {
                if (getid == id)
                {
                    sum += cartSum;
                }
                fprintf(fout, "%9i%30s%8.2lf\n", getid, getname, sum);
                fscanf(fin, "  %9i %30s %lf", &getid, getname, &sum);
            }
        }
    }
    // dumpster
    fclose(fin);
    fin = NULL;
    fclose(fout);
    fout = NULL;
    // --

    // rename
    if (remove(filename))
    {
        perror("Error");
        return 0;
    }
    if (rename("temp.txt", filename))
    {
        perror("Error");
        return 0;
    }
    // --

    return 1;
}
// int updateCustomer(char *id, double cartSum, char *filename)
// {
//     FILE *fout = NULL;
//     double sum = -1;
//     long pos;
//     char line[10];
//     line[9] = '\0';
//     // edgecases

//     fout = fopen(filename, "r+");
//     // file didnt open
//     if (fout == NULL)
//     {
//         perror("Error");
//         return 0;
//     }

//     // try 1.
//     fscanf(fout, "%[0-9] %*[A-Za-z]", line);
//     pos = ftell(fout);
//     fscanf(fout, "%lf", &sum);
//     while (!feof(fout))
//     {
//         if (!strcmp(line, id))
//         {
//             sum += cartSum;
//             fseek(fout, pos, SEEK_SET);
//             fprintf(fout, "%8.2lf", sum);
//             fputs(" ", fout);
//             pos = ftell(fout);
//             while ((*line = fgetc(fout)) != '\n')
//             {
//                 fputc(' ', fout);
//             }
//             break;
//         }
//         fgets(line, 9, fout);
//         fscanf(fout, "%[0-9] %*[A-Za-z]", line);
//         pos = ftell(fout);
//         fscanf(fout, "%lf", &sum);
//     }

//     // dumpster
//     fclose(fout);
//     fout = NULL;

//     return 1;
// }
