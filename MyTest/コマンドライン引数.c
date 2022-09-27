#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[]) //argc は引数の数 argv[0] が./コマンドライン引数 argv[1]がそのあとに書いたやつ
{
    if (argc == 2) //引数が2の時（./コマンドライン引数 の後ろに何か打った時）
    {
        printf("hello, %s\n", argv[1]);
    }
    else
    {
        printf("hello, world\n");
    }
}