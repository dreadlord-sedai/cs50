#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Couldn't open the file\n");
        return 1;
    }

    // Create a buffer to hold each block of data
    uint8_t buffer[512];
    FILE *img = NULL;   // File pointer for the JPEG files
    char filename[8];   // Buffer to hold the filename
    int file_count = 0; // Counter for the number of JPEGs found
    int jpeg_found = 0; // Flag to indicate if a JPEG has been found

    // Read the memory card until the end
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check for the JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already found a JPEG, close the previous file
            if (jpeg_found)
            {
                fclose(img);
            }
            else
            {
                // Set the flag since we found the first JPEG
                jpeg_found = 1;
            }

            // Create a new file for the new JPEG
            sprintf(filename, "%03d.jpg", file_count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Couldn't create output JPEG file %s\n", filename);
                fclose(card);
                return 1;
            }

            file_count++;
        }

        // If a JPEG has been found, write the buffer to the current JPEG file
        if (jpeg_found)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // Close any remaining files
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}
