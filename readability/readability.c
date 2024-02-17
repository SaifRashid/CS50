#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string);
int count_words(string);
int count_sentences(string);

int main(void)
{
    string text = get_string("Text: ");
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);
    //printf("%i letters\n", letter_count);
    //printf("%i words\n", word_count);
    //printf("%i sentences\n", sentence_count);
    int index = 0.0588 * ((double)letter_count/word_count*100) - 0.296 * ((double)sentence_count/word_count*100) - 15.8 + 0.5;
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
}

int count_letters(string text)
{
    int letter_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 65 && text[i] <= 122)
        {
            letter_count += 1;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int word_count = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            word_count += 1;
        }
    }
    return word_count;
}

int count_sentences(string text)
{
    int sentence_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text [i] == 63)
        {
            sentence_count += 1;
        }
    }
    return sentence_count;
}