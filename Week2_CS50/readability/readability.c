#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    string sentence = get_string("Write your sentence: ");
    printf("Your sentence is: %s\n", sentence);
    float amount_letters = 0;
    float amount_words = 0;
    float amount_sentences = 0;
    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        if (isblank(sentence[i]))
        {
            amount_words++;
        }
        if (isalpha(sentence[i]))
        {
            amount_letters++;
        }
        if (sentence[i] == ('.') || sentence[i] == ('!') || sentence[i] == ('?'))
        {
            amount_sentences++;
        }
    }
    printf("amount of Letters: %f\n", amount_letters);
    printf("Amount of words: %f\n", amount_words + 1);
    printf("Amount of sentences: %f\n", amount_sentences);
    float L = (amount_letters / (amount_words+1) * 100);
    float S = (amount_sentences / (amount_words+1)* 100);

    float index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("Grade %f\n", index);
    return 0;
}