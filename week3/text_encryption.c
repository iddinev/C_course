// Encrypt and decrypt a string with a
// given password using XOR.


#include <stdio.h>
#include <string.h>


void xor_strings(char *msg, char *key, char *xor)
{
    int cypher;
    int len;
    len = strlen(msg);
    printf("%d\n", len);

}


int main()
{
    char msg[] = "This is the to-be encrypted message.";
    char pass[] = "vnasdjg7dfFhadsf";
    char xor[] = "This is the to-be encrypted message.";

    xor_strings(msg, pass, xor);

    /* printf("%s\n", tst); */

    return 0;
}
