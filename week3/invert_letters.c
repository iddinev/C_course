// Invert the positions of a string: "Text" -> "txeT".


#include <stdio.h>
#include <string.h>


char *invert_str(char *msg, int len)
{
    static char invert[250];
    int i;

    for (i=0; i<len; i++)
    {
        invert[len-i-1] = msg[i];
    }

    invert[len] = '\0';

    return invert;
}


int main()
{
    char string[] = "This string will be reverted.";
    char *inverted;

    inverted = invert_str(string, strlen(string));
    printf("%s\n", inverted);

    return 0;
}

