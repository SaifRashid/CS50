#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string message = get_string("What is your message? ");
    int message_length = strlen(message);
    char letter;
    int bits[8] = {0,0,0,0,0,0,0,0};
    for (int i = 0; i < message_length; i++)
    {
        letter = message[i];
        for (int j = 7; j >= 0; j--)
        {
            if (letter % 2 == 1)
            {
                bits[j] = 1;
            }
            if (letter % 2 == 0)
            {
                bits[j] = 0;
            }
            letter /= 2;
        }

        for (int k = 0; k < 8; k++)
        {
            print_bulb(bits[k]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
