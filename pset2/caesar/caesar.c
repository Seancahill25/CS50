#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key = 0;
    string s;
    while(argc == 2)
    {
        key = atoi(argv[1]);
        s = get_string("plaintext: ");
        break;
    }
    printf("ciphertext: ");
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(isalpha(s[i]))
        {
            if(isupper(s[i]))
            {
                char t = (((s[i] - 65) + key) %26) + 65;
                printf("%c", t);
            }
            else
            {
                char t = (((s[i] - 97) + key) %26) + 97;
                printf("%c", t);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}