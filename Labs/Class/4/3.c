#include <stdio.h>
#include <stdlib.h>

typedef struct apartment
{
    char address[30];
    int rooms;
    double price;
} Apartment;

Apartment *inRange(const Apartment *const data, const int dataSize, const int wantedrooms, const double maxprice, int *myrangeSize);

int main()
{
    Apartment data[3] = {{"1st Street", 2, 1000.0},
                         {"2nd Street", 2, 2000.0},
                         {"3rd Street", 3, 3000.0}};
    int dataSize = 3;
    int wantedrooms = 2;
    double maxprice = 2000.0;
    int myrangeSize = 0;
    Apartment *myrange = NULL;

    myrange = inRange(data, dataSize, wantedrooms, maxprice, &myrangeSize);
    for (int i = 0; i < myrangeSize; i++)
    {
        printf("%s %d %.2f\n", (myrange + i)->address, (myrange + i)->rooms, (myrange + i)->price);
    }

    free(myrange);
    myrange = NULL;

    return 0;
}

Apartment *inRange(const Apartment *const data, const int dataSize, const int wantedrooms, const double maxprice, int *myrangeSize)
{
    int i, j;
    Apartment *myrange = NULL;
    // count apartments in price range
    for (i = 0; i < dataSize; i++)
    {
        if ((data + i)->rooms == wantedrooms && (data + i)->price <= maxprice)
        {
            (*myrangeSize)++;
        }
    }
    myrange = (Apartment *)malloc((*myrangeSize) * sizeof(Apartment));
    if(!myrange)
        return NULL;
    // copy apartments in range into myrange array
    for (i = j = 0; i < dataSize; i++)
    {
        if ((data + i)->rooms == wantedrooms && (data + i)->price <= maxprice)
        {
            *(myrange + (j++)) = *(data + i);
        }
    }

    return myrange;
}