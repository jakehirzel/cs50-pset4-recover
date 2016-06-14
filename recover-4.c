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
    int test_block_num = 0; // TEST variable for fread and fwrite
    
    // open input file and error check
    card_ptr = fopen("card.raw", "r");
    if (card_ptr == NULL)
    {
        printf("Could not open file.");
        return 2;
    }
 
    // read in first block
    fread(&block_value, sizeof(char), 512, card_ptr);

    // create output_name for output file
    sprintf(output_name, "%03d.jpg", output_counter);
    
    // open output file and error check
    output_ptr = fopen(output_name, "w");
    if (output_ptr == NULL)
    {
        printf("Could not create output file.\n");
        return 3;
    }
    
    // write output file, close, and iterate name
    fwrite(&block_value, sizeof(char), 512, output_ptr);
    fclose(output_ptr);
    output_counter++;
    sprintf(output_name, "%03d.jpg", output_counter);

    // TEST: print block_value
    for (int i = 0; i < sizeof(block_value); i++)
    {
        printf("%x", block_value[i]);
    }
    printf("\n\n");
    
    // open next output file and error check
    output_ptr = fopen(output_name, "w");
    if (output_ptr == NULL)
    {
        printf("Could not create output file.\n");
        return 3;
    }

    // read next block, write next file, close, and iterate
    fread(&block_value, sizeof(char), 512, card_ptr);
    fwrite(&block_value, sizeof(char), 512, output_ptr);
    fclose(output_ptr);
    output_counter++;
    sprintf(output_name, "%03d.jpg", output_counter);

    // TEST: print block_value
    for (int i = 0; i < sizeof(block_value); i++)
    {
        printf("%x", block_value[i]);
    }
    printf("\n\n");

    // open next output file and error check
    output_ptr = fopen(output_name, "w");
    if (output_ptr == NULL)
    {
        printf("Could not create output file.\n");
        return 3;
    }

    // read next block, write next file, close, and iterate
    fread(&block_value, sizeof(char), 512, card_ptr);
    test_block_num = fwrite(&block_value, sizeof(char), 512, output_ptr);
    fclose(output_ptr);
    output_counter++;
    sprintf(output_name, "%03d.jpg", output_counter);
    
    // TEST: print test_block_num
    printf("%i\n", test_block_num);

    // TEST: print block_value
    for (int i = 0; i < sizeof(block_value); i++)
    {
        printf("%x", block_value[i]);
    }
    printf("\n\n");

    // close input file
    fclose(card_ptr);
}

// Every time there is a new jpg, I will make a new file and start writing, just like copy.