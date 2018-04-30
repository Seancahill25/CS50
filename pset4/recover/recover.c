#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }

    char* infile = argv[1];
    const int block = 512;

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[block];

    FILE *outptr = NULL;

    char filename[7];

    int images = 0;

    while(fread(buffer, block, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&  (buffer[3] & 0xf0) == 0xe0)
        {
                if (images > 0)
                {
                    fclose(outptr);
                }
                sprintf(filename, "%03i.jpg", images);

                outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    fprintf(stderr, "Could not create image");
                    return 3;
                }
                images++;
        }
        if (outptr != NULL)
        {
            fwrite(buffer, block, 1, outptr);
        }
    }
    fclose(outptr);
    fclose(inptr);
    return 0;
}
