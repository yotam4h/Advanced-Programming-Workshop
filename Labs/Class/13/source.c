#include <stdio.h>
#include <stdlib.h>

void printBits(int num);
int leftshift(int num, int shift);
int rightshift(int num, int shift);

int main()
{
    int (*shift[2])(int, int) = {leftshift, rightshift};
    int num, shiftNum, i;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Enter a shift number: ");
    scanf("%d", &shiftNum);
    printf("Menu:\n");
    printf("1. Left shift\n");
    printf("2. Right shift\n");
    printf("Enter your choice: ");
    scanf("%d", &i);
    printBits(num);
    printBits((*shift[i-1])(num, shiftNum));


    return EXIT_SUCCESS;
}

int leftshift(int num, int shift)
{
    int mask;
    while(shift--)
    {
        mask = 1 << 31;
        mask = num & mask;
        num = num << 1;
        num = num | (mask >> 31);
    }
    return num;
}

int rightshift(int num, int shift)
{
    int mask;
    while(shift--)
    {
        mask = 1;
        mask = num & mask;
        num = num >> 1;
        num = num | (mask << 31);
    }
    return num;
}

void printBits(int num)
{
    int i;
    printf("%d Bits: ", num);
    for (i = 31; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}
