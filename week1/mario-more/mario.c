#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompting for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Pyramid creation
    for (int i = 0; i < height; i++)
    {
        // Print Leading Spaces
        for (int ls = 0; ls < height - i - 1; ls++)
        {
            printf(" ");
        }

        // Print left Hashes
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }

        // Print middle Spaces
        printf("  ");

        // Print Right Hashes
        for (int r = 0; r < i + 1; r++)
        {
            printf("#");
        }

        // Move to the next line after each row
        printf("\n");
    }
}
