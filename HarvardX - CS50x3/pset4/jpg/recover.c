/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCKSIZE 512
#define JPG 4

/* Compare if the buffer read is a JPG file */
int compare(uint8_t buffer[])
{
    uint8_t pattern[] = {0xff, 0xd8, 0xff, 0xe0};
    int i, found;

    for (i = found = 0; i < 4; ++i) {
        if (buffer[i] == pattern[i]) {
            ++found;
        }
        else if (i == 3 && buffer[i] == 0xe1) {
                ++found;
        }
    }    
    return found;
}

int main(int argc, char* argv[])
{
    FILE *card = fopen("card.raw", "r");
    
    if (card == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }
    uint8_t buffer[BLOCKSIZE];
    FILE *outfile = NULL;
    int outname = 0;
    char title[10];

    while (!feof(card)) {   /* Read card untill find its end*/
        if (fread(&buffer, sizeof (uint8_t), BLOCKSIZE, card) < BLOCKSIZE) {   // EOF found the program should abort 
            fclose(card);
            if (outfile != NULL) {
                fclose(outfile);
            }
            return 0;
        }
        if (compare(buffer) == JPG) {
            if (outfile != NULL) {
                fclose(outfile);
            }
            sprintf(title, "%03d.jpg", outname);
            outfile = fopen(title, "w");
            if (outfile == NULL) {
                printf("Could not open the outfile\n");
                printf("Summary: jpgs found -> %d\n", outname);
                return 1;
            }
            fwrite(&buffer[0], BLOCKSIZE * sizeof (uint8_t), 1, outfile);
            ++outname;
        }
        else if (outfile != NULL) {
            fwrite(&buffer[0], BLOCKSIZE * sizeof (uint8_t), 1, outfile);
        }
    }
    fclose(card);
    if (outfile != NULL) {
        fclose(outfile);
    }
    return 0;
}
