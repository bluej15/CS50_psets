/** 
* caesar.c
*
* Jessica Perina
* jperina@gmail.com
* 
* Encyphers text using the caesar cypher.
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
    
    // make key the second comand line argument, convert to int and test if valid
    int key = atoi(argv[1]); 
    if (key != 0)
    {
        /* get string to be encyphered from user
        *  loop through the characters of the string checking for case
        *  and apply appropriate algorithm based on result
        *  if charcter is not alpha print it */
        string s = GetString();
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            if (isupper(s[i]))
            {
                int result = ((((s[i] - 'A') + key) % 26)+ 'A');
                printf("%c", result);
            }
            else if (islower(s[i]))
            {
                int result = ((((s[i] - 'a') + key) % 26)+ 'a');
                printf("%c", result);
            }
            else
            {
                printf("%c", s[i]);
            }
        }
        printf("\n");
    }
    else
    {
        // if key is not valid yell at user and quit
        printf("Use a number!\n");
        return 1;
    }
    
    return 0;
}
