#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Usage ./selection n f [s]\nn = number of elements in list\nf = number to find\ns = seed for randomizing function\n");
	}

	int len = atoi(argv[1]);
	int toFind = atoi(argv[2]);
	int seed = atoi(argv[3]);

	int elements[atoi(argv[1])];

	/*
	 * Initiate the list
	*/

	// initiate srand if provided
	if (argv[3])
	{

		srand48((long) seed);
	}
	else
	{
		srand48((long) time(NULL));
	}

	// generate list with drand
	for (int i = 0; i < len; i++)
	{
		elements[i] = (drand48() * 10000);
		printf("%i ", elements[i]);
	}

		printf("\n\n");

    /*
     * Sorting with insertion sort.
    */
    int buffer;
    for (int i = 1; i < len; i++)
    {
		if (elements[i] < elements[i-1])
        {
            // looping through previous entries to find right location
			buffer = elements[i];
			int half = (i - 1)/ 2;
			bool found = false;
			int max = i;
			int min = 0;

			while (found == false)
			{
				if (elements[half] >= elements[i] && elements[half-1] <= elements[i])
				{
					found = true;
				}
				else if (elements[half] > elements[i])
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
				elements[j] = elements[j-1];				
			}

			// place at right position.
			elements[half] = buffer;
        }

		for (int k = 0; k < len; k++)
		{
			printf("%i ", elements[k]);
		}
		printf("\n");

    }

	printf("\n");
	// checking output
	for (int i = 0; i < len; i++)
	{
		printf("%i ", elements[i]);
	}
	printf("\n");

}