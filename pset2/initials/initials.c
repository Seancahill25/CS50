//Program works well. But check50 throws error because
//the expected output do not have "name:  " but the actual output prints "name: ".
//For example: expected "HLJ\n", not "name: HLJ\n"

//line 21 - i++ after printf is not required

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("name: ");
    printf("%c", toupper(s[0]));
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ' && s[i + 1] != '\0')
        {
            printf("%c", toupper(s[i + 1]));
            i++;
        }
    }
    printf("\n");
}