#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE; // following the hint on the website

int main(int argc, char *argv[])
{

    // open card.raw file
    FILE *f = fopen(argv[1], "r");


    //making variables
    BYTE buffer[512]; // storing the bytes
    int file_nr = 0; // for the names and knowing when to close the img files and such.
    int itterations = 0;
    char filename[8]; // I thought was the size of the img file.... But yeah is name size!
    FILE *img = NULL; // for making the jpg


    // repeat until end of card
    while (fread(&buffer, 1, 512, f) == 512) // read 512 bytes into a buffer until the end of the memory card
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // finding the start if a jpeg
        {
            printf("%d\n", itterations); // me testing if the if statement worked.
            itterations++;

            if (file_nr > 0) // stop writing to first jpeg and writing to a new one
            {
                fclose(img);
            }

            // filename
            sprintf(filename, "%03i.jpg", file_nr);
            file_nr++;

            // open the jpeg file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                break;
            }
            // write information onto it.
            fwrite(buffer, 1, sizeof(buffer), img);

        }
        else  // if you are on a new byte size and already have found a jpeg. (continuing writing).
        {
            if (file_nr > 0)
            {
                fwrite(buffer, 1, sizeof(buffer), img);
            }
        }
    }

    fclose(img);
    fclose(f);

    return 0;
}