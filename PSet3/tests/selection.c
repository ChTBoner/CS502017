#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
		elements[i] = (drand48() * 100);
		printf("%i ", elements[i]);
	}

		printf("\n\n");

	/*
	 * Sorting with selection sort
	*/
	int minNum, minElem, buffer;
	for (int i = 0; i < len; i++)
	{
		minNum = elements[i];

		for (int j = i; j < len; j++)
		{
			if (minNum > elements[j])
			{
				minNum = elements[j];
				minElem = j;
			}	
		}

		buffer = elements[i];
		elements[i] = minNum;
		elements[minElem] = buffer;
	}

	for (int i = 0; i < len; i++)
	{
		printf("%i ", elements[i]);
	}

	printf("\n");
	return 0;
}