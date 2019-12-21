#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Invalid input. Please insert memory card");
        return 1;
    }

    // once memory card is input store it
    char *memory_card = argv[1];

    // open memory card with mode set to "r" for READ
    FILE *inptr = fopen(memory_card, "r");

    if(inptr == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", memory_card);
        return 2;
    }
    // Create array called buffer that can store 512 bytes
    BYTE buffer[512];

    char filename[8];

    // keep track of count of jpegs found
    int count = 0;

    FILE *img = NULL;

    bool new_jpeg_header = false;

    while(fread(&buffer, sizeof(buffer), 1, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // until we find our first jpeg header img will remain close
            if(new_jpeg_header == true)
            {
               fclose(img);
            }

            else
            {
                new_jpeg_header = true;
            }

            sprintf(filename, "%03i.jpg", count);
            // open image
            img = fopen(filename, "w");
            count++;
        }
        if(new_jpeg_header)
        {
            fwrite(&buffer, sizeof(buffer), 1, img);
        }

    }
    fclose(img);
    fclose(inptr);
    return 0;

}
