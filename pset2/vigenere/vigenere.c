//Program works well. Passes all Check50 tests.
//Style50 - Looks good! But consider adding more comments!

//When the User do not enter key, you can be more specific on what the User is missing on line 19 and 28.

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
        for (int letter = 0, k = strlen(key); letter < k; letter++)//checks if key is valid
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

    for (int letter = 0, keyCount = 0; letter < messageLength; letter++)//loop through key and message
    {
        int keyLetter = tolower(key[keyCount % keyLength]) - 'a';//keeps track of where my place in the key is

        if (isalpha(message[letter]))
        {
            if (isupper(message[letter]))
            {
                printf("%c", (((message[letter] - 'A') + keyLetter) % 26) + 'A');
                keyCount++;//only ups the count on my key when used
            }
            else
            {
                printf("%c", (((message[letter] - 'a') + keyLetter) % 26) + 'a');
                keyCount++;
            }
        }
        else
        {
            printf("%c", message[letter]);
        }
    }
    printf("\n");
}



