// Copies a BMP file
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    // if argc counter does not equal 4
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    // char *c = argv[1];
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // check if n is indeed an interger and null

    if (!n && !isdigit(n))
    {
        printf("Invalid! \n");
        return 2;
    }

    // check if n is between 0 and 100
    if (n < 0 || n > 100)
    {
        printf("Number must be between 0 - 100");
        return 3;
    }

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
        return 5;
    }

    // store a new instance of the BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER n_bf = bf;
    BITMAPINFOHEADER n_bi = bi;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    // new width being times by the n input
    //  bi.biWidth = bi.biWidth * n;
    n_bi.biWidth *= n;
    // new height being times by the n input
    //  out_bi = bi.biHeight *n;
    n_bi.biHeight *= n;
    //getting padding of the new scaled outfile
    int new_padding = (4 - (n_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // placing new biSizeImage for output file
    n_bi.biSizeImage = ((sizeof(RGBTRIPLE) * n_bi.biWidth) + new_padding) * abs(n_bi.biHeight);
    // placing new bfsize for output file
    // equation is bfsize = the infoheader's size image plus the size of both the new bitmapfileheader and bitmapinfoheader
    n_bf.bfSize = n_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&n_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&n_bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // vertical loop based on the height of the original height
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        // loop keeps track of cursor
        for (int j = 0; j < n; j++)
        {
            // horizontal loop based on the width of the original width
            for (int k = 0, biWidth = bi.biWidth; k < biWidth; k++)
            {
                //tempary storage triple
                RGBTRIPLE triple;

                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // writes the pixels n times
                for (int l = 0; l < n;  l++)
                {
                    // write RGB triple
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over original padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add in new padding
            for (int m = 0; m < new_padding; m++)
            {
                // add padding
                fputc(0x00, outptr);
            }
            if (j < n - 1)
            {
                // move the cursor back backwards
                // negative value of the total amount in bytes to move backwards
                fseek(inptr, -((bi.biWidth * sizeof(RGBTRIPLE)) + padding), SEEK_CUR);
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
