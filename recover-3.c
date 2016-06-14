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

    // create block_value buffer, output_counter, and output_open toggle
    char block_value[512] = {0};
    int output_counter = 0;
    char* output_name[7] = {0};
    int output_open = 0;

    // open input file and error check
    FILE* card_ptr = fopen("card.raw", "r");
    if (card_ptr == NULL)
    {
        printf("Could not open file.");
        return 2;
    }
    
    // create output_name for output file
    sprintf(output_name, "%03d.jpg", output_counter);
    
    // open output file and error check
    FILE* output_ptr = fopen(output_name, "w");
    if (output_ptr == NULL)
    {
        printf("Could not create output file.\n");
        return 3;
    }

    // address situations where there is no file being written
    while (output_open == 0)
    {
        // read a block
        fread(&block_value, 512, 1, card_ptr);
        
        // a new jpg? open and write, change file_open, and move on
        if (block_value[0] == (char)0xff && block_value[1] == (char)0xd8 && block_value[2] == (char)0xff)
        {
            
            // write the block if you can, and toggle output_open
            fwrite(&block_value, 512, 1, output_ptr);
            output_open = 1;
        }
    }

    // address situations where there is a file write in progress
    while (output_open == 1)
    {
        // a new jpg? close current, open new, write, and move on
        if (block_value[0] == (char)0xff && block_value[1] == (char)0xd8 && block_value[2] == (char)0xff)
        {
            // close current file
            fclose(output_ptr);
            
            // iterate output_counter
            output_counter ++;
            
            // open new file and error check
            output_ptr = fopen(output_name, "w");
            if (output_ptr == NULL)
            {
                printf("Could not create output file.\n");
                return 3;
            }
            
            // write the block
            fwrite(&block_value, 512, 1, output_ptr);
        }

        // not a new jpg? write and move on
        else if (block_value[0] != (char)0xff && block_value[1] != (char)0xd8 && block_value[2] != (char)0xff)
        {
            fwrite(&block_value, 512, 1, output_ptr);
        }
    }
    

// CLEAN UP BELOW HERE
    
    
//    sprintf(output_name, "%02d.jpg", output_counter);

/*
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
*/

    // iterate output counter
    
    // free malloc --> output_name, current_block, next_block

// TODO: what if there's nothing ever written to output?

// TODO: sweep notes

}

/*

create buffer array
open memory card file
initialize jpeg image pointer
initialize string for image title
initialize image counter
if memory card can be opened:
    loop until end of card
        fread card file into buffer
        if new jpeg header is found:
            close image file if any were opened
            sprintf
            open new image file
            fwrite into image file
            increment image counter
        else if there is an image file opened:
            fwrite into image file
if memory card can't be opened:
    print statement saying can't open
    return 1
close memory card file
return 0

*/