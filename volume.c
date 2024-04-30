// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    uint8_t header[HEADER_SIZE];

    int16_t buffer;
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    fread(&header, sizeof(uint8_t), 44, input);
    fwrite(&header, sizeof(uint8_t), 44, output);

    // Prints out header buffer as test...
    for(int i=0; i < HEADER_SIZE+1; i++)
    {
        printf("%u", header[i]);
    }

    // Read samples from input file and write updated data to output file
   while (feof(input) != true)
   { 
    fread(&buffer, sizeof(buffer),1, input);
    buffer *= factor;
    fwrite(&buffer, sizeof(buffer), 1, output);
   }
	


    // Close files
    fclose(input);
    fclose(output);
}

