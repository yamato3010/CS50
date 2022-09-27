#include <cs50.h>
#include <stdio.h>


int main(void)
{
    string s = get_string("Input:  ");
    printf("Output: ");
    for (int i = 0; s[i] != '\0'; i++) // \0 はnull文字
    {
        printf("%c", s[i]);
    }
    printf("\nOutput with ASCII: ");
    for (int i = 0; s[i] != '\0'; i++)
    {
        printf("%i ", (int)s[i]);
    }
    printf("\n");
}

