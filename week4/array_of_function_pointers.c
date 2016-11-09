// Write a program that sequentially executes an array of functions.
// This means that the array should consist of function pointers.
// The functions should be of void type and take no params -
// just print something.


#include <stdio.h>
#include <stdlib.h>


void func0()
{
    printf("%s\n", __FUNCTION__);
}


void func1()
{
    printf("%s\n", __FUNCTION__);
}


void func2()
{
    printf("%s\n", __FUNCTION__);
}


int main()
{
    void (**fp)();
    int i = 0;
    int n = 4;

    fp = (void(**)())malloc(n * sizeof(void(*)()));

    fp[0] = &func0;
    fp[1] = &func1;
    fp[2] = &func2;
    fp[3] = NULL;

    while (*(fp+i) != NULL)
    {
        // The (*(fp+i))(); syntax is also valid - you can call a function
        // by its pointer as well as by dereferencing its pointer.
        (*(*(fp+i)))();
        i++;
    }

    free(fp);

    return 0;
}
