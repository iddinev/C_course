// Write a program that uses 3 non int pointers
// and casts them to the n-th element of an int array.


#include <stdio.h>


int main()
{
    int array[] = {12, 13, 22, 44, 55, 66};
    void *vp;
    char *cp;
    float *fp;

    vp = (void*)array;
    cp = (char*)array;
    fp = (float*)array;

    printf("\n");
    printf("void pointer casting %d\n", *((int*)vp+4));
    printf("char pointer casting %d\n", *((int*)cp+4));
    printf("float pointer casting %d\n",*((int*)fp+4));

    return 0;
}
