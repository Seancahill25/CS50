#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

int duration(string fraction)
{
    int numerator =  fraction[0] - '0';
    int denominator = fraction[2] - '0';

    return numerator * (8 / denominator);
}

int frequency(string note)
{
    double hertz = 440.0;
    int octave = note[strlen(note) - 1] - '0';
    switch (note[0])
    {
        case 'A' :
            break;
        case 'B':
            hertz *= pow(2.0, 2.0 / 12.0);
            break;
        case 'C':
            hertz /= pow(2.0, 9.0 / 12.0);
            break;
        case 'D':
            hertz /= pow(2.0, 7.0 / 12.0);
            break;
        case 'E':
            hertz /= pow(2.0, 5.0 / 12.0);
            break;
        case 'F':
            hertz /= pow(2.0, 4.0 / 12.0);
            break;
        case 'G':
            hertz /= pow(2.0, 2.0 / 12.0);
    }
    if (octave > 4)
    {
        hertz *= pow(2, octave - 4);
    }
    else if (octave < 4)
    {
        hertz /= pow(2, 4 - octave);
    }

    if (note[1] == '#')
    {
        hertz *= pow(2.0, 1.0 / 12.0);
    }
    else if (note[1] == 'b')
    {
        hertz /= pow(2.0, 1.0 / 12.0);
    }
    return round(hertz);
}

bool is_rest(string s)
{
    return strlen(s) == 0;
}
