#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET 26
#define UPPERCASE_A 65
#define LOWERCASE_A 97
char cipher(char letter, int key)
{
    char crypted;
    if (isupper(letter))
    {
        crypted = ((((letter - UPPERCASE_A) + key) % ALPHABET) + UPPERCASE_A);
    }
    else 
    {
        crypted = ((((letter - LOWERCASE_A) + key) % ALPHABET) + LOWERCASE_A);
    }
    return crypted;
}
int main(int argc, char *argv[]) 
{
    // Before proceding verify that the argument count is 2
    // and that the input the user gives is a number
    if (argc != 2 || !isdigit(*argv[1])) 
    {
        // should either of these conditions be true return 1 and print invalid
        printf("Invalid Input\n");
        return 1;
    }
    // assign the key that was given that's in the argument vector 1 index into keyInput
    // using atoi to convert it from string to an int
    int keyInput = atoi(argv[1]);
    string plainText = get_string("plaintext: "); 
    char cipherText[strlen(plainText)];
    int textLength = strlen(plainText);
    
    for (int letterIndex = 0; letterIndex < textLength; letterIndex++)
    {    
        // if char is in the alphabet proceed to cipher else just  
        // assign the char to cipherText
        if (isalpha(plainText[letterIndex]))
        {
            printf("This is upper: %c\n", plainText[letterIndex]);
            cipherText[letterIndex] = cipher(plainText[letterIndex], keyInput);      
        }
        else 
        {
            printf("This is not alpha char: %c\n", plainText[letterIndex]);
            cipherText[letterIndex] = plainText[letterIndex];
        }     
    }
    printf("ciphertext: %s\n", cipherText);
    return 0;    
}