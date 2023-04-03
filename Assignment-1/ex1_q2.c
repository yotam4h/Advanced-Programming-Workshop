// Course: Advanced C programming
// exercise 1, question 2
// file name: ex1_q2.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --------------------------- //
//
//	Assigned by:
//		Student1_Full_Name #ID
//		Student2_Full_Name #ID
//
// --------------------------- //

// structs and function declarations section:
typedef struct point
{
    int x, y;
} point;

typedef struct polygon
{
    int n;
    point *points;
    double scope;
} polygon;

void scanPoint(point *p);
polygon *createPolygon();
double distance(point *p1, point *p2);
double calculateScope(point *points, int n);
int addPoint(polygon *poly);
int removePoint(polygon *poly, int idx);
void freeMemory(polygon *poly);

// --------------------------- //

int main()
{
    int i, n, idx;
    polygon *poly;

    // Start Program:
    printf("Start Program\n");

    // call functions:
    poly = createPolygon();
    printf("How many points to add: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Point #%d: \n", i + 1);
        addPoint(poly);
    }

    printf("Enter index value to remove, invalid index to stop: ");
    do
    {
        scanf("%d", &idx);
    } while (removePoint(poly, idx));

    // write output:
    printf("Output: Scope of polygon: %.2lf\n", poly->scope);
    freeMemory(poly);

    return 0;
}
// --------------------------- //

/// <summary>
/// Function scan a point in the plane,
/// Used as auxiliary function for createPolygon.
/// </summary>
/// <param>point* p - pointer to p</param>
/// <returns>None</returns>
void scanPoint(point *p)
{
    // your code:
    printf("Entering scanPoint\n");
    printf("Please enter x value: ");
    scanf("%d", &p->x);
    printf("Please enter y value: ");
    scanf("%d", &p->y);
}
// --------------------------- //

/// <summary>
/// Function allocate an empty polygon.
/// </summary>
/// <returns>New allocated polygon</returns>
polygon *createPolygon()
{
    // your code:

    // allocate memory for the polygon
    polygon *poly = (polygon *)malloc(sizeof(polygon));

    // initialize the polygon
    if (poly != NULL)
    {
        poly->n = 0;
        poly->points = NULL;
        poly->scope = 0;
    }

    return poly; // NULL if malloc failed
}
// --------------------------- //

/// <summary>
/// Function calculates distance between 2 adjacent points
/// </summary>
/// <param>point* p1 - pointer to the first point</param>
/// <param>point* p2 - pointer to the second point</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
double distance(point *p1, point *p2)
{
    // your code:

    // declare variables for readability, also to avoid using pow().
    double xdis = p1->x - p2->x,
           ydis = p1->y - p2->y;

    // return the distance
    return sqrt(xdis * xdis + ydis * ydis);
}
// --------------------------- //

/// <summary>
/// Function calculates and returns the Scope of a polygon.
/// </summary>
/// <param>point* points - array of points</param>
/// <param>int n - size of the array</param>
/// <returns>The Scope of a polygon</returns>
double calculateScope(point *points, int n)
{
    // your code:

    int i;
    double scope = 0;

    if (points != NULL && n > 2)
    {
        // iterate over all points and sum the distance between them
        for (i = 0; i < n - 1; i++) 
        {
            scope += distance((points + i), (points + i + 1));
        }

        // add the distance between the last and the first point
        scope += distance((points + i), (points));
    }

    return scope;
}
// --------------------------- //

/// <summary>
/// Function add a new point at the end of the polygon,
/// and update the scope falue.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>1- success, 0- failure</returns>
int addPoint(polygon *poly)
{
    // your code:

    // allocate new memory for the new point
    poly->points = (point *)realloc(poly->points, (poly->n + 1) * sizeof(point));

    // if the allocation was successful
    if (poly->points != NULL)
    {
        scanPoint(poly->points + poly->n);
        poly->n++;
        poly->scope = calculateScope(poly->points, poly->n);
        return 1;
    }

    return 0; // if the allocation failed
}
// --------------------------- //

/// <summary>
/// Function remove a point from the polygon,
/// at spesific index.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <param>int idx - the index to remove</param>
/// <returns>1- success, 0- failure</returns>
int removePoint(polygon *poly, int idx)
{
    // your code:
    
    int i;
    point *temp = NULL;  

    // if index is valid
    if (0 <= idx && idx < poly->n)
    {
        // move all points after the index to the left
        for (i = idx; i < (poly->n - 1); i++)
        {
            poly->points[i] = poly->points[i + 1];
        }

        // reallocate memory for the new size
        temp = (point *)realloc(poly->points, (poly->n - 1) * sizeof(point));

        // if the allocation was successful, should always be true (but just in case ...).
        // ! this also fucks up [points array] if it's false !
        // ? should duplicate the array before moving the points, and not corrupt the original data if the allocation fails ?
        if (temp != NULL)
        {
            poly->points = temp;
            temp = NULL;
            poly->n--;
            poly->scope = calculateScope(poly->points, poly->n);
            return 1;
        }
    }

    return 0; // if the index is invalid
}
// --------------------------- //

/// <summary>
/// Function free alocated memory.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>None</returns>
void freeMemory(polygon *poly)
{
    // your code:

    free(poly->points);
    poly->points = NULL;
    free(poly);
    poly = NULL;
}
// --------------------------- //