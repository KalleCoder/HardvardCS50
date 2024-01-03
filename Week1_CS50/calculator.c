#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // need to use long if you would add upp very large numbers (think in bits!!)
    long x = get_long("x: ");
    long y = get_long("y: ");

    // float z = (float) x / (float) y;
    // cant have to many floating point numbers as the bits will end

    // instead use to double the floating point numbers:
    double z = (double) x / (double) y;

    // %.*f still works for double
    printf("%.20f\n", z);
}