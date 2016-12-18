#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 11

void sanitizeString(char **input_str)
/* char sanitizeString(char *input_str) */
{
    /* printf("%d\n", input_str); */
    /* printf("%d\n", *input_str); */
    static char work_str[NAME_SIZE];
    /* static char work_str[NAME_SIZE]; */
    char *tmp;
    char delim[] = " \n";
    int len;

    /* strcpy(work_str, input_str); */

    printf("BBBB, %s\n", *input_str);
    while ((*input_str = strtok(*input_str, delim)) != NULL)
    /* while ((input_str = strtok(input_str, delim)) != NULL) */
    {
        printf("AAAA\n");
        strcat(work_str, *input_str);
        *input_str = NULL;
        /* strcat(work_str, input_str); */
        /* input_str = NULL; */
    }

    len = strlen(work_str);
    if (!strcmp(&work_str[len], " ")) {work_str[len] = '\0';}

    *input_str = work_str;
    /* return work_str; */
}

int main()
{
    char str[NAME_SIZE];
    int ptr[2];
    ptr[0] = 5;
    int *pt = (int *)malloc(2*sizeof(int));
    pt[0] = 6;
    char c = 'c';
    /* ptr = &c; */
    int str_size = NAME_SIZE;

    printf("Give a string\n");
    fgets(str, str_size, stdin);
    printf("Input string is\n\"%s\"", str);
    /* printf("%d\n", ptr); */
    /* printf("%d\n", &ptr); */
    /* printf("%d\n", *ptr); */
    printf("%d\n", pt);
    printf("%d\n", &pt);
    printf("%d\n", *pt);
    printf("%d\n", &pt[0]);
    /* printf("%d\n", &ptr[0]); */
    /* printf("%d\n", &ptr[1]); */
    /* printf("%d\n", &str); */
    /* printf("%d\n", str); */
    /* printf("AAAA, %s\n", *ptr ); */
    /* printf("Input string is\n%s", str); */
    sanitizeString((char **)&str);
    /* str = sanitizeString(str); */
    printf("Sanitized string is\n\"%s\"", str);

    return 0;
}
