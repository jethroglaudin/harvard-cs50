#include <cs50.h>
#include <stdio.h>

int get_height_int(string prompt);
int main(void)
{
    int height = get_height_int("Height: ");
   
    for (int blockHeight = 0; blockHeight < height; blockHeight++)
    {
        for (int spaces = height; spaces > blockHeight; spaces--)
        {
            printf(" ");
        }
        for (int hashes = 0; hashes <= blockHeight; hashes++)
        {
            printf("#");
        }
        printf("\n");
    }
}
int get_height_int(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt); 
    }
    while (n < 1 || n > 8);
    return n;
}


