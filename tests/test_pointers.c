#include <stdio.h>
#include <stdlib.h>


void p_calcs(int *p, int len)
{
    int *start = p;
    for (int i=0; i<len; i++)
    {
        *p = i;
        printf("incrementing pointer\n");
        p++;
    }

    p = start;
}

void printP(int *p, int len)
{
    for (int i=0; i<len; i++)
    {
        printf("%d ", *p);
        p++;
    }

    printf("\n");
}


int main()
{
    int *pt, a, len;
    len = 10;

    pt = &a;

    p_calcs(pt, len);
    printP(pt, len);
    printP(pt, len);

    return 0;
}
