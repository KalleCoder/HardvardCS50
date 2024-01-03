#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // string key_upper = "YTNSHKVEFXRBAUQZCLWDMIPGJO";
    string key_upper = get_string("Type in your key: ");
    //string key_lower = "ytnshkvefxrbauqzclwdmipgjo";
    char key_lower[26];
    bool correct_key = true;
    int n;
    while (correct_key)
    {
        for (n = 0; n < 26; n++)
        {
            if (isblank(key_upper[n]) || isdigit(key_upper[n]) || islower(key_upper[n]) || ispunct(key_upper[n]))
            {
                printf("No spaces, symbols or lower case letters!\n");
                break;
                return 1;
            }
            else
            {
                key_lower[n] = tolower(key_upper[n]);
            }
        }
        correct_key = false;
    }
    
    string alphabet_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alphabet_lower = "abcdefghijklmnopqrstuvwxyz";


    if (n == 26)
    {
        string word = get_string("Write what you want to code: ");
        char letter_switch[strlen(word)];
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < strlen(word); j++)
            {
                if (word[j] == alphabet_upper[i])
                {
                    letter_switch[j] = key_upper[i];
                }
                else if (alphabet_lower[i] == word[j])
                {
                    letter_switch[j] = key_lower[i];
                }
                else if (word[j] == '!' || word[j] == '.' || word[j] == ',' || word[j] == ' ')
                {
                    letter_switch[j] = word[j];
                }
            }
        }

        for (int k = 0; k < strlen(word); k++)
        {
            printf("%c", letter_switch[k]);
        }
        printf("\n");
    }
        return 0;
}