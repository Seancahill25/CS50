#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    // This while loop can use a comment
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);

    for (int i = 0; i < n; i++)
    {
        // I think you should indent comments to match the line it refers to
//s is for spaces
        // instead of having a comment that declares s is for spaces, try using space as the variable name, that way the code comments itself
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

