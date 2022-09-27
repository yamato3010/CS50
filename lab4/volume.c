// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    //アウトプット用ファイルを開く
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    //unit8_tは8ビットの符号なし (すなわち負でない) 整数を格納する型。それをheader_sizeつまり44バイト分確保する
    uint8_t header[HEADER_SIZE];
    
    //HEADER_SIZEつまり44バイトを読み込み、一時的にheaderにおく
    fread(header, HEADER_SIZE, 1, input);
    //headerに置かれたデータをHEADER_SIZEつまり44バイト分書き込む
    fwrite(header, HEADER_SIZE, 1, output);
    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    
    //sizeof(int16_t)のところは読み込むデータ1つのバイト数
    //それを1個ずつ読み込む
    //freadの戻り値は読み込んだデータの個数なので、読み込み終わったら0になり、whileを抜ける
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
