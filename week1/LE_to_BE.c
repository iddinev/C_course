// Write a program that converts
// a 32 bit int from little endiean to big
// endian and back.


#include <stdio.h>
#include <stdint.h>


void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}


int main()
{
    const int32_t LE = 0xfa;
    int32_t to_LE = 0x00;

    const int32_t BE = 0xcc;
    int32_t to_BE = 0x00;

    uint32_t BE_mask = 0x80000000;
    uint32_t LE_mask = 0x01;

    char rem_bits = sizeof(LE) * 8;

    while (rem_bits > 0)
    {
        if (LE & LE_mask) {to_BE |= BE_mask;}
        if (BE & BE_mask) {to_LE |= LE_mask;}
        LE_mask <<= 1;
        BE_mask >>= 1;
        rem_bits--;
    }
    printf("LE number is:\n");
    printBits(sizeof(LE), &LE);
    printf("LE number in BE is:\n");
    printBits(sizeof(to_BE), &to_BE);

    printf("BE number is:\n");
    printBits(sizeof(BE), &BE);
    printf("BE number in LE is:\n");
    printBits(sizeof(to_LE), &to_LE);

    return 0;
}
