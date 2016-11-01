// Write a function that calculates factorials recursively.


#include <stdio.h>


int fac(int num)
{
    if (num == 0) {return 1;}
    else {return num * fac(num -1);}
}


int main()
{

    unsigned int num;

    num = 4;

    printf("%d! is %d\n", num, fac(num));

    return 0;
}
