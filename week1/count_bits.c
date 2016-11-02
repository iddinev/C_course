// Count the bits set to 1 in a 32 bit int.


#include <stdio.h>
#include <stdint.h>


// Function taken from stackoverflow and used for
// representational/debugging purposes.
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
    const int32_t num = 0xfa6bce9d;
    uint32_t mask = 0x01;
    char i = 0;
    char rem_bits = sizeof(num) * 8;

    while (rem_bits > 0)
    {
        if (num & mask) {i++;}
        mask <<= 1;
        rem_bits--;
    }

    printBits(sizeof(num), &num);
    printf("%d\n", i);

    return 0;
}
