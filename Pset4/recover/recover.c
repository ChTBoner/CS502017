#include <stdio.h>
#include <stdlib.h>

int main(int argv, char * argc[])
{
    // check for usage
    if (argv != 2)
    {
        printf("Usage : \"./recover card.raw\" \n");
        return 2
    }
    //set variables
    char *card = argc[1];
    
    // open file
    FILE *input = fopen(card, "r")
    //chek if file correctly opened
    
    // start program
    /*
        create new picture
        open as write
        parse until end of picture, write bytebybite
        close the file
    */
    

    // close file to empty RAM
    fclose(input)
}