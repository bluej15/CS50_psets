/** 
* vigenere.c
*
* Jessica Perina
* jperina@gmail.com
* 
* Encyphers text using the vigenere cypher.
*
*/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // make sure two comand line arguments are entered
    if (argc != 2)
    {
        printf("Wrong number of arguments!\n");
        return 1;
    }
    
    // make key the second comand line argument
    // store the length of the key
    string key = argv[1];
    int keylen = strlen(key);
 
    // verify key is a word
    for (int i = 0; i < keylen; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("No numbers!\n");
            return 1;
        }
    }
  
    // get message to be encrypted from user
    string s = GetString();
    
    /*
    * loop through the user input string shifting each character by it's
    * coresponding key character, skipping over non alphabetic characters
    */
    for (int i = 0, j = 0, counter = 0, n = strlen(s); i < n; i++)
        {
            // check if character is alpha, if not, increment counter
            if (!isalpha(s[i]))
            {
                counter++;
            }
            
            // find the [j] character of the key to use
            j = (i - counter) % keylen;
            
            // shift and print the character of the message by the appropriate key character
            if (isupper(s[i]) && isupper(key[j]))
            {
                int result = ((((s[i] - 'A') + (key[j] - 'A')) % 26) + 'A');
                printf("%c", result);
            }
            else if (isupper(s[i]) && islower(key[j]))
            {
                int result = ((((s[i] - 'A') + (key[j] - 'a')) % 26) + 'A');
                printf("%c", result);
            }
            else if (islower(s[i]) && isupper(key[j]))
            {
                int result = ((((s[i] - 'a') + (key[j] - 'A')) % 26) + 'a');
                printf("%c", result);
            }
            else if(islower(s[i]) && islower(key[j]))
            {
                int result = ((((s[i] - 'a') + (key[j] - 'a')) % 26) + 'a');
                printf("%c", result);
            }
            else
            {
                printf("%c", s[i]);
            }
        }
        printf("\n");
    
    return 0;
}
