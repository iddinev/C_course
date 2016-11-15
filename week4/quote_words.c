// Write a program that quotes the words in a given string.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *quote_words(char *string, int len, char *delim)
{
    int n_words = 0;
    char *tmp = (char*)malloc(len * sizeof(char));
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
