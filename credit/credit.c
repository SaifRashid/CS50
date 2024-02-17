#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

long get_card(void);
int get_card_length(long);
string get_company(long, int);
bool card_verify(long, int);

int main(void)
{
    long card = get_card();
    int card_length = get_card_length(card);
    string company = get_company(card, card_length);
    bool real = card_verify(card, card_length);
    if (real && strcmp(company, "INVALID") != 0)
        printf("%s\n", company);
    else
        printf("INVALID\n");
}

long get_card(void)
{
    long card = get_long("What is your credit card number? ");
    return card;
}

int get_card_length(long card)
{
    long card2 = card;
    int card_length = 0;
    for (card_length = 0; card2 > 0; card_length++)
    {
        card2 = card2 / 10;
    }
    return card_length;

}

string get_company(long card, int card_length)
{
    for (int i = 0; i < card_length - 2; i++)
    {
        card = card / 10;
    }
    if (card_length == 15 && (card == 34 || card == 37))
        return "AMEX";
    if (card_length == 16 && (card == 51 || card == 52 || card == 53 || card == 54 || card == 55))
        return "MASTERCARD";
    if ((card_length == 13 || card_length == 16) && card / 10 == 4)
        return "VISA";
    else
        return "INVALID";
}

bool card_verify(long card, int card_length)
{
    long card2 = card;
    long totalx2 = 0;
    int digit;
    int digit2;
    int digit3;
    for (int i = 0; i < card_length / 2; i++)
    {
        card = card / 10;
        digit = card % 10;
        card = card / 10;
        digit *= 2;
        if (digit >= 10)
        {
            digit2 = digit % 10;
            digit3 = digit / 10;
            totalx2 += digit2 + digit3;

        }
        else
            totalx2 += digit;

    }
    int total = totalx2;
    for (int i = 0; i < card_length / 2 + .5; i++)
    {
        digit = card2 % 10;
        card2 = card2 / 100;
        total += digit;
    }
    if (total % 10 == 0)
        return true;
    else
        return false;
}