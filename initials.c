/** 
* initials.c
*
* Jessica Perina
* jperina@gmail.com
* 
* Take the input of a name and returns the capitilized initials of that name.
*
*/

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // prompt user to input their name and store as a string
    string name = GetString();
    
    // test to ensure string is usable and not NULL
    if (name != NULL)
    {
        // capitilize (if needed) and print the first letter of the string
        printf("%c", toupper(name[0]));
        
        // itterate through string and when a space is found capitilize and print the following letter
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            // cast 32 as a char to get the space character
            if (name[i] == (char) 32)
            {
                printf("%c", toupper(name[i+1]));
            }
        }
        
        printf("\n");
    }
    return 0;
}
