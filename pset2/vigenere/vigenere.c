#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = (argv[1]);
    string message;

    if (argc != 2)
    {
        printf("Try again\n");
        return 1;
    }
    else
    {
        for (int letter = 0, k = strlen(key); letter < k; letter++)
        {
            if (!isalpha(key[letter]))
            {
                printf("Try again\n");
                return 1;
            }
        }
        message = get_string("plaintext: ");
    }

    printf("ciphertext: ");
    int messageLength = strlen(message);
    int keyLength = strlen(key);

    for (int letter = 0, kLetter = 0; letter < messageLength; letter++)
    {
        int keyLetter = tolower(key[kLetter % keyLength]) - 97;

        if (isalpha(message[letter]))
        {
            if (isupper(message[letter]))
            {
                printf("%c", (((message[letter] - 65) + keyLetter) % 26) + 65);
                kLetter++;
            }
            else
            {
                printf("%c", (((message[letter] - 97) + keyLetter) % 26) + 97);
                kLetter++;
            }
        }
        else
        {
            printf("%c", message[letter]);
        }
    }
    printf("\n");
}



