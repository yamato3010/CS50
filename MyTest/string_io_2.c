#include <cs50.h>
#include <stdio.h>
#include <string.h> //strlenを使うのに必須

int main(void)
{
    string s = get_string("Input:  ");
    printf("Output: ");
    for (int i = 0; i < strlen(s); i++) //ここでstrlenを使っている 「文字列の長さ」回繰り返すループ
    {
        printf("%c", s[i]);
    }
    printf("\n");
}
