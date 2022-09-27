#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_key(string key);

int main(int argc, string
         argv[]) //argc は引数の数 argv[0] が./コマンドライン引数 argv[1]がそのあとに書いたやつ
{
    if (argc == 2) //引数が2の時（./コマンドライン引数 の後ろに何か打った時）
    {
        if (strlen(argv[1]) == 26)
        {
            string key = argv[1]; //./substitution の後ろのキー
            if (check_key(key) == false)
            {
                printf("Key must only contain alphabetic characters and must not contain repeated characters.\n");
                return (1);
            }
            
            
            string plainText = get_string("plaintext: "); //入力された文字
            string org_u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            string org_l = "abcdefghijklmnopqrstuvwxyz";
            int u_num, l_num;

            printf("ciphertext: ");

            for (int i = 0, j = strlen(plainText); i < j; i++)
            {
                char moji = (char)plainText[i]; //plaintextを一文字ずつとる
                for (int k = 0; k < 26; k++)
                {
                    if (isupper(moji) && moji == org_u[k]) //入力された文字が大文字で、org_uの番号と一致したら
                    {

                        key[k] = toupper(key[k]);
                        printf("%c", key[k]);

                    }
                    else if (islower(moji) && moji == org_l[k]) //入力された文字が小文字で、org_uの番号と一致したら
                    {

                        key[k] = tolower(key[k]);
                        printf("%c", key[k]);

                    }


                }
                if (moji == 44 || moji == 46 || moji == 32)
                {
                    printf("%c", moji);
                }
                else if (moji >= 48 && moji <= 57)
                {
                    printf("%c", moji);
                }
            }
            printf("\n");




        }
        else
        {
            //KEYが26文字でない時
            printf("Key must contain 26 characters.");
            return (1);
        }
    }
    else if (argc > 2)
    {   
        //引数を渡しすぎたとき
        printf("Usage: ./substitution key\n");
        return (1);
    }
    else
    {
        //何も引数を渡さなかったとき
        printf("Usage: ./substitution key\n");
        return (1);
    }
}

bool check_key(string key)
{
    int match = 0;
    //a-zまでループ
    for (char c = 'a'; c <= 'z'; c++)
    {
        for (int i = 0; i < 26; i++)
        {
            //小文字に変換してcと一致したらmatchをふやす
            if (tolower(key[i]) == c)
            {
                match++;
                break;
            }
        }
    }
    //matchが26なら正常なのでtrueで返す
    if (match == 26)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}