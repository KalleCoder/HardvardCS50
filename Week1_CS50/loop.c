#include <cs50.h>
#include <stdio.h>


int main(void)
{
    int i = 3;
    while (i > 0)
    {
        printf("meow\n");
        i --;
    }
}

## Even shorter code ###

int main(void)
{
    for (int i = 3; i > 0; i--)
    {
        printf("meow\n");
    }
}


### Forever loop
#include <stdbool-h>

int main(void)
{
    while (true)
    printf("meow\n");
}

### write control + c in terminal to cancel it