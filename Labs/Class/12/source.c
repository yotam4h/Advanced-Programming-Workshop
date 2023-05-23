#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct account
{
    int id;
    char name[31];
    double sum;
} Account;

int updateCustomer(int id, double cartSum, char *filename);
int createFile(char *filename);
int createBinFile(char *filename);
void printBinFile(char *filename);
int updateBinCustomer(int id, double cartSum, char *filename);

int main() // ohadbi@my.hit.ac.il
{
    // char *name = "data.txt";
    char *bname = "data.bin";
    if (!createBinFile(bname))
    {
        return EXIT_FAILURE;
    }
    else
    {
        printBinFile(bname);
        updateBinCustomer(333444555, 500.5, bname);
        printBinFile(bname);
    }
    // if (!createFile(name))
    // {
    //     return EXIT_FAILURE;
    // }
    // else if (!updateCustomer(212345678, 200, name))
    // {
    //     return EXIT_FAILURE;
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

    fout = fopen(filename, "w");
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

int updateBinCustomer(int id, double cartSum, char *filename)
{
    FILE *fd = NULL;
    Account acc = {0, "", 0};

    fd = fopen(filename, "rb+");
    if (fd == NULL)
    {
        perror("! Error");
        return 0;
    }
    else
    {
        fread(&acc, sizeof(Account), 1, fd);
        while (!feof(fd))
        {
            if (acc.id == id)
            {
                fseek(fd, -(int)sizeof(Account), SEEK_CUR);
                acc.sum += cartSum;
                fwrite(&acc, sizeof(Account), 1, fd);
                fclose(fd);
                fd = NULL;
                return 1;
            }
            fread(&acc, sizeof(Account), 1, fd);
        }
    }

    fclose(fd);
    fd = NULL;
    return 0;
}

int createBinFile(char *filename)
{
    FILE *fout = NULL;
    Account acc = {0, "", 0};
    int check;

    fout = fopen(filename, "wb");
    if (fout == NULL)
    {
        perror("! Error");
        return 0;
    }
    else
    {

        printf("! Writing to file %s\n! Enter ID, Name, Sum by order. Spam EOF to stop.\n? ", filename);
        check = scanf(" %9i %30s %lf", &acc.id, acc.name, &acc.sum);
        while (check == 3)
        {
            fwrite(&acc, sizeof(Account), 1, fout);
            printf("? ");
            check = scanf(" %9i %30s %lf", &acc.id, acc.name, &acc.sum);
        }
    }
    printf("\n! Finished input. \n\n");
    fclose(fout);
    fout = NULL;
    return 1;
}

void printBinFile(char *filename)
{
    FILE *fin = NULL;
    Account acc;

    fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        perror("! Error");
        return;
    }
    else
    {
        printf("! Printing file:\n");
        fread(&acc, sizeof(Account), 1, fin);
        while (!feof(fin))
        {
            printf("! ID:\t%-9i\t\tName:\t%-s\t\tSum:\t%-.2lf\n", acc.id, acc.name, acc.sum);
            fread(&acc, sizeof(Account), 1, fin);
        }
        printf("\n");
    }
    fclose(fin);
    fin = NULL;
}
