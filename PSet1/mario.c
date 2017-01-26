#include <stdio.h>
#include <cs50.h>

int main()
{
    int num = -1;
    while (num < 0 || num > 23)
    {
        printf("Please pick an integer between 1 and 23 : ");
        num = GetInt();
    };

    for (int i = 0 ; i < num ; i++)
    {
        for (int j = 0; j < num-i-1; j++)
        {
            printf(" ");
        }

        for (int k = 0; k < i+1; k++)
        {
            printf("#");
        }

        printf("  ");

        for (int k = 0; k < i+1; k++)
        {
        	printf("#");
        }
        printf("\n");
    }
}