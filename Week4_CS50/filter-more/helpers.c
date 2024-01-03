#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int mean_value = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            image[i][j].rgbtRed = mean_value;
            image[i][j].rgbtGreen = mean_value;
            image[i][j].rgbtBlue = mean_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // making temporary reversed array
    RGBTRIPLE temporary_array[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temporary_array[i][j] = image[i][width -j];
        }
    }

    // configureing original array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temporary_array[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // making the variables
    int centre_red = 0;
    int centre_green = 0;
    int centre_blue = 0;

    int top_red = 0;
    int top_green = 0;
    int top_blue = 0;

    int bottom_red = 0;
    int bottom_green = 0;
    int bottom_blue = 0;

    int left_red = 0;
    int left_green = 0;
    int left_blue = 0;

    int upper_left_corner_red = 0;
    int upper_left_corner_green = 0;
    int upper_left_corner_blue = 0;

    int lower_left_corner_red = 0;
    int lower_left_corner_green = 0;
    int lower_left_corner_blue = 0;

    int right_red = 0;
    int right_green = 0;
    int right_blue = 0;

    int upper_right_corner_red = 0;
    int upper_right_corner_green = 0;
    int upper_right_corner_blue = 0;

    int lower_right_corner_red = 0;
    int lower_right_corner_green = 0;
    int lower_right_corner_blue = 0;

    // making the changes
    RGBTRIPLE temporary_array[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // centre
            centre_red = image[i][j].rgbtRed;
            centre_green = image[i][j].rgbtGreen;
            centre_blue = image[i][j].rgbtBlue;

            // top
            if (i != 0)
            {
                top_red = image[i - 1][j].rgbtRed;
                top_green = image[i - 1][j].rgbtGreen;
                top_blue = image[i - 1][j].rgbtBlue;
            }

            //bottom
            if (i != height-1)
            {
                bottom_red = image[i + 1][j].rgbtRed;
                bottom_green = image[i + 1][j].rgbtGreen;
                bottom_blue = image[i + 1][j].rgbtBlue;
            }

            // left side
            if (j != 0)
            {
                left_red = image[i][j - 1].rgbtRed;
                left_green = image[i][j - 1].rgbtGreen;
                left_blue = image[i][j - 1].rgbtBlue;
            }

            // upper left corner
            if (j != 0 && i != 0)
            {
                upper_left_corner_red = image[i - 1][j - 1].rgbtRed;
                upper_left_corner_green = image[i - 1][j - 1].rgbtGreen;
                upper_left_corner_blue = image[i - 1][j - 1].rgbtBlue;
            }

            // lower left corner ------
            if (j != 0 && i != height-1)
            {
                lower_left_corner_red = image[i + 1][j - 1].rgbtRed;
                lower_left_corner_green = image[i + 1][j - 1].rgbtGreen;
                lower_left_corner_blue = image[i + 1][j - 1].rgbtBlue;
            }

            // right side --------
            if (j != width-1)
            {
                right_red = image[i][j + 1].rgbtRed;
                right_green = image[i][j + 1].rgbtGreen;
                right_blue = image[i][j + 1].rgbtBlue;
            }

            // upper right corner
            if (j != width-1 && i != 0)
            {
                upper_right_corner_red = image[i - 1][j + 1].rgbtRed;
                upper_right_corner_green = image[i - 1][j + 1].rgbtGreen;
                upper_right_corner_blue = image[i - 1][j + 1].rgbtBlue;
            }

            // lower right corner
            if (j != width-1 && i != height-1)
            {
                lower_right_corner_red = image[i + 1][j + 1].rgbtRed;
                lower_right_corner_green = image[i + 1][j + 1].rgbtGreen;
                lower_right_corner_blue = image[i + 1][j + 1].rgbtBlue;
            }

            // Doing the calculations!!!!!!!!!!!!!!

            if (j == width-1 && i == height-1) // bottom right corner
            {
                int average_red = round((centre_red+top_red+upper_left_corner_red+left_red)/4);
                int average_green = round((centre_green+top_green+upper_left_corner_green+left_green)/4);
                int average_blue = round((centre_blue+top_blue+upper_left_corner_blue+left_blue)/4);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (j == 0 && i == height-1) // bottom left corner
            {
                int average_red = round((centre_red+top_red+upper_right_corner_red+right_red)/4);
                int average_green = round((centre_green+top_green+upper_right_corner_green+right_green)/4);
                int average_blue = round((centre_blue+top_blue+upper_right_corner_blue+right_blue)/4);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (j == 0 && i == 0) //top left corner
            {
                int average_red = round((centre_red+right_red+bottom_red+lower_right_corner_red)/4);
                int average_green = round((centre_green+right_green+bottom_green+lower_right_corner_green)/4);
                int average_blue = round((centre_blue+right_blue+bottom_blue+lower_right_corner_blue)/4);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (j == width-1 && i == 0) // top right corner
            {
                int average_red = round((centre_red+left_red+lower_left_corner_red+bottom_red)/4);
                int average_green = round((centre_green+left_green+lower_left_corner_green+bottom_green)/4);
                int average_blue = round((centre_blue+left_blue+lower_left_corner_blue+bottom_blue)/4);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (j == width-1 && i != 0 && i != height-1) // right wall
            {
                int average_red = round((centre_red+top_red+upper_left_corner_red+lower_left_corner_red+left_red+bottom_red)/6);
                int average_green = round((centre_green+top_green+upper_left_corner_green+lower_left_corner_green+left_green+bottom_green)/6);
                int average_blue = round((centre_blue+top_blue+upper_left_corner_blue+lower_left_corner_blue+left_blue+bottom_blue)/6);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (j == 0 && i != 0 && i != height-1) // left wall
            {
                int average_red = round((centre_red+top_red+upper_right_corner_red+right_red+lower_right_corner_red+bottom_red)/6);
                int average_green = round((centre_green+top_green+upper_right_corner_green+right_green+lower_right_corner_green+bottom_green)/6);
                int average_blue = round((centre_blue+top_blue+upper_right_corner_blue+right_blue+lower_right_corner_blue+bottom_blue)/6);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (i == 0 && j != 0 && j != width-1) // top wall
            {
                int average_red = round((centre_red+bottom_red+lower_right_corner_red+lower_left_corner_red+right_red+left_red)/6);
                int average_green = round((centre_green+bottom_green+lower_right_corner_green+lower_left_corner_green+right_green+left_green)/6);
                int average_blue = round((centre_blue+bottom_blue+lower_right_corner_blue+lower_left_corner_blue+right_blue+left_blue)/6);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (i == height-1 && j != 0 && j != width-1) // bottom wall
            {
                int average_red = round((centre_red+top_red+upper_right_corner_red+upper_left_corner_red+right_red+left_red)/6);
                int average_green = round((centre_green+top_green+upper_right_corner_green+upper_left_corner_green+right_green+left_green)/6);
                int average_blue = round((centre_blue+top_blue+upper_right_corner_blue+upper_left_corner_blue+right_blue+left_blue)/6);

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
            else if (i != 0)
            {
                int average_red = round(centre_red+top_red+bottom_red+left_red+upper_left_corner_red+lower_left_corner_red+right_red+upper_right_corner_red+lower_right_corner_red)/9;
                int average_green = round(centre_green+top_green+bottom_green+left_green+upper_left_corner_green+lower_left_corner_green+right_green+upper_right_corner_green+lower_right_corner_green)/9;
                int average_blue = round(centre_blue+top_blue+bottom_blue+left_blue+upper_left_corner_blue+lower_left_corner_blue+right_blue+upper_right_corner_blue+lower_right_corner_blue)/9;

                temporary_array[i][j].rgbtRed = average_red;
                temporary_array[i][j].rgbtGreen = average_green;
                temporary_array[i][j].rgbtBlue = average_blue;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temporary_array[i][j].rgbtRed;
            image[i][j].rgbtGreen = temporary_array[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temporary_array[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // making the variables
    int centre_red = 0;
    int centre_green = 0;
    int centre_blue = 0;

    int top_red = 0;
    int top_green = 0;
    int top_blue = 0;

    int bottom_red = 0;
    int bottom_green = 0;
    int bottom_blue = 0;

    int left_red = 0;
    int left_green = 0;
    int left_blue = 0;

    int upper_left_corner_red = 0;
    int upper_left_corner_green = 0;
    int upper_left_corner_blue = 0;

    int lower_left_corner_red = 0;
    int lower_left_corner_green = 0;
    int lower_left_corner_blue = 0;

    int right_red = 0;
    int right_green = 0;
    int right_blue = 0;

    int upper_right_corner_red = 0;
    int upper_right_corner_green = 0;
    int upper_right_corner_blue = 0;

    int lower_right_corner_red = 0;
    int lower_right_corner_green = 0;
    int lower_right_corner_blue = 0;

    float x_red = 0;
    float y_red = 0;
    float x_green = 0;
    float y_green = 0;
    float x_blue = 0;
    float y_blue = 0;

    // making the changes
    RGBTRIPLE temporary_array[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // centre
            centre_red = image[i][j].rgbtRed;
            centre_green = image[i][j].rgbtGreen;
            centre_blue = image[i][j].rgbtBlue;

            // top
            if (i != 0)
            {
                top_red = image[i - 1][j].rgbtRed;
                top_green = image[i - 1][j].rgbtGreen;
                top_blue = image[i - 1][j].rgbtBlue;
            }


            // bottom
            if (i != height - 1)
            {
                bottom_red = image[i + 1][j].rgbtRed;
                bottom_green = image[i + 1][j].rgbtGreen;
                bottom_blue = image[i + 1][j].rgbtBlue;
            }

            // left side
            if (j != 0)
            {
                left_red = image[i][j - 1].rgbtRed;
                left_green = image[i][j - 1].rgbtGreen;
                left_blue = image[i][j - 1].rgbtBlue;
            }

            // upper left corner
            if (j != 0 && i != 0)
            {
                upper_left_corner_red = image[i - 1][j - 1].rgbtRed;
                upper_left_corner_green = image[i - 1][j - 1].rgbtGreen;
                upper_left_corner_blue = image[i - 1][j - 1].rgbtBlue;
            }

            // lower left corner
            if (j != 0 && i != height - 1)
            {
                lower_left_corner_red = image[i + 1][j - 1].rgbtRed;
                lower_left_corner_green = image[i + 1][j - 1].rgbtGreen;
                lower_left_corner_blue = image[i + 1][j - 1].rgbtBlue;
            }

            // right side
            if (j != width - 1)
            {
                right_red = image[i][j + 1].rgbtRed;
                right_green = image[i][j + 1].rgbtGreen;
                right_blue = image[i][j + 1].rgbtBlue;
            }

            // upper right corner
            if (j != width - 1 && i != 0)
            {
                upper_right_corner_red = image[i - 1][j + 1].rgbtRed;
                upper_right_corner_green = image[i - 1][j + 1].rgbtGreen;
                upper_right_corner_blue = image[i - 1][j + 1].rgbtBlue;
            }

            // lower right corner
            if (j != width - 1 && i != height - 1)
            {
                lower_right_corner_red = image[i + 1][j + 1].rgbtRed;
                lower_right_corner_green = image[i + 1][j + 1].rgbtGreen;
                lower_right_corner_blue = image[i + 1][j + 1].rgbtBlue;
            }

            // Doing the calculations!!!!!!!!!!!!!!

            if (j == width - 1 && i == height - 1) // bottom right corner
            {

                // X
                x_red = -2*(left_red) + -1*(upper_left_corner_red) + 0 * top_red + 0 * centre_red;
                x_green = -2*(left_green) + -1*(upper_left_corner_green) + 0 * top_green + 0 * centre_green;
                x_blue = -2*(left_blue) + -1*(upper_left_corner_blue) + 0 * top_blue + 0 * centre_blue;

                // Y
                y_red = 0 *left_red + -1*(upper_left_corner_red) + -2*(top_red) + 0 * centre_red;
                y_green = 0 * left_green + -1*(upper_left_corner_green) + -2*(top_green) + 0 * centre_green;
                y_blue = 0 * left_blue + -1*(upper_left_corner_blue) + -2*(top_blue) + 0 * centre_blue;
            }
            else if (j == 0 && i == height - 1) // bottom left corner
            {
                // X
                x_red = 0 * top_red + 0 * centre_red +
                        1 * upper_right_corner_red + 2 * right_red;

                x_green = 0 * top_green +
                          0 * centre_green + 1 * upper_right_corner_green + 2 * right_green;

                x_blue = 0 * top_blue +
                         0 * centre_blue+ 1 * upper_right_corner_blue + 2 * right_blue;
                // Y
                y_red = -2 * top_red + 0 * centre_red +
                        -1 * upper_right_corner_red + 0 * right_red;

                y_green = -2 * top_green +
                          0 * centre_green + 2 * bottom_green + -1 * upper_right_corner_green + 0 * right_green;

                y_blue = -2 * top_blue +
                         0 * centre_blue + 2 * bottom_blue + -1 * upper_right_corner_blue + 0 * right_blue;
            }
            else if (j == 0 && i == 0) // top left corner
            {
                // X
                x_red = 0 * centre_red +
                        0 * bottom_red + 2 * right_red + 1 * lower_right_corner_red;

                x_green = 0 * centre_green + 0 * bottom_green + 2 * right_green + 1 * lower_right_corner_green;

                x_blue = 0 * centre_blue + 0 * bottom_blue + 2 * right_blue +
                         1 * lower_right_corner_blue;
                // Y
                y_red = 0 * centre_red +
                        2 * bottom_red + 0 * right_red + 1 * lower_right_corner_red;

                y_green = 0 * centre_green + 2 * bottom_green + 0 * right_green +
                          1 * lower_right_corner_green;

                y_blue = 0 * centre_blue + 2 * bottom_blue + 0 * right_blue +
                         1 * lower_right_corner_blue;
            }
            else if (j == width - 1 && i == 0) // top right corner
            {
                // X
                x_red =  -2 * left_red + -1 * lower_left_corner_red + 0 * centre_red +
                        0 * bottom_red + 1 * upper_right_corner_red + 2 * right_red + 1 * lower_right_corner_red;

                x_green = -2 * left_green + -1 * lower_left_corner_green +
                          0 * centre_green + 0 * bottom_green;

                x_blue = -2 * left_blue + -1 * lower_left_corner_blue  +
                         0 * centre_blue + 0 * bottom_blue;
                // Y
                y_red = 0 * left_red + 1 * lower_left_corner_red  + 0 * centre_red +
                        2 * bottom_red;

                y_green = 0 * left_green + 1 * lower_left_corner_green  +
                          0 * centre_green + 2 * bottom_green;

                y_blue = 0 * left_blue + 1 * lower_left_corner_blue +
                         0 * centre_blue + 2 * bottom_blue;
             }
             else if (j == width && i != 0 && i != height - 1) // right wall
             {
                // X
                x_red = -1 * upper_left_corner_red + -2 * left_red + -1 * lower_left_corner_red + 0 * top_red + 0 * centre_red +
                        0 * bottom_red;

                x_green = -1 * upper_left_corner_green + -2 * left_green + -1 * lower_left_corner_green + 0 * top_green +
                          0 * centre_green + 0 * bottom_green;

                x_blue = -1 * upper_left_corner_blue + -2 * left_blue + -1 * lower_left_corner_blue + 0 * top_blue +
                         0 * centre_blue + 0 * bottom_blue;
                // Y
                y_red = -1 * upper_left_corner_red + 0 * left_red + 1 * lower_left_corner_red + -2 * top_red + 0 * centre_red +
                        2 * bottom_red;

                y_green = -1 * upper_left_corner_green + 0 * left_green + 1 * lower_left_corner_green + -2 * top_green +
                          0 * centre_green + 2 * bottom_green;

                y_blue = -1 * upper_left_corner_blue + 0 * left_blue + 1 * lower_left_corner_blue + -2 * top_blue +
                         0 * centre_blue + 2 * bottom_blue;
            }
            else if (j == 0) // left wall
            {

                if (i != 0 && i != height - 1)
                {
                    // X
                    x_red = 0 * top_red + 0 * centre_red + 0 * bottom_red + 1 * upper_right_corner_red + 2 * right_red +
                            1 * lower_right_corner_red;

                    x_green = 0 * top_green + 0 * centre_green + 0 * bottom_green + 1 * upper_right_corner_green + 2 * right_green +
                              1 * lower_right_corner_green;

                    x_blue = 0 * top_blue + 0 * centre_blue + 0 * bottom_blue + 1 * upper_right_corner_blue + 2 * right_blue +
                             1 * lower_right_corner_blue;
                    // Y
                    y_red = -2 * top_red + 0 * centre_red + 2 * bottom_red + -1 * upper_right_corner_red + 0 * right_red +
                            1 * lower_right_corner_red;

                    y_green = -2 * top_green + 0 * centre_green + 2 * bottom_green + -1 * upper_right_corner_green +
                              0 * right_green + 1 * lower_right_corner_green;

                    y_blue = -2 * top_blue + 0 * centre_blue + 2 * bottom_blue + -1 * upper_right_corner_blue + 0 * right_blue +
                             1 * lower_right_corner_blue;
                }

            }
            else if (i == 0 && j != 0 && j != width - 1) // top wall
            {
                // X
                x_red = -2 * left_red + -1 * lower_left_corner_red + 0 * centre_red +
                        0 * bottom_red + 2 * right_red + 1 * lower_right_corner_red;

                x_green = -2 * left_green + -1 * lower_left_corner_green +
                          0 * centre_green + 0 * bottom_green + 2 * right_green +
                          1 * lower_right_corner_green;

                x_blue = -2 * left_blue + -1 * lower_left_corner_blue  +
                         0 * centre_blue + 0 * bottom_blue + 2 * right_blue +
                         1 * lower_right_corner_blue;
                // Y
                y_red = 0 * left_red + 1 * lower_left_corner_red  + 0 * centre_red +
                        2 * bottom_red + 0 * right_red + 1 * lower_right_corner_red;

                y_green = 0 * left_green + 1 * lower_left_corner_green +
                          0 * centre_green + 2 * bottom_green + 0 * right_green +
                          1 * lower_right_corner_green;

                y_blue = 0 * left_blue + 1 * lower_left_corner_blue +
                         0 * centre_blue + 2 * bottom_blue+ 0 * right_blue +
                         1 * lower_right_corner_blue;
            }
            else if (i == height - 1 && j != 0 && j != width - 1) // bottom wall
            {
                //X
                x_red = -1 * upper_left_corner_red + -2 * left_red +  0 * top_red + 0 * centre_red + 1 * upper_right_corner_red + 2 * right_red;

                x_green = -1 * upper_left_corner_green + -2 * left_green + 0 * top_green +
                          0 * centre_green + 1 * upper_right_corner_green + 2 * right_green;

                x_blue = -1 * upper_left_corner_blue + -2 * left_blue  + 0 * top_blue +
                         0 * centre_blue  + 1 * upper_right_corner_blue + 2 * right_blue;
                // Y
                y_red = -1 * upper_left_corner_red + 0 * left_red + -2 * top_red + 0 * centre_red + -1 * upper_right_corner_red + 0 * right_red;

                y_green = -1 * upper_left_corner_green + 0 * left_green + -2 * top_green +
                          0 * centre_green + -1 * upper_right_corner_green + 0 * right_green;

                y_blue = -1 * upper_left_corner_blue + 0 * left_blue + -2 * top_blue +
                         0 * centre_blue + -1 * upper_right_corner_blue + 0 * right_blue;
            }
            else if (i != 0) // normal spots
            {
                // X
                x_red = -1 * upper_left_corner_red + -2 * left_red + -1 * lower_left_corner_red + 0 * top_red + 0 * centre_red +
                              0 * bottom_red + 1 * upper_right_corner_red + 2 * right_red + 1 * lower_right_corner_red;

                x_green = -1 * upper_left_corner_green + -2 * left_green + -1 * lower_left_corner_green + 0 * top_green +
                                0 * centre_green + 0 * bottom_green + 1 * upper_right_corner_green + 2 * right_green +
                                1 * lower_right_corner_green;

                x_blue = -1 * upper_left_corner_blue + -2 * left_blue + -1 * lower_left_corner_blue + 0 * top_blue + 0 * centre_blue +
                               0 * bottom_blue + 1 * upper_right_corner_blue + 2 * right_blue + 1 * lower_right_corner_blue;
                // Y
                y_red = -1 * upper_left_corner_red + 0 * left_red + 1 * lower_left_corner_red + -2 * top_red + 0 * centre_red +
                              2 * bottom_red + -1 * upper_right_corner_red + 0 * right_red + 1 * lower_right_corner_red;

                y_green = -1 * upper_left_corner_green + 0 * left_green + 1 * lower_left_corner_green + -2 * top_green +
                                0 * centre_green + 2 * bottom_green + -1 * upper_right_corner_green + 0 * right_green +
                                1 * lower_right_corner_green;

                y_blue = -1 * upper_left_corner_blue + 0 * left_blue + 1 * lower_left_corner_blue + -2 * top_blue + 0 * centre_blue +
                               2 * bottom_blue + -1 * upper_right_corner_blue + 0 * right_blue + 1 * lower_right_corner_blue;
            }

            // final calculations and moving to temporary array
            int red = round(sqrt((x_red * x_red) + (y_red * y_red)));
            int green = round(sqrt((x_green * x_green) + (y_green * y_green)));
            int blue = round(sqrt((x_blue * x_blue) + (y_blue * y_blue)));

            if (red > 255 || green > 255 || blue > 255)
            {
                if (red > 255)
                {
                    temporary_array[i][j].rgbtRed = 255;
                    temporary_array[i][j].rgbtGreen = green;
                    temporary_array[i][j].rgbtBlue = blue;
                }
                else if (green > 255)
                {
                    temporary_array[i][j].rgbtRed = red;
                    temporary_array[i][j].rgbtGreen = 255;
                    temporary_array[i][j].rgbtBlue = blue;
                }
                else if (blue > 255)
                {
                    temporary_array[i][j].rgbtRed = red;
                    temporary_array[i][j].rgbtGreen = green;
                    temporary_array[i][j].rgbtBlue = 255;
                }
            }
            else
            {
                temporary_array[i][j].rgbtRed = red;
                temporary_array[i][j].rgbtGreen = green;
                temporary_array[i][j].rgbtBlue = blue;
            }
        }
    }

    // copying over the new values to image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temporary_array[i][j].rgbtRed;
            image[i][j].rgbtGreen = temporary_array[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temporary_array[i][j].rgbtBlue;
        }
    }

    return;
}
