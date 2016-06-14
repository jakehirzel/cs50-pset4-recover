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
    // create file_size variable
    int file_size;
    
    // create output counter and string for image file names
    int output_counter = 1;
    char* output_name = malloc(8);
    sprintf(output_name, "%02d.jpg", output_counter);
    
    // open the file and ascertain and assign length
    FILE* cardptr = fopen("card.raw", "r");
    if (cardptr == NULL)
    {
        printf("Could not open file.");
        return 2;
    }
    else
    {
        fseek(cardptr, 0, SEEK_END);
        file_size = ftell(cardptr);
        rewind(cardptr);
    }
    
    // calculate number of blocks in file
    int file_blocks = file_size / 512;
    
    // set temp variables for current and next block
    char* current_block = malloc(512);
    if (current_block == NULL)
    {
        printf("Insufficient memory available.");
    }
    
    char* next_block = malloc(512);
    if (next_block == NULL)
    {
        printf("Insufficient memory available.");
    }

    // iterate through the file block-by-block
    for (int i = 0; i < file_blocks; i++)
    {
        fread(&current_block, 512, 1, cardptr);
        fread(&next_block, 512, 1, cardptr);
        
        if (current_block[0] == (char)0xff && current_block[1] == (char)0xd8 && current_block[2] == (char)0xff)
        {
            // open output file
            FILE* imageptr = fopen(output_name, "w");
            if (imageptr == NULL)
            {
                fclose(cardptr);
                fprintf(stderr, "Could not create %s.\n", output_name);
                return 3;
            }

            // check for last block and close file, if so
            if (next_block[0] == (char)0xff && next_block[1] == (char)0xd8 && next_block[2] == (char)0xff)
            {
                fwrite(&current_block, 512, 1, imageptr);
                fclose(imageptr);
            }
            
            // otherwise write successive blocks to the file
            else
            {
                 fwrite(&current_block, 512, 1, imageptr);               
            }
        }
    }
    
        
    
    
    
    
    // when found, open a new file (using counter for naming), write consecutive blocks to file, stopping the block before the next jpeg signature is found
    
    // iterate output counter
    
    // free malloc --> output_name, current_block, next_block
}
