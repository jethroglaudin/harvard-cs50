# Questions

## What's `stdint.h`?

stdint.h is a header file used to define different integer types and macros with size constraints. It allows you to write more portable code by providing typedefs with exact-width interger types. 


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These are signed and unsigned intergers. int meaning signed uint meaning unsigned. We use them to get exact widths. int32_t would be a width of 32 bits. Signed can represent negative values and unsingned represents non-negative values.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 8 bits or 1 byte Data type. unsigned
DWORD: 32 bits or 4 Bytes. Unsigned
LONG: 8 Bytes (64 bits)
WORD: 2 Bytes (16 bits) Unsigned


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII_Header: BM for BitMap
Hexidecimal_Header: 0x424D(which equeats to BM)
6577

## What's the difference between `bfSize` and `biSize`?

bfSize is the total size of the whole bmpfile. 
BiSize is the size of the BITMAPINFOHEADER structure

## What does it mean if `biHeight` is negative?

If biHeight is negative then the image is top down. Beginning in the upper left-hand corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount within the BITMAPINFOHEADER structure determines the color depth. It finds the number of bits for each pixel and the max number of colors in the bitmap.
## Why might `fopen` return `NULL` in `copy.c`?

fopen may return null if it can't open the file or write the file. 

## Why is the third argument to `fread` always `1` in our code?

The third argument to fread is always one because we're reading images 1 pixel at a time. 

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

The value would be 3 I believe. 
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
Would translate to int padding = (4 - (3 * 3) % 4) % 4 
thus padding = 3;

## What does `fseek` do?

fseek is used to move the file pointer. The function goes fssek(file_ptr, offset, position) ;

## What is `SEEK_CUR`?

SEEK_CUR is the current position of the file pointer
