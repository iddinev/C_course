// Find out what the hell you should do in this assignment!


#define BYTLE_LEN 8

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

void printBCD(uint8_t *num)
{
}

int main()
{
    uint8_t num = 0x72;
    uint8_t  tmp_num = num;
    uint32_t BCD;
    uint8_t mask = 0x01;
    char i = 0;
    /* char rem_bits = sizeof(num) * BYTLE_LEN; */

    /* printf("%d\n", num); */
    do
    {
        tmp_num = num % 10;
        printf("%d\n", num);
        num = num / 10;
        /* printf("%d\n", tmp_num); */
    } while (num / 10 != 0);

    /* printf("%d\n", 11 % 10); */

    return 0;
}

