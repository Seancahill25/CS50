#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int coins = 0;
    float number;
    int change;
    do
    {
        number = get_float("Change owed: ");
        change = round(number * 100);
    }
    while (change <= 0);

    while (change >= 25)
    {
        coins++;
        change = change - 25;
    }
    while (change >= 10)
    {
        coins++;
        change = change - 10;
    }
    while (change >= 5)
    {
        coins++;
        change = change - 5;
    }
    while (change >= 1)
    {
        coins++;
        change = change - 1;
    }
    printf("%i\n", coins);
}

