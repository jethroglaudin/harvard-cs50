#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_positive_float(string prompt);
int main(void)
{
    int quarters = 25;
    int dimes = 10;
    int nickles = 5;
    int pennies = 1;
    int change = get_positive_float("Change Owed: ");
    int cents = round(change * 100);
    int coins = 0;
    
    while (cents >= quarters)
    {
        cents = cents - quarters;
        coins++;
    }
    while (cents >= dimes)
    {
        cents = cents - dimes;
        coins++;
    }
    while (cents >= nickles)
    {
        cents = cents - nickles;
        coins++;
    }
    while (cents >= pennies)
    {
        cents = cents - pennies;
        coins++;
    }
    
    printf("%i\n", coins);
}
float get_positive_float(string prompt)
{
    float n;
    do
    {
        n = get_float("%s", prompt);
    }
    while (n < 0);
    return n;
}

