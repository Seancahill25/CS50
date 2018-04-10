#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // These "comments" are just just unused code. Try making comments that help describe what the code is doing.
    // int min = get_int("Minutes: ");
    // int bottles = min * 12;
    // I personally like how you got everything in one line, but I think this actually makes it more difficult to read.
    printf("Bottles: %i\n", get_int("Minutes: ") * 12);
}

