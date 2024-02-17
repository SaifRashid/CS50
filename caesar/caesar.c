#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string key = argv[1];
    int k = atoi(key);

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (key[i] < 48 || key[i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    string text = get_string("plaintext:  ");
    bool upper[strlen(text)];
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            if (isupper(text[i]))
            {
                upper[i] = true;
            }
            else
            {
                upper[i] = false;
            }
            text[i] = tolower(text[i]);
            text[i] -= 97;
            text[i] = (text[i] + k) % 26;
            if (upper[i])
            {
                text[i] += 65;
                printf("%c", text[i]);
            }
            else
            {
                text[i] += 97;
                printf("%c", text[i]);
            }
         }
         else
         {
            printf("%c", text[i]);
         }
    }
    printf("\n");
}