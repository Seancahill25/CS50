#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // int min = get_int("Minutes: ");
    // int bottles = min * 12;
    printf("Bottles: %i\n", get_int("Minutes: ") * 12);
}