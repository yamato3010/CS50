#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{

    string s = get_string("String: ");

    int code[strlen(s)]; //文字数分のint配列を作成

    for (int i = 0 ; i < strlen(s); i++)
    {
        printf("%i\n", (int)s[i]); //テスト用
        code[i] = (int)s[i];  //配列にint化した文字を一文字ずつ入れていく
    }

    int key = get_int("Key: ");

    //キーの設定
    for (int i = 0; i < strlen(s); i++)
    {
        code[i] += key; //key個分たす
        s[i] = (char)code[i]; //int化したものを文字に戻す
        printf("%i\n", (int)s[i]); //テスト用
    }
    printf("\n");
    for (int i = 0; i < strlen(s); i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}