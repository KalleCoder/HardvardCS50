#include <stdio.h>
#include <cs50.h>

//Dont need to have functions in the top, just write the "title" first
int get_size(void);
void make_grid(int size);

int main(void)
{
    // get size of grid using a do while loop
    int n = get_size();
    // make grid
    make_grid(n);
}



int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1);
    return n;
}

void make_grid(int size)
{
    for (int i = 0; i < size; i ++)
    {
        for (int x = 0; x < size; x ++)
        {
            printf("#");
        }
        printf("\n");
    }
}
