/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember the factor n to be mutiplied by
    int n = atoi(argv[1]);
    if (n < 1 || n > 100) {
        printf("The factor must be in the interval [1, 100]\n");
        return 1;
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    bi.biWidth *= n;
    bi.biHeight *= n;
    bi.biSizeImage = (bi.biWidth * 3 + ((4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4)) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) / n) % 4) % 4;
    int out_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight) / n; i < biHeight; i++)
    {
      for (int r = 0; r < n; r++) 
      {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth / n; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile
            for (int k = 0; k < n; k++)
            {    
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }  
        }
        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < out_padding; k++)
        {
            fputc(0x00, outptr);
        }
        fseek(inptr, -(bi.biWidth * 3 / n + in_padding), SEEK_CUR);
      }
        fseek(inptr, (bi.biWidth * 3 / n + in_padding), SEEK_CUR);
    }  

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
