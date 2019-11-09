#include <cs50.h>
#include <stdio.h>

int main(void)
{    
    int height;
    // prompt the user to enter height input
    /* should value be less than 1 or greater than 8 re-prompt user for 
     * the height moving on */
    do
    {
        height = get_int("Height: ");   
    } 
    while (height < 1 || height > 8); 
    
     
    // first loop with create the height for our pyramid   
    for (int i = 0; i < height; i++)
    {
        // second loop will align the left hash
        for (int spaces = 0; spaces < height - 1 - i; spaces++)
        {
            printf(" ");
        }
        // print out the left hashes of the pyramid
        for (int leftHashes = 0; leftHashes <= i; leftHashes++)
        {
            printf("#");
        }
        // the gap between the leftside and rightside of the pyramid is the size of two hashes
        // set int gap to two and decrement the value. Should print out two blank spaces
        for (int gap = 2; gap > 0; gap--)
        {
            printf(" ");
        }
        // print right-side hashes
        for (int rightHashes = 0; rightHashes <= i; rightHashes++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}