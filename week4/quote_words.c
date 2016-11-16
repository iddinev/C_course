// Write a program that quotes the words in a given string.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *quote_words(char *string, int len, char *delim)
{
    int n_words = 0;
    // Always beware when copying strings - strlen() DOES NOT COUNT THE
    // TERMINATING NULL BYTE, BUT strcpy() COPIES IT: so when doing
    // strcpy(dest,src) dest must be atleast strlen(src)+1 long!
    // Otherwise you get a buffer overflow - the function docs say it's
    // unpredictable what might happen in such a case.
    char *tmp = (char*)malloc(len * sizeof(char)+1);
    // ^ This is the case at hand.
    char *quoted_string, *tmp_start = tmp;

    strcpy(tmp, string);

    while ((tmp = strtok(tmp, delim)) != NULL)
    {
        n_words++;
        tmp = NULL;
    }

    tmp = tmp_start;
    strcpy(tmp, string);

    quoted_string = (char*)malloc((len + 2 * n_words)*sizeof(char));

    while ((tmp = strtok(tmp, delim)) != NULL)
    {
        strcat(quoted_string, "\"");
        strcat(quoted_string, tmp);
        strcat(quoted_string, "\" ");
        tmp = NULL;
    }

    return quoted_string;
}


int main()
{
    char msg[] = "This is the test string, ,  : bla,, wtf.";
    char *quoted_msg;
    char delim[] = " ";
    int msg_len = strlen(msg);

    quoted_msg = (char*)quote_words(msg, msg_len, delim);

    printf("%s\n", msg);
    printf("%s\n", quoted_msg);

    return 0;
}
