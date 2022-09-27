#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //平均値を入れる変数
    float heikin;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            heikin = ((float)image[y][x].rgbtRed + (float)image[y][x].rgbtBlue + (float)image[y][x].rgbtGreen) / 3;
            //平均値を丸める
            int gray = round(heikin);
            //それぞれに代入
            image[y][x].rgbtRed = gray;
            image[y][x].rgbtBlue = gray;
            image[y][x].rgbtGreen = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaBlue, sepiaGreen;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            //セピアの計算式に元図いて計算
            sepiaRed = round(.393 * (float)image[y][x].rgbtRed + .769 * (float)image[y][x].rgbtGreen + .189 * (float)image[y][x].rgbtBlue);
            sepiaGreen = round(.349 * (float)image[y][x].rgbtRed + .686 * (float)image[y][x].rgbtGreen + .168 * (float)image[y][x].rgbtBlue);
            sepiaBlue = round(.272 * (float)image[y][x].rgbtRed + .534 * (float)image[y][x].rgbtGreen + .131 * (float)image[y][x].rgbtBlue);
            //255を超えてしまうといけないので、超えた場合は255に
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            //セピア計算したものに置き換え
            image[y][x].rgbtRed = sepiaRed;
            image[y][x].rgbtBlue = sepiaBlue;
            image[y][x].rgbtGreen = sepiaGreen;
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
    float aRed, aBlue, aGreen;
    for (int y = 0; y < height; y++)
    {
        //オリジナルのコピーを取る
        for (int x = 0; x < width; x++)
        {
            temp[y][x].rgbtRed = image[y][x].rgbtRed;
            temp[y][x].rgbtBlue = image[y][x].rgbtBlue;
            temp[y][x].rgbtGreen = image[y][x].rgbtGreen;
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //左上
            if (y == 0 && x == 0)
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y][x + 1].rgbtRed + temp[y + 1][x].rgbtRed + temp[y + 1][x + 1].rgbtRed) / 4);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y][x + 1].rgbtBlue + temp[y + 1][x].rgbtBlue + temp[y + 1][x + 1].rgbtBlue) / 4);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y][x + 1].rgbtGreen + temp[y + 1][x].rgbtGreen + temp[y + 1][x + 1].rgbtGreen) /
                               4);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //左下
            else if (y == (height - 1) && x == 0)
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y - 1][x + 1].rgbtRed + temp[y - 1][x].rgbtRed + temp[y][x + 1].rgbtRed) / 4);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y - 1][x + 1].rgbtBlue + temp[y - 1][x].rgbtBlue + temp[y][x + 1].rgbtBlue) / 4);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y - 1][x + 1].rgbtGreen + temp[y - 1][x].rgbtGreen + temp[y][x + 1].rgbtGreen) /
                               4);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //右上
            else if (y == 0 && x == (width - 1))
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y][x - 1].rgbtRed + temp[y + 1][x - 1].rgbtRed + temp[y + 1][x].rgbtRed) / 4);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y][x - 1].rgbtBlue + temp[y + 1][x - 1].rgbtBlue + temp[y + 1][x].rgbtBlue) / 4);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y][x - 1].rgbtGreen + temp[y + 1][x - 1].rgbtGreen + temp[y + 1][x].rgbtGreen) /
                               4);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //右下
            else if (y == (height - 1) && x == (width - 1))
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y - 1][x - 1].rgbtRed + temp[y - 1][x].rgbtRed + temp[y][x - 1].rgbtRed) / 4);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y - 1][x - 1].rgbtBlue + temp[y - 1][x].rgbtBlue + temp[y][x - 1].rgbtBlue) / 4);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y - 1][x - 1].rgbtGreen + temp[y - 1][x].rgbtGreen + temp[y][x - 1].rgbtGreen) /
                               4);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //左端
            else if ((y > 0 && y < height - 1) && x == 0)
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y - 1][x].rgbtRed + temp[y - 1][x + 1].rgbtRed + temp[y][x +
                                     1].rgbtRed + temp[y + 1][x].rgbtRed + temp[y + 1][x + 1].rgbtRed) / 6);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y - 1][x].rgbtBlue + temp[y - 1][x + 1].rgbtBlue + temp[y][x + 1].rgbtBlue + temp[y
                                      + 1][x].rgbtBlue + temp[y + 1][x + 1].rgbtBlue) / 6);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y - 1][x].rgbtGreen + temp[y - 1][x + 1].rgbtGreen + temp[y][x + 1].rgbtGreen +
                                       temp[y + 1][x].rgbtGreen + temp[y + 1][x + 1].rgbtGreen) / 6);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //右端
            else if ((y > 0 && y < height - 1) && x == (width - 1))
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y - 1][x - 1].rgbtRed + temp[y - 1][x].rgbtRed + temp[y][x - 1].rgbtRed + temp[y +
                                     1][x - 1].rgbtRed + temp[y + 1][x].rgbtRed) / 6);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y - 1][x - 1].rgbtBlue + temp[y - 1][x].rgbtBlue + temp[y][x - 1].rgbtBlue + temp[y
                                      + 1][x - 1].rgbtBlue + temp[y + 1][x].rgbtBlue) / 6);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y - 1][x - 1].rgbtGreen + temp[y - 1][x].rgbtGreen + temp[y][x - 1].rgbtGreen +
                                       temp[y + 1][x - 1].rgbtGreen + temp[y + 1][x].rgbtGreen) / 6);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //上
            else if ((x > 0 && x < width - 1) && y == 0)
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y][x - 1].rgbtRed + temp[y + 1][x - 1].rgbtRed + temp[y][x + 1].rgbtRed + temp[y +
                                     1][x].rgbtRed + temp[y +
                                             1][x + 1].rgbtRed) / 6);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y][x - 1].rgbtBlue + temp[y + 1][x - 1].rgbtBlue + temp[y][x + 1].rgbtBlue + temp[y
                                      + 1][x].rgbtBlue + temp[y + 1][x + 1].rgbtBlue) / 6);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y][x - 1].rgbtGreen + temp[y + 1][x - 1].rgbtGreen + temp[y][x + 1].rgbtGreen +
                                       temp[y + 1][x].rgbtGreen + temp[y + 1][x + 1].rgbtGreen) / 6);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //下
            else if ((x > 0 && x < width - 1) && y == height - 1)
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y][x - 1].rgbtRed + temp[y - 1][x + 1].rgbtRed + temp[y][x + 1].rgbtRed + temp[y -
                                     1][x].rgbtRed + temp[y - 1][x - 1].rgbtRed) / 6);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y][x - 1].rgbtBlue + temp[y - 1][x + 1].rgbtBlue + temp[y][x + 1].rgbtBlue + temp[y
                                      - 1][x].rgbtBlue + temp[y - 1][x - 1].rgbtBlue) / 6);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y][x - 1].rgbtGreen + temp[y - 1][x + 1].rgbtGreen + temp[y][x + 1].rgbtGreen +
                                       temp[y - 1][x].rgbtGreen + temp[y - 1][x - 1].rgbtGreen) / 6);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
            //その他
            else
            {
                aRed = round((float)(temp[y][x].rgbtRed + temp[y - 1][x - 1].rgbtRed + temp[y - 1][x].rgbtRed + temp[y - 1][x + 1].rgbtRed +
                                     temp[y][x - 1].rgbtRed + temp[y][x + 1].rgbtRed + temp[y + 1][x - 1].rgbtRed + temp[y + 1][x].rgbtRed + temp[y + 1][x +
                                             1].rgbtRed) / 9);
                aBlue = round((float)(temp[y][x].rgbtBlue + temp[y - 1][x - 1].rgbtBlue + temp[y - 1][x].rgbtBlue + temp[y - 1][x + 1].rgbtBlue +
                                      temp[y][x - 1].rgbtBlue + temp[y][x + 1].rgbtBlue + temp[y + 1][x - 1].rgbtBlue + temp[y + 1][x].rgbtBlue + temp[y + 1][x +
                                              1].rgbtBlue) / 9);
                aGreen = round((float)(temp[y][x].rgbtGreen + temp[y - 1][x - 1].rgbtGreen + temp[y - 1][x].rgbtGreen + temp[y - 1][x + 1].rgbtGreen
                                       + temp[y][x - 1].rgbtGreen + temp[y][x + 1].rgbtGreen + temp[y + 1][x - 1].rgbtGreen + temp[y + 1][x].rgbtGreen + temp[y + 1][x +
                                               1].rgbtGreen) / 9);

                image[y][x].rgbtRed = aRed;
                image[y][x].rgbtBlue = aBlue;
                image[y][x].rgbtGreen = aGreen;
            }
        }
    }

    return;
}
