#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //もしコマンド引数がなかったら
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //ファイルを開く
    FILE *f = fopen(argv[1], "r");
    //ファイルが開けなかったら
    if (f == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    //jpegファイルを区切るためのカウンタ
    int jpeg_counter = 0;
    //ポインタをNULLで初期化
    FILE *pointer = NULL;
    BYTE buffer[512];

    while (fread(&buffer, 512, 1, f))
    {
        //もしjpegファイルの特徴と一致したら
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //もしjpegファイルを書き込む処理が終わっていたら閉じる
            if (jpeg_counter != 0)
            {
                fclose(pointer);
            }

            char file_name[8];

            sprintf(file_name, "%03i.jpg", jpeg_counter);
            pointer = fopen(file_name, "w");
            jpeg_counter++;
        }

        if (jpeg_counter != 0)
        {
            fwrite(&buffer, 512, 1, pointer);
        }
    }

    fclose(pointer);
    fclose(f);

}