// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator =  fraction[0];
    int denominator = fraction[2];

    if (denominator == '8')
    {
        printf("%c", numerator * denominator / '8');
    }
    if else (denominator == '4')
    {
        printf("%c", numerator * denominator * '2' / '4')
    }
    if else (denominator == '2')
    {
        printf("%c", numerator * denominator * '4' / '2');
    }
    else (denominator == '1')
    {
        printf("%c", '8');
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s = "")
    {
        return true;
    }
    else
    {
        return false;
    }
}
