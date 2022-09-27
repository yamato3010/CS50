#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int year;

    for (year = 0; start < end; year++)
    {
        int b = 0;
        int d = 0;
        b = start / 3;
        d = start / 4;
        start = start + b - d;
    }

    // TODO: Print number of years
    printf("Years: %i\n", year);
}
