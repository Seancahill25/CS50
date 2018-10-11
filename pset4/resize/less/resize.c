#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    int resizeValue = atoi(argv[1]);

     if (resizeValue < 1 || resizeValue > 100)
    {
        printf("Factor must be in the range [1-100]\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, resized_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    resized_bf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, resized_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    resized_bi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //makes the new demension for the file
    resized_bi.biWidth = bi.biWidth * resizeValue;
    resized_bi.biHeight = bi.biHeight * resizeValue;

    // determine padding for scanlines of original and new files
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int resized_padding =  (4 - (resized_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //fiqures out new images size
    resized_bf.bfSize = 54 + (resized_bi.biWidth * sizeof(RGBTRIPLE) + resized_padding) * abs(resized_bi.biHeight);
    resized_bi.biSizeImage = resized_bf.bfSize - 54;



    // write outfile's BITMAPFILEHEADER
    fwrite(&resized_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&resized_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //reads scanline based on argument value
        int scanCount = 0;
        while (scanCount < resizeValue)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                //how many times the pixel has been printed
                int pixelCount = 0;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                while (pixelCount < resizeValue)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    pixelCount++;
                }
            }
            //puts in new padding
            for (int newPad = 0; newPad < resized_padding; newPad++)
                fputc(0x00, outptr);

            //restart scanline, unless printing is done
            if (scanCount < (resizeValue - 1))
                fseek(inptr, (-bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
                scanCount++;
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
