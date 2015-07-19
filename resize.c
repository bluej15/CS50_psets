/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP by a factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int size = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // check resize amount is a positive int between 1 and 100
    if (size < 1 || size > 100)
    {
        printf("Invalid resize amount. Must be 1 - 100.\n");
        return -1;
    }

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
    BITMAPFILEHEADER bf, bfResize;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfResize = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, biResize;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    biResize = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // update width and height of new header
    biResize.biWidth = bi.biWidth * size;
    biResize.biHeight = bi.biHeight * size;
    
    // determine padding for scanlines in both files
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int resizePadding = (4 - (biResize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update image and file size of new header
    biResize.biSizeImage = (biResize.biWidth * sizeof(RGBTRIPLE) + resizePadding) * abs(biResize.biHeight);
    bfResize.bfSize = bf.bfSize - bi.biSizeImage + biResize.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfResize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResize, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over scanlines to resize vertically
        for (int j = 0; j < size; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile resized by n
                for (int l = 0; l < size; l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // add in new padding
            for (int l = 0; l < resizePadding; l++)
                fputc(0x00, outptr);
                
            // return to the beginning of the scanline (recopy)
            if (j < size - 1)
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
