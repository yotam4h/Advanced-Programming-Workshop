#include <stdio.h>
#include <stdlib.h>

typedef struct apartment
{
    char address[30];
    int rooms;
    double price;
} Apartment;

// TODO: drive code for inRange function
int main()
{

    return 0;
}

// TODO: copy into inrage, return inrage address, return by reference inrage size
Apartment *inRange(const Apartment *const data, const int dataSize, const int wantedrooms, const double maxprice)
{
    int i, myrangeSize;
    Apartment *myrange = NULL;
    // count apartments in price range
    for (i = 0; i < dataSize; i++)
    {
        if ((data + i)->rooms == wantedrooms && (data + i)->price <= maxprice)
        {
            myrangeSize++;
        }
    }
    myrange = (Apartment *)malloc(myrangeSize * sizeof(Apartment));
    // copy apartments in range into myrange array
    for (i = 0; i < dataSize; i++)
    {
        if ((data + i)->rooms == wantedrooms && (data + i)->price <= maxprice)
        {
        
        }
    }


}