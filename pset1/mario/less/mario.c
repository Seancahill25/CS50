#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);

    for (int i = 0; i < n; i++)
    {
//s is for spaces
        for (int s = 0; s < n - i - 1; s++)
        {
            printf(" ");
        }
//h is for hashes
        for (int h = 0; h < i + 2; h++)
        {
            printf("#");
        }

        printf("\n");
    }
}

