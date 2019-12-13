#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    // store infile
    char *infile = argv[1];

    //open input file and set mode to read
    FILE *inptr = fopen(infile, "r");


    // check to make sure input file is not NULL
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", infile);
        return 2;
    }

    BYTE buffer[512];
    // this is for storing the file's name
    // this will include the number of the file 001, 002 etc..
    // then the period jpg (.jpg) thus 001.jpg;
    char filename[8];

    // count number for how many jpegs images found.
    // this will be addd to the front of title
    int count = 0;

    FILE *img = NULL;

    bool newJpeg = false;

    while (fread(&buffer, 512, 1, inptr))
    {

        // check header to see if header is that of the jpeg format
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)

        {
            // if there was previously a jpeg file being written we must close it before we begin writing the new jpeg file
            if (newJpeg == true)
            {
                // close the img file
                fclose(img);
            }
            else
            {
                // if not we'll set newJpeg to true meaning this is indeed a new header
                newJpeg = true;
            }

            // if that passes then we've found a jpeg
            // increment the count

            //create filename for the new jpeg
            sprintf(filename, "%03i.jpg", count);
            // open that new jpeg file
            img = fopen(filename, "w");
            count++;
        }

        if (newJpeg == true)
        {
            fwrite(&buffer, 512, 1, img);
        }

    }
    // close last file
    fclose(img);
    // close input file
    fclose(inptr);
    return 0;

}
