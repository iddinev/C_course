// Write a program that executes an array of functions
// (meaning the array has pointers to the functions).
// Execute the array sequentially, use NULL as the array end.


#include <stdio.h>
#include <stdlib.h>


int func0()
{
    printf("%s\n", __FUNCTION__);
    return 0;
}


int func1()
{
    printf("%s\n", __FUNCTION__);
    return 0;
}


/* void func2() */
/* { */
    /* printf("%s\n", __FUNCTION__); */
/* } */


int main()
{
    /* void (**fp)(); */
    int (**fp)();
    int a;
    /* void (*fc)(); */

    /* **fp() = ((void**)())malloc(3 * sizeof(void(*)())); */
    /* (**fp)() = (int**())malloc(3 * sizeof(int(*)())); */
    (**fp)() = malloc(3 * sizeof(int(*)()));
    /* fc = &func0; */

    /* (*fc)(); */
    fp[0] = func0;
    a = fp[0];
    /* fp[1] = func1; */
    /* fp[2] = func2; */

    /* fp[2](); */

    free(fp);

    return 0;
}

