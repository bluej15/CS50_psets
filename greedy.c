/** 
* greedy.c
*
* Jessica Perina
* jperina@gmail.com
* 
* This program takes a dollar value input from the user and returns the fewest number of coins
* needed to make that amount in change.
*
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    //declare variable for amount of money
    float amount;
    
    //get input of amount from user and test to ensure it is a non negative number
    do
    {
        printf("How much change is owed?: ");
        amount = GetFloat();
    }
    while (amount <= 0);  
    
    // round the input and convert it from dollars to cents
    amount = round(amount * 100);
    
    // declare variables used to keep track of amount as it decreases and number of coins used
    int n = 0, count = 0;
    
    // use while loops to divide amount by given coin to get count of number of that coin used
    // use modulo to determine remaining amount
    // pass remaining aount to the next while loop
    while ((int)amount >= 25)
    {
        n = ((int)amount / 25);
        count = (count + n);
        amount = ((int)amount % 25);
    }
    
    while (amount >= 10)
    {
        n = (amount / 10);
        count = (count + n);
        amount = ((int)amount % 10);
    }
    
    while (amount >= 5)
    {
        n = (amount / 5);
        count = (count + n);
        amount = ((int)amount % 5);
    }
    
    while (amount >= 1)
    {
        n = (amount / 1);
        count = (count + n);
        amount = ((int)amount % 1);
    }
    
    printf("%d\n", count);
    
    return 0;
}
