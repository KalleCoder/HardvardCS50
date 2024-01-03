#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string first = get_string("What's your first name?\n");
    string last = get_string("What's your last name?\n");
    printf("Hello, %s %s\n", first, last );
}