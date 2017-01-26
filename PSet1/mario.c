#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // asking a number of lines and ask again if conditions not met
    int lines;

    do
    {
        printf("please give me a positive integer under or egal to 23.\n");
        lines = GetInt();
    }
    while(lines < 0 || lines > 23);

    // printing the pyramid

    // currently printed line
    int current = 1;

    while (current <= lines)
    {
        // number of spaces
        int space = lines - current;
        // number of hashes
        int hash = 1;

        // prints the amount of spaces for each line
        while (space > 0)
        {
            printf(" ");
            space--;
        }

        // prints the amount of hashes for each line
        while (hash <= current + 1)
        {
            printf("#");
            hash++;
        }

    	// prints the 2 spaces
    	printf("  ");

    	// prints the second hashes
    	hash = 1;
    	while (hash <= current + 1)
                {
                    printf("#");
                    hash++;
                }
    	// newline
    	printf("\n");
        current++;
     }

}