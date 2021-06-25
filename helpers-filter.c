#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            int sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            int sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            if (sepiaRed < 256)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }


            if (sepiaBlue < 256)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }

            if (sepiaGreen < 256)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally                                  !!!!!NÃO DEU CERTO!!!!!
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = width / 2;

    for (int i = 0; i < height; i++) //iterate on rows
    {
        for (int j = 0;  j <middle; j++) //iterate on lines, until the midlle of image
        {
            // alocting the info in a buffer (from the beginning to the middle)
            int bufferRed = image[i][j].rgbtRed;
            int bufferBlue = image[i][j].rgbtBlue;
            int bufferGreen = image[i][j].rgbtGreen;

            // allocating the info on the end in the position in begining
            image[i][width - 1].rgbtRed = image[i][j].rgbtRed;
            image[i][width - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - 1].rgbtGreen = image[i][j].rgbtGreen;

            // allocating the info in the buffer to the end
            image[i][width - 1].rgbtRed = bufferRed;
            image[i][width - 1].rgbtBlue = bufferBlue;
            image[i][width - 1].rgbtGreen = bufferGreen;

        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int limit1 = height - 1;
    int limit2 = width - 1;

    // middle of the image
    for (int i = 1; i < limit1 ; i++)
    {
        for(int j = 1; j < limit2; j++)
        {
            int newRed = (image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed+ image[i+1][j+1].rgbtRed) / 9.0;
            image[i][j].rgbtRed = newRed;

            int newBlue = (image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue+ image[i+1][j+1].rgbtBlue) / 9.0;
            image[i][j].rgbtBlue = newBlue;

            int newGreen = (image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen+ image[i+1][j+1].rgbtGreen) / 9.0;
            image[i][j].rgbtGreen = newGreen;
        }
    }
    //top row
        for(int j = 1; j < limit2; j++)
        {
            int newRed1 = (image[0][j-1].rgbtRed + image[0][j].rgbtRed + image[0][j+1].rgbtRed +image[1][j-1].rgbtRed + image[1][j].rgbtRed + image[1][j+1].rgbtRed) / 6.0;
            image[0][j].rgbtRed = newRed1;

            int newBlue1 = (image[0][j-1].rgbtBlue + image[0][j].rgbtBlue + image[0][j+1].rgbtBlue +image[1][j-1].rgbtBlue + image[1][j].rgbtBlue + image[1][j+1].rgbtBlue) / 6.0;
            image[0][j].rgbtBlue = newBlue1;

            int newGreen1 = (image[0][j-1].rgbtGreen + image[0][j].rgbtGreen + image[0][j+1].rgbtGreen +image[1][j-1].rgbtGreen + image[1][j].rgbtGreen + image[1][j+1].rgbtGreen) / 6.0;
            image[0][j].rgbtGreen = newGreen1;
         }

    //botton row
       for(int j = 1; j < limit2; j++)
        {
            int newRedw = (image[height][j-1].rgbtRed + image[height][j].rgbtRed + image[height][j+1].rgbtRed +image[limit1][j-1].rgbtRed + image[limit1][j].rgbtRed + image[limit1][j+1].rgbtRed) / 6.0;
            image[height][j].rgbtRed = newRedw;

            int newBluew = (image[height][j-1].rgbtBlue + image[height][j].rgbtBlue + image[height][j+1].rgbtBlue +image[limit1][j-1].rgbtBlue + image[limit1][j].rgbtBlue + image[limit1][j+1].rgbtBlue) / 6.0;
            image[height][j].rgbtBlue = newBluew;


            int newGreenw = (image[height][j-1].rgbtGreen + image[height][j].rgbtGreen + image[height][j+1].rgbtGreen +image[limit1][j-1].rgbtGreen + image[limit1][j].rgbtGreen + image[limit1][j+1].rgbtGreen) / 6.0;
            image[height][j].rgbtGreen = newGreenw;
        }

    //first collun
    for(int i = 1; i < limit1; i++)
    {
        int new1Red = (image[i-1][0].rgbtRed + image[i][0].rgbtRed + image[i+1][0].rgbtRed +image[i-1][1].rgbtRed + image[i][1].rgbtRed + image[i+1][1].rgbtRed) / 6.0;
            image[i][0].rgbtRed = new1Red;

        int new1Blue = (image[i-1][0].rgbtBlue + image[i][0].rgbtBlue + image[i+1][0].rgbtBlue +image[i-1][1].rgbtBlue + image[i][1].rgbtBlue + image[i+1][1].rgbtBlue) / 6.0;
            image[i][0].rgbtBlue = new1Blue;

        int new1Green = (image[i-1][0].rgbtGreen + image[i][0].rgbtGreen + image[i+1][0].rgbtGreen +image[i-1][1].rgbtGreen + image[i][1].rgbtGreen + image[i+1][1].rgbtGreen) / 6.0;
            image[i][0].rgbtGreen = new1Green;

    }

    //Last Collun
    for(int i = 1; i < limit1; i++)
    {
        int newwRed = (image[i-1][width].rgbtRed + image[i][width].rgbtRed + image[i+1][width].rgbtRed +image[i-1][limit2].rgbtRed + image[i][limit2].rgbtRed + image[i+1][limit2].rgbtRed) / 6.0;
        image[i][limit2].rgbtRed = newwRed;

        int newwBlue = (image[i-1][width].rgbtBlue + image[i][width].rgbtBlue + image[i+1][width].rgbtBlue +image[i-1][limit2].rgbtBlue + image[i][limit2].rgbtBlue + image[i+1][limit2].rgbtBlue) / 6.0;
        image[i][limit2].rgbtBlue = newwBlue;

        int newwGreen = (image[i-1][width].rgbtGreen + image[i][width].rgbtGreen + image[i+1][width].rgbtGreen +image[i-1][limit2].rgbtGreen + image[i][limit2].rgbtGreen + image[i+1][limit2].rgbtGreen) / 6.0;
        image[i][limit2].rgbtGreen = newwGreen;


    }

    //corners


    return;
}
