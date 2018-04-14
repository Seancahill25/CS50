#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key = 0;
    string message;
    if (argc == 2)
    {
        key = atoi(argv[1]);
        message = get_string("plaintext: ");
    }
    else
    {
        printf("Try again\n");
        return 1;
    }
    printf("ciphertext: ");
    for (int letter = 0, length = strlen(message); letter < length; letter++)
    {
        if (isalpha(message[letter]))
        {
            if (isupper(message[letter]))
            {
                printf("%c", (((message[letter] - 65) + key) % 26) + 65);
            }
            else
            {
                printf("%c", (((message[letter] - 97) + key) % 26) + 97);
            }
        }
        else
        {
            printf("%c", message[letter]);
        }
    }
    printf("\n");
}