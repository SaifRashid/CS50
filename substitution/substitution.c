#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string cipher = argv[1];

    if (argc != 2)
    {
         printf("Usage: ./substitution key\n");
         return 1;
    }

    if (strlen(cipher) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        if(!isalpha(cipher[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }

    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (cipher[i] == cipher[j])
            {
                printf("Key must not contain duplicate letters.\n");
                return 1;
            }
        }
    }

    string plain_text = get_string("plaintext: ");
    string cipher_text = plain_text;
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    bool upper[strlen(plain_text)];

    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        if (isupper(plain_text[i]))
        {
            upper[i] = true;
        }
        else
        {
            upper[i] = false;
        }
        plain_text[i] = tolower(plain_text[i]);
    }

    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (plain_text[i] == alphabet[j])
            {
                cipher_text[i] = cipher[j];
                if (upper[i])
                {
                    cipher_text[i] = toupper(cipher_text[i]);
                }
                else
                {
                    cipher_text[i] = tolower(cipher_text[i]);
                }
                break;
            }
        }
    }
    printf("ciphertext: %s\n", cipher_text);
}