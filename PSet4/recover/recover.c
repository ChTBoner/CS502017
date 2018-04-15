#include <stdio.h>
#include <stdlib.h>

int main(int argv, char * argc[])
{
    // check for usage
    if (argv != 2)
    {
        printf("Usage : \"./recover card.raw\" \n");
		return 1;
    }
    //set variables
    char *card = argc[1];
    
    // open file
	FILE *input = fopen(card, "r")
	//check if file correctly opened
	if (input == NULL)
	{
		fprintf(stderr, "Could not open file %s.\n", infile);
		return 2
	}

		// start program
		/*
			create new picture
			open as write
			find first byte of picture
			parse until end of picture, write bytebybite
			close the file
		*/


		// close file to empty RAM
		fclose(input);
}