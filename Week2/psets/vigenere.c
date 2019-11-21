#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET 26
#define UPPERCASE_A 65
#define LOWERCASE_A 97
int shift(char c)
{   
    // initalize char letter as null / '\0'
    char letter = '\0';
    if (isupper(c))
    {
        letter = c - UPPERCASE_A; 
    }
    else if (islower(c))
    {
        letter = c - LOWERCASE_A;
    }
    return letter;
}
int main(int argc, char *argv[]) 
{   
    if (argc != 2 || !argv[1])
    {
        printf("Invalid Input: Must Insert Key\n");
        return 1;
    }
    
    // loop through the argument vector to make sure each char is not a number
    for (int a = 0, b = strlen(argv[1]); a < b; a++)
    {
        if (isdigit(argv[1][a]))
        {
            printf("Invalid Input: Key cannot contain numbers\n");
            return 1;
        }
    }
    string keyword = argv[1];
    string plainText = get_string("plaintext: ");
    char cipherText[strlen(plainText) + 1];
    int textLength = strlen(plainText);
    int textIndex = 0;
    
    
    for (int charIndex = 0; charIndex <= textLength; charIndex++)
    {
        if (isalpha(plainText[charIndex]))
        {
            int key = shift(argv[1][textIndex % strlen(keyword)]);
            if (isupper(plainText[charIndex]))
            {
                cipherText[charIndex] = ((((plainText[charIndex] - UPPERCASE_A) + key) % ALPHABET) + UPPERCASE_A);
                textIndex++;
//                 printf("cipherText currently: %c\n", cipherText[charIndex]);
                
            }
            else if (islower(plainText[charIndex]))
            {
                cipherText[charIndex] = ((((plainText[charIndex] - LOWERCASE_A) + key) % ALPHABET) + LOWERCASE_A);
                textIndex++;
//                 printf("cipherText currently: %c\n", cipherText[charIndex]);        
            }
        }
        else 
        {
//             printf("cipherText currently: %c\n", cipherText[charIndex]);
            cipherText[charIndex] = plainText[charIndex];
        }
//         printf("cipherText currently: %c\n", cipherText[charIndex]);
    }
    
    printf("ciphertext: %s\n", cipherText);
    return 0;
}

