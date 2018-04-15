/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int factor = atof(argv[1]);

	int paddingOld = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// saving height and width before resize.
	int heightBR = abs(bi.biHeight);
	int widthBR = bi.biWidth;

	// print before factor
	printf("biWidth = %i\n", bi.biWidth);
	printf("biHeight = %i\n", bi.biHeight);
	printf("biSizeImage = %i\n", bi.biSizeImage);
	printf("bf.bfSize = %i\n", bf.bfSize);
	printf("padding = %i\n", paddingOld);

    // change info in headers
    /*
    BITMAPINFOHEADER
    biWidth
    biHeight
    !!biSizeImage !! includes padding!
    bi.biSizeImage = ((siezof(RGBTRIPLE)*bi.biWidth) + padding * abs(bi.biHeight))

    BITMAPFILEHEADER
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
    */
	
	bi.biWidth = bi.biWidth * factor;
	bi.biHeight = bi.biHeight * factor;
	int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biWidth) + padding) * abs(bi.biHeight);
	bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// print after factor
	printf("\nbiWidth = %i\n", bi.biWidth);
	printf("biHeight = %i\n", bi.biHeight);
	printf("biSizeImage = %i\n", bi.biSizeImage);
	printf("bf.bfSize = %i\n", bf.bfSize);
	printf("padding = %i\n", padding);

	// write outfile's BITMAPFILEHEADER
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
	printf("%lu\n", padding + sizeof(RGBTRIPLE)*bi.biWidth);

    // iterate over infile's scanlines
    for (int i = 0; i < heightBR ; i++)
    {
        line[widthBR] = [];
        // iterate over pixels in scanline
        for (int j = 0; j < widthBR; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            line[j] = triple;
            
            // write RGB triple to outfile
            // changed 1 to factor
			for (int m = 0; m < factor; m++)
				fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		
        }

        // skip over padding, if any
        fseek(inptr, paddingOld, SEEK_CUR);

        // then add it back (to demonstrate how)
		for (int k = 0; k < padding; k++)
		{
			fputc(0x00, outptr);
		}
		
		

		//copy line n times
		// move the cursor in outptr to beginning of new line, read the line and write
		/*int *line = NULL;
		line = (int *) malloc(sizeof(BYTE)*padding + sizeof(RGBTRIPLE)*bi.biWidth);
		printf("line = %lu", sizeof(*line));

		fseek(outptr, -(sizeof(BYTE)*padding + sizeof(RGBTRIPLE)*bi.biWidth), SEEK_CUR);
		fread(line, sizeof(BYTE)*padding + sizeof(RGBTRIPLE)*bi.biWidth, 1, outptr);
		printf("line = %i", line);
		for (int m = 0; m < factor-1; m++)
			fwrite(line, sizeof(BYTE)*padding + sizeof(RGBTRIPLE)*bi.biWidth, 1, outptr);

		free(line);
		printf("\n");*/
    }
	

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
