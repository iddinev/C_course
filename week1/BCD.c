// Encode an 8 bit int in a unpacked binary-coded decimal format.
// Wiki has more info on BCD's. Basically encode each int digit
// to a separate byte: BCD(72) == 0x72 == 114.


#define BYTE_LEN 8

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

int BCD(uint8_t num)
{
    uint32_t BCDencoded = 0;
    uint32_t nibble_mask = 0x01;
    uint8_t bit;
    char digit;
    char i = 0;

    while (num)
    {
        digit = num % 10;

        while (digit)
        {
            bit = digit % 2;
            if (bit) {BCDencoded |= nibble_mask;}
            nibble_mask <<= 1;
            digit /= 2;
        }

        i++;
        nibble_mask = 0x01;
        nibble_mask <<= 4 * i;
        num /= 10;
    }

    return BCDencoded;
}

int main()
{
    uint8_t num = 73;
    uint32_t BCDencoded;

    BCDencoded = BCD(num);
    printf("input int: %d, BCD as hex: 0x%x, BCD as decimal: %d\n", num, BCDencoded, BCDencoded);
    printf("BCD as binary:\n");
    printBits(sizeof(BCDencoded), &BCDencoded);

    return 0;
}

