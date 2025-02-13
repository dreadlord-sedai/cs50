#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Loop over each column in the row
        for (int j = 0; j < width; j++)
        {
            // Get the current pixel
            RGBTRIPLE *pixel = &image[i][j];

            // Calculate the average of the red, green, and blue values
            float average = (pixel->rgbtBlue + pixel->rgbtGreen + pixel->rgbtRed) / 3.0;

            // Round the average to the nearest integer
            BYTE roundedAverage = round(average);

            // Set each color component to the rounded average value
            pixel->rgbtBlue = roundedAverage;
            pixel->rgbtGreen = roundedAverage;
            pixel->rgbtRed = roundedAverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Loop over each column in the row up to the midpoint
        for (int j = 0; j < width / 2; j++)
        {
            // Calculate the index of the pixel to swap with
            int opposite = width - j - 1;

            // Swap the current pixel with the opposite pixel
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][opposite];
            image[i][opposite] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the original image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Loop over each column in the row
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Loop over the surrounding pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Calculate the indices of the neighboring pixel
                    int ni = i + di; // Row index of the neighboring pixel
                    int nj = j + dj; // Column index of the neighboring pixel

                    // Check if neighboring pixel is within the bounds of the image
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += temp[ni][nj].rgbtRed;     // Sum of red values
                        sumGreen += temp[ni][nj].rgbtGreen; // Sum of green values
                        sumBlue += temp[ni][nj].rgbtBlue;   // Sum of blue values

                        count++;
                    }
                }
            }
            // Calculate the average values+
            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel kernels
    int Gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Create a temporary copy of the original image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Loop over each column in the row
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0, Gy_red = 0;
            int Gx_green = 0, Gy_green = 0;
            int Gx_blue = 0, Gy_blue = 0;

            // Loop over the surrounding pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Calculate the indices of the neighboring pixel
                    int ni = i + di; // Row index of the neighboring pixel
                    int nj = j + dj; // Column index of the neighboring pixel

                    // Apply Sobel kernels to compute Gx and Gy for each color channel
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        Gx_red += temp[ni][nj].rgbtRed * Gx_kernel[di + 1][dj + 1];
                        Gy_red += temp[ni][nj].rgbtRed * Gy_kernel[di + 1][dj + 1];

                        Gx_green += temp[ni][nj].rgbtGreen * Gx_kernel[di + 1][dj + 1];
                        Gy_green += temp[ni][nj].rgbtGreen * Gy_kernel[di + 1][dj + 1];

                        Gx_blue += temp[ni][nj].rgbtBlue * Gx_kernel[di + 1][dj + 1];
                        Gy_blue += temp[ni][nj].rgbtBlue * Gy_kernel[di + 1][dj + 1];
                    }
                }
            }

            // Calculate the magnitude of the gradient for each color channel
            int magnitude_red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int magnitude_green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int magnitude_blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Cap the magnitude values at 255
            magnitude_red = (magnitude_red > 255) ? 255 : magnitude_red;
            magnitude_green = (magnitude_green > 255) ? 255 : magnitude_green;
            magnitude_blue = (magnitude_blue > 255) ? 255 : magnitude_blue;

            image[i][j].rgbtRed = magnitude_red;
            image[i][j].rgbtGreen = magnitude_green;
            image[i][j].rgbtBlue = magnitude_blue;
        }
    }
    return;
}
