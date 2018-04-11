#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key;
    string s;
    if (argc < 2 || argc > 2)
    {
        printf("Try again\n");
        return 1;
    }
    if (argc == 2)
    {
        key = (argv[1]);
        for (int letter = 0, k = strlen(key); letter < k;)
        {
            if (isalpha(key[letter]))
            {
                letter++;
            }
            else
            {
                printf("Try again\n");
                return 1;
            }
        }
        s = get_string("plaintext: ");
    }
}