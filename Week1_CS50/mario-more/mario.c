#include <cs50.h>
#include <stdio.h>

int get_height(void);
void make_pyramid(int height);

int main(void)
{
    int n = get_height();
    make_pyramid(n);
}


int get_height(void)
{
    int n;
    do
    {
        n = get_int("Set height for pyramid: ");
    }

    while (n <= 0 || n > 8);
    return n;
}
void make_pyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        //Making the spaces before
        int reducing = height - i - 1;
        for (int f = reducing; f >= 0; f--)
        {
            printf(" ");
        }
        //making first bricks
        for (int x = 1; x <= i; x++)
        {
            printf("#");
        }

        //making the space inbetween
        printf("  ");

        //making the second bricks
        for (int y = 1; y <= i; y++)
        {
            printf("#");
        }

        printf("\n");
    }
}