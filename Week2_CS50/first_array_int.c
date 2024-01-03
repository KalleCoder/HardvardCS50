#include <stdio.h>
#include <cs50.h>

//Global variable and also made constant. IT ALSO must be an integer if you want to use in array --> []
const int N = 3;

// Making it so the function below is loaded first
float average(int array[]);

int main(void)
{
    // Arrays takes less space in an program!!!! I think... but shouldnt
    // how to declare an array, and this one can store 3 integers
    int scores[N];
    // you place the data just as in a list in python
    scores[0] = get_int("Score1: ");
    scores[1] = get_int("Score2: ");
    scores[2] = get_int("Score3: ");
    // the looong way to write it
    printf("Avarage: %f\n", (scores[0] + scores[1] + scores[2]) / (float) 3);

    // __________---------------__________________--------______________________

    // MAKING a more efficient way to do it
    // Instead you can make a for loop for this above
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }
    // and the final thing with a function made below
    printf("Avarage: %f\n", average(N, scores));
}

// Making a function that work depending on the value of Global N
float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float)length;
}
