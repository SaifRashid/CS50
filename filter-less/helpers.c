#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE pixel = image[h][w];
            average = (pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0 + .5;
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE pixel = image[h][w];
            int originalRed = pixel.rgbtRed;
            int originalGreen = pixel.rgbtGreen;
            int originalBlue = pixel.rgbtBlue;

            int sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue + .5;
            int sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue + .5;
            int sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue + .5;

            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflect[width];
    int j = width - 1;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            reflect[w] = image[h][w];
        }
        for (int i = 0; i < width; i++)
        {
            image[h][j] = reflect[i];
            j--;
        }
        j = width - 1;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy [height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red_average = 0;
            int green_average = 0;
            int blue_average = 0;
            int average_count = 0;

            for (int j = -1; j < 2; j++)
            {
                for (int k = -1; k < 2; k++)
                {
                    if (h + j < 0 || h + j > height - 1 || w + k < 0 || w + k > width - 1)
                    {
                        continue;
                    }
                    red_average += copy[h+j][w+k].rgbtRed;
                    green_average += copy[h+j][w+k].rgbtGreen;
                    blue_average += copy[h+j][w+k].rgbtBlue;
                    average_count++;

                }
            }
            if (red_average != 0)
                red_average = red_average / (float)average_count +.5;
            if (green_average != 0)
                green_average = green_average / (float)average_count +.5;
            if (blue_average != 0)
                blue_average = blue_average / (float)average_count +.5;
            image[h][w].rgbtRed = red_average;
            image[h][w].rgbtGreen = green_average;
            image[h][w].rgbtBlue = blue_average;
        }

    }
    return;
}
