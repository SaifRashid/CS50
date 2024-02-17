#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./ reverse input.wav output.wav");
        return 1;
    }

    // Open input file for reading
    // TODO #2]
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
        return 1;

    // Read header
    // TODO #3
    WAVHEADER jotaro;
    fread(&jotaro.chunkID, 4, 1, input);
    fread(&jotaro.chunkSize, 4, 1, input);
    fread(&jotaro.format, 4, 1, input);
    fread(&jotaro.subchunk1ID, 4, 1, input);
    fread(&jotaro.subchunk1Size, 4, 1, input);
    fread(&jotaro.audioFormat, 2, 1, input);
    fread(&jotaro.numChannels, 2, 1, input);
    fread(&jotaro.sampleRate, 4, 1, input);
    fread(&jotaro.blockAlign, 2, 1, input);
    fread(&jotaro.bitsPerSample, 2, 1, input);
    fread(&jotaro.subchunk2ID, 4, 1, input);
    fread(&jotaro.subchunk2Size, 4, 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(jotaro))
    {
        printf("Not a valid .wav file");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");

    // Write header to file
    // TODO #6
    fwrite(&jotaro.chunkID, 4, 1, output);
    fwrite(&jotaro.chunkSize, 4, 1, output);
    fwrite(&jotaro.format, 4, 1, output);
    fwrite(&jotaro.subchunk1ID, 4, 1, output);
    fwrite(&jotaro.subchunk1Size, 4, 1, output);
    fwrite(&jotaro.audioFormat, 2, 1, output);
    fwrite(&jotaro.numChannels, 2, 1, output);
    fwrite(&jotaro.sampleRate, 4, 1, output);
    fwrite(&jotaro.blockAlign, 2, 1, output);
    fwrite(&jotaro.bitsPerSample, 2, 1, output);
    fwrite(&jotaro.subchunk2ID, 4, 1, output);
    fwrite(&jotaro.subchunk2Size, 4, 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(jotaro);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];
    if (fseek(input, 0, SEEK_END) != 0)
    {
        return 1;
    }
    while (ftell(input) > 44)
    {
        fread(&buffer, 1, block_size, input);
        fwrite(&buffer, 1, block_size, output);
        fseek(input, -block_size, SEEK_CUR);
    }
    fclose(input);
    fclose(output);

    }

int check_format(WAVHEADER header)
{
    // TODO #4
    char *wave = "WAVE";
    for (int i = 0; i < 4; i++)
    {
        if (!(header.format[i] == wave[i]))
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);

}