#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // ask for number of elements
    int num;
    printf("How many elements need to be sorted : ");
    scanf("%i", &num);
    
    // generating elements
    int elements[num];
    
    for (int i = 0; i < num; i++)
    {
        elements[i] = rand() % 100 ;
        printf("%i ", elements[i]);
    }
    printf("\n\n");
    
    int swap = -1;
    
    // sorting elements
    do
    {
        swap = 0;
        for (int i = 0 ; i < num - 1 ; i++)
        {
            if (elements[i] > elements[i+1])
            {
                int buffer = elements[i];
                // printf("i = %i | element = %i | element+1 = %i | buffer = %i\n", i, elements[i], elements[i+1], buffer);
                elements[i] = elements[i+1];
                elements[i+1] = buffer;
                swap += 1;
                
            }
        }
        // printf("swap = %i\n", swap);
    }
    while (swap > 0);
    
    // print results
    for (int i = 0; i < num; i++)
    {
        printf("%i ", elements[i]);
    }
    
    printf("\n");
    
    // start searching
    int found = 0;
    int canMove = 1;
    int half = (num - 1) / 2;
    int toFind;
    int max = num;
    int min = 0;
    
    printf("What number do you want to find : ");
    scanf("%i", &toFind);
    
    while (found == 0 && canMove == 1)
    {
        
        // printf("scanned: %i - half: %i - min: %i - max: %i\n", elements[half], half, min, max);
        
        if (elements[half] == toFind)
        {
            found = 1;
            break;
        }
        else if (min == (max - 1) )
        {
            canMove = 0;
            break;
        }
        else if (elements[half] > toFind)
        {
            // toFind is smaller
            max = half;
            half = (half + min) / 2;
            
        }
        else
        {
            // to find is bigger
            min = half;
            half = half + (max - half) / 2;
        }
        
    }
    
    if (found == 1)
        printf("found!!\n");
    else printf("not found!!\n");
}