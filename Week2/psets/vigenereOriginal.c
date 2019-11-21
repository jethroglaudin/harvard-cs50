#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int shift(char c);
int main(int argc, char *argv[]) 
{   
    
    if (!argv[1])
    {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }
  
  for (int a = 0, b = strlen(argv[1]); a < b; a++)
    {
        if ((argc != 2) || !isalpha(argv[1][a]))
        {
            printf("Usage: %s\n", argv[0]);
            return 1;  
        }
    }
         
    string plainText = get_string("plaintext: ");
    
    int j = 0;
    
    char cipherText[strlen(plainText)];
    char *keyword = argv[1];
    int keywordLength = strlen(argv[1]);
    int key = shift(argv[1][j]);
    int length = strlen(plainText);
        
    for (int i = 0; i <= strlen(plainText); i++)
    {
        // check to see if current character within plaintext is alphabetic
        if (isalpha(plainText[i]))
        {
            key = shift(argv[1][j % strlen(keyword)]);
            // check to see if character is lowercased 
            if (plainText[i] >= 97 && plainText[i] <= 122)
            {
                
                cipherText[i] = (((plainText[i] - 97) + key) % 26) + 97;
                j++;
                 
            }
            // check to see if character is uppercased 
            else if ((plainText[i] >= 65 && plainText[i] <= 90)) 
            {
              
                cipherText[i] = (((plainText[i] - 65) + key) % 26) + 65;
                j++;             
            }             
        }  
        else
        {
            cipherText[i] = plainText[i];       
        } 
             
        printf("ciphertext %i: %c\n", i, cipherText[i]);
           
    }
              
    printf("ciphertext: %s\n", cipherText);
    return 0;         

//      // convert char to int based on position value
//      // A or a would be 0 and Z or z would be 25    
}

// define value for the alphabet characters inputted
// so A-a would be 0 and Z-z would be 25
int shift(char c)
{
    if (c >= 65 && c <= 90 && isalpha(c))
    {
        return c - 65 ;  
    } 
    else if (c >= 97 && c <= 122 && isalpha(c))
    {
        return c - 97; 
    } 
    else 
    {
        return 2; 
    }
}
