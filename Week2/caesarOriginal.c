#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char *argv[]) 
{
    // check if more than 2 arguent and if the value in argv1 is not a number
    if (argc != 2 || !isdigit(*argv[1])) 
    {       
        printf("Usage: %s key\n", argv[0]);
        return 1;     
    } 
      
    int key =  atoi(argv[1]); 
    printf("Key is %i\n", key);
    string plainText = get_string("plaintext: ");
    int length = strlen(plainText);
    char cipherText[strlen(plainText) + 1];
   // loop through ciphertext and rotate each letter based on the key input
    for (int k = 0; k < length; k++)
    {    
        // if input is lowercased
        if ((plainText[k] >= 97 && plainText[k] <= 122)) 
        {
          cipherText[k] = (((plainText[k] - 97) + key) % 26) + 97;
           
        }
        else if ((plainText[k] >= 65 && plainText[k] <= 90))
        {
            cipherText[k] = (((plainText[k] - 65) + key) % 26) + 65;
           
            
        }  
        else {
            cipherText[k] = plainText[k];
        }
    }
    
//     scanf("%s\n", cipherText);
//     
    printf("ciphertext: %s\n", cipherText);
    return 0;     
    
}


