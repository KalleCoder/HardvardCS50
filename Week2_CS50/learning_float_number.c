#include <stdio.h>

int main(void)
{
    int score1 = 72;
    int score2 = 73;
    int score3 = 33;
    // To fix a float issue you can just change the value to the right to a float
    printf("Avarage: %f\n", (score1 + score2 + score3) / 3.0);
    // or convert into float
    printf("Avarage: %f\n", (score1 + score2 + score3) / (float) 3);
}


