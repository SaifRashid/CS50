#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;

            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;

            int count1 = 0;
            for (int j = -1; j < 2; j++)
            {
                int count2 = 0;
                for (int k = -1; k < 2; k++)
                {
                    if (h + j < 0 || h + j > height - 1 || w + k < 0 || w + k > width - 1)
                    {

                    }
                    else
                    {
                        gx_red += (copy[h+j][w+k].rgbtRed * gx[count1][count2]);
                        gx_green += (copy[h+j][w+k].rgbtGreen * gx[count1][count2]);
                        gx_blue += (copy[h+j][w+k].rgbtBlue * gx[count1][count2]);
                    }
                    count2++;
                }
                count1++;
            }

            count1 = 0;
            for (int j = -1; j < 2; j++)
            {
                int count2 = 0;
                for (int k = -1; k < 2; k++)
                {
                    if (h + j < 0 || h + j > height - 1 || w + k < 0 || w + k > width - 1)
                    {

                    }
                    else
                    {
                        gy_red += (copy[h+j][w+k].rgbtRed * gy[count1][count2]);
                        gy_green += (copy[h+j][w+k].rgbtGreen * gy[count1][count2]);
                        gy_blue += (copy[h+j][w+k].rgbtBlue * gy[count1][count2]);
                    }
                    count2++;
                }
                count1++;
            }
            int final_red = sqrt(gx_red*gx_red + gy_red*gy_red) + .5;
            int final_green = sqrt(gx_green*gx_green + gy_green*gy_green) + .5;
            int final_blue = sqrt(gx_blue*gx_blue + gy_blue*gy_blue) + .5;
            if (final_red > 255)
                final_red = 255;
            if (final_green > 255)
                final_green = 255;
            if (final_blue > 255)
                final_blue = 255;

            image[h][w].rgbtRed = final_red;
            image[h][w].rgbtGreen = final_green;
            image[h][w].rgbtBlue = final_blue;
        }
    }
    return;
}
