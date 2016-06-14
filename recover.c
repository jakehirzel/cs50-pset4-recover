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

int main(void)
{
    // set up variables
    FILE* card_ptr; // input file
    FILE* output_ptr; // output file
    unsigned char block_value[512] = {0}; // buffer for block values
    int output_counter = 0; // numbers for output file names
    char output_name[8] = {0}; // string for output file names
    char output_toggle = 0; // track whether an output file is open or not

    // open input file and error check
    card_ptr = fopen("card.raw", "r");
    if (card_ptr == NULL)
    {
        printf("Could not open file.");
        return 2;
    }
 
    // loop through all full blocks in file
    while (fread(&block_value, sizeof(char), 512, card_ptr) == 512)
    {
        // start new files whenever a jpg signature is found
        if (block_value[0] == (unsigned char)0xff && block_value[1] == (unsigned char)0xd8 && block_value[2] == (unsigned char)0xff)
        {
            // close any open output files
            if (output_toggle == 1)
            {
                fclose(output_ptr);
            }
            
            // create output_name for output file
            sprintf(output_name, "%03d.jpg", output_counter);
            
            // open output file and error check
            output_ptr = fopen(output_name, "w");
            if (output_ptr == NULL)
            {
                printf("Could not create output file.\n");
                return 3;
            }
            
            // write output file, iterate name counter, toggle output_toggle
            fwrite(&block_value, sizeof(char), 512, output_ptr);
            output_counter++;
            output_toggle = 1;
        }
        else if (output_toggle == 1)
        {
            // write the block to the open file
            fwrite(&block_value, sizeof(char), 512, output_ptr);
        }
    }
    
    // close input file
    fclose(card_ptr);
}