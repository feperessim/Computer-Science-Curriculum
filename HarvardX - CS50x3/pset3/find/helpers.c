/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm

    if (n < 0) {
        return false;
    }
    int begin, end, middle;

    begin = 0;
    end = n - 1;
    while (begin <= end) {
        middle = (begin + end) / 2;
        if (value < values[middle]) {
            end = middle - 1;
        }
        else if (value > values[middle]) {
            begin = middle + 1;
        }
        else {
            return true;
        }     
    }
    return false;
}

/**
 * Sorts array of n values.
 */
 void swap(int a, int b);

void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int i, j;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (values[1] > values[i + 1]) {
                    swap(values[i], values[i+1]);
            }
        }
    }    
    return;
}
void swap(int a, int b)
{
    int tmp;

    tmp = b;
    b = a;
    a = tmp;
    return;
}
