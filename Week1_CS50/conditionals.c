#include <cs50.h>
#include <stdio.h>


int main(void)
{
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");
    if (x > y)
    {
        printf("x is larger than y\n");
    }
    else if (x < y)
    {
        printf("Y is larger than x\n");
    }
    else
    {
        printf("x is equal to y\n");
    }
}


int main(void)
{
    char c = get_char("Do you agree? ");

    if (c=='y' || c=='Y')
    {
        printf("Agree.\n");
    }
    else if (c=='n' || c=='N')
    {
        printf("Not agreed.\n");
    }
}