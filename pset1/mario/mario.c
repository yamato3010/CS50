#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        //Get height from user
        height = get_int("height: ");
    }
    while (height > 8 || height < 1);

    //Draw pyramid
    for (int i = 0; i < height; i++)
    {
        //Draw left space
        for (int c = 1; c < height - i; c++)
        {
            printf(" ");
        }
        //Draw left brick
        for (int d = 0; d <= i; d++)
        {
            printf("#");
        }
        //Draw center space
        printf("  ");

        //Draw right brick
        for (int e = 0; e <= i; e++)
        {
            printf("#");
        }

        printf("\n");

    }
}