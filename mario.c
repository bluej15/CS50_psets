/** 
* mario.c
*
* Jessica Perina
* jperina@gmail.com
* 
* Prints a half pyramid of hashes based on a user submitted height.
*
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{ 
    //initialize variable
    int h;  
    
    //ask user for height of pyramid
    //continue asking until int is between 1 and 23
    do      
    {
        printf("height:");
        h = GetInt(); 
    }
    while ((h > 23) || (h<0));       
   
    //use height input to increment the number of rows   
    for (int row=0; row < h; row++)  
    {
        //use height to decrement the number of spaces printed
        for (int column=h; column > (row+1); column--) 
        {
            printf(" ");
        }
        //use incremeting row variable to increment the number for hashes printed
        for (int column=0; column <= (row+1); column++) 
        {
            printf("#");
        }
        
        printf("\n");
    }
    return 0;
}
