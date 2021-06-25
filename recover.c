#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Checking command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    //Open memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }


uint8_t buffer[512];// buffer to storage 512 bytes
int count = 0; //count the number of JPEG files
char filename[9];// string to storage the name of the jpeg's files
FILE *img; // declaration of the file to be open with fopen


    while(!feof(file)) //reapet until the end of the card
    {
        fread (buffer, 512 , 1, file); // read 512 bytes into a buffer

        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //if it is the start of a JPEG file ...
        {

            if (!(count == 0)) //If it is the first JPEG file
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", count); //print filename into a string
            img = fopen(filename, "w");//open a new file
            fwrite (buffer, 512, 1 , img);
            count++;

        }
        else // if is not the begining of a JPEG file
        {
            if (count > 0) //it could be the middle of a file that is already open
            {
                 fwrite (buffer, 512, 1, img); //continuing writing on the file
            }
        }
    }
   fclose(img);// Close any remaining files

}
