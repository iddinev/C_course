// Write a program that converts
// a 32 bit int from little endiean to big
// endian and back.

#include <stdio.h>

int main()
{
    unsigned long long int LE;
    unsigned long long int BE;

    LE = 0x01020304;
    printf("%x\n", LE);

    while (LE != 0)

    printf("%x\n", BE);

    return 0;
}
