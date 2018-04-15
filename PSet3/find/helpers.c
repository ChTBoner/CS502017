/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
   bool found = false;
   int canMove = true;
   int half = (n - 1) / 2;
   int max = n;
   int min = 0;

   while (found == false && canMove == true)
   {
        
       if ( values[half] == value)
       {
           found = true;
           break;
       }
       else if (min == (max - 1) )
       {
           canMove = false;
           break;
       }
       else if ( values[half] > value)
       {
           // value is smaller
           max = half;
           half = (half + min) / 2;        
       }
       else
       {
           // value is bigger
           min = half;
           half = half + (max - half) / 2;
       }   
   }

    return found;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int buffer;
    for (int i = 1; i < n; i++)
    {
		if (values[i] < values[i-1])
        {
            // looping through previous entries to find right location
			buffer = values[i];
			int half = (i - 1)/ 2;
			bool found = false;
			int max = i;
			int min = 0;

            // finding right location with Binary search
			while (found == false)
			{
                if (values[half] >= values[i] && values[half-1] <= values[i])
				{
					found = true;
				}
				else if (values[half] > values[i])
				{
					max = half;
					half = (half + min ) / 2;
				}
				else
				{
					min = half;
					half = half + (max - half) / 2;
				}
			}

			// replace all other entries
			for (int j = i; j > half; j--)
			{
				values[j] = values[j-1];				
			}

			// place at right position.
			values[half] = buffer;
        }
    }
    return;
}
