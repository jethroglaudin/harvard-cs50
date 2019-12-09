// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    int resize_num = atoi(argv[1]);

    if (!resize_num && !isdigit(resize_num))
    {
        fprintf(stderr, "Invalid Input\n");
        return 2;
    }


    if (resize_num < 0 || resize_num > 100)
    {
        fprintf(stderr, "Number must be betwee 0 - 100\n");
        return 3;
    }
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 4;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 5;
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
        return 6;
    }



    // create outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER new_bf = bf;

    // create outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER  new_bi = bi;

    // original width now will be multipled by the num the user provided
    new_bi.biWidth *= resize_num;

    // original height now will be multiplied by the num the user provided
    new_bi.biHeight *= resize_num;

    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;



    // updating new bi sizeimage
    new_bi.biSizeImage = ((sizeof(RGBTRIPLE) * new_bi.biWidth) + new_padding) * abs(new_bi.biHeight);

    // updating bf size
    new_bf.bfSize = new_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int column = 0, biHeight = abs(bi.biHeight); column < biHeight; column++)
    {
        for (int cursor = 0; cursor < resize_num; cursor++)
        {

            // iterate over pixels in scanline
            for (int pixels = 0; pixels < bi.biWidth; pixels++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int write = 0; write < resize_num; write++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, old_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }

            if (cursor < resize_num - 1)
            {
                fseek(inptr, -((bi.biWidth * sizeof(RGBTRIPLE)) + old_padding), SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
