#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename");
        return 1;
    }

    char *memory_file = argv[1];
    FILE *f = fopen(memory_file, "r");
    if (f == NULL)
    {
        printf("File cannot be accessed");
        return 1;
    }

    unsigned char buffer[512];
    char filename[8];
    int jpg_count = 0;
    sprintf(filename, "%03i.jpg", jpg_count);
    FILE *img = fopen(filename, "w");

    while (fread(buffer, 1, 512, f) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg_count == 0)
            {
                fwrite(buffer, 1, 512, img);
                jpg_count++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpg_count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                jpg_count++;
            }
        }
        else if (jpg_count != 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    fclose(img);
    fclose(f);
}