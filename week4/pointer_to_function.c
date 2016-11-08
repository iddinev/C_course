// Write a function that prints 'Hello World!' N times.
// Call it with a pointer.


#include <stdio.h>
#include <stdlib.h>


void printHelloWorld(int n)
{
    for (int i=0; i<n; i++)
    {
        printf("Hello World!\n");
    }
}


int main()
{
    void (*fp)(int);
    int n;

    // The 'fp = printHelloWorld;' syntax is also valid and
    // more explicit.
    fp = &printHelloWorld;

    fp(1);
    (*fp)(2);

    return 0;
}

