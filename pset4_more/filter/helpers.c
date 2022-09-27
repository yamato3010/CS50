#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float heikin;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

                heikin =  ((float)image[y][x].rgbtRed + (float)image[y][x].rgbtBlue + (float)image[y][x].rgbtGreen) / 3;
                int gray = round(heikin);
                image[y][x].rgbtRed = gray;
                image[y][x].rgbtBlue = gray;
                image[y][x].rgbtGreen = gray;


        }


    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //情報を一時的に保管する変数
    RGBTRIPLE temp[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            //tempに一時的に格納して入れ替える
            temp[y][x] = image[y][x];
            image[y][x] = image[y][width - (x + 1)];
            image[y][width - (x + 1)] = temp[y][x];

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = temp[y][x];
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}