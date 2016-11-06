// Encrypt and decrypt a string with a
// given password using XOR. Len(pass) can be > len(string).


#include <stdio.h>
#include <string.h>


char *xor_strings(char *msg, char *key, int msg_len, int key_len)
{
    int j = 0;
    static char xor[250];

    strcpy(xor, msg);

    for (int i=0; i<msg_len; i++)
    {
        j = i % key_len;
        xor[i] = msg[i] ^ key[j];
    }

    return xor;
}


void printXOR(char *msg, int msg_len)
{
    for (int i=0; i<msg_len; i++)
    {
        printf("%c", msg[i]);
    }

    printf("\n");
}


int main()
{
    char msg[] = "This is the to-be encrypted message.";
    char pass[] = "aF^xa!d@sdasd|a$asdhgdasdjhasgd";
    int msg_len = strlen(msg);
    int key_len = strlen(pass);
    char *xor;
    char *decrypt;

    xor = xor_strings(msg, pass, msg_len, key_len);
    printf("len of xor is %d\n", strlen(xor));
    printXOR(xor, msg_len);

    decrypt = xor_strings(xor, pass, msg_len, key_len);
    printf("len of decrypt is %d\n", strlen(decrypt));
    printXOR(decrypt, msg_len);

    return 0;
}
