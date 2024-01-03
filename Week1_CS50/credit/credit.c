#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(void)
{
    long card_number = get_long("Card number: ");
    long first_digit = card_number; //Used for getting the first digit later
    long two_digits = card_number; //Used for getting the two first digits later
    // convert card_number into string and calculate its length
    char card_number_str[20];
    sprintf(card_number_str, "%ld", card_number);
    int card_length = strlen(card_number_str);

    //making necesary variables
    char concactenated_string[20] = "";
    char added_digit_string[20];
    int i;
    int added_uneven = 0;
    // lists the numbers in reverse order
    for (int k = 1; k <= card_length; k++)
    {
        //extrating and calculating the even didigts and making them into a single string
        if (k % 2 == 0)
        {
            int single_digit = card_number % 10;
            card_number /= 10;
            int double_value = (single_digit * 2);
            sprintf(added_digit_string, "%d", double_value);
            for (i = 0; concactenated_string[i] != '\0'; i++);

            for (int j = 0; added_digit_string[j] != '\0'; j++)
            {
                concactenated_string[i] = added_digit_string[j];
                i++;
            }
            concactenated_string[i] = '\0';
        }
        //calculating the uneven digit sum
        else
        {
            int single_digit = card_number % 10;
            card_number /= 10;
            added_uneven += single_digit;
        }
    }
    //printf("After concatenation is done, the new concatenated string will be: %s\n", concactenated_string);

    //Calculating the sum of even digits
    int combined_digits = 0;
    for (int c = 0; concactenated_string[c] != '\0'; c++)
    {
        if (concactenated_string[c] != ' ')// not a white space
        {
            int number_string = concactenated_string[c] - '0';
            combined_digits += number_string;
        }
    }
    //printf("The sum of all even digits is: %i\n", combined_digits);
    //printf("The uneven sum is: %i\n", added_uneven);

    int combined_even_uneven = added_uneven + combined_digits;
    //printf("The total sum is: %i\n", combined_even_uneven);
    //Figureing out the first digit in the number
    while (first_digit >= 10)
    {
        first_digit = first_digit / 10;
    }
    //printf("First digit is: %ld\n", first_digit);

    //Figureing out the two first digits in the number
    while (two_digits >= 100)
    {
        two_digits = two_digits / 10;
    }
    //printf("two digits is: %ld\n", two_digits);

    //Final thing to say witch type of card it is
    if (combined_even_uneven % 10 == 0)
    {
        if (card_length == 15 && first_digit == 3)
        {
            if (two_digits == 34 || two_digits == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }

        }
        else if (card_length == 13 && first_digit == 4)
        {
            printf("VISA\n");
        }
        else if (card_length == 16)
        {
            if (first_digit == 4)
            {
                printf("VISA\n");
            }
            else if (two_digits >= 51 && two_digits <= 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
