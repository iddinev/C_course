// Compute the remainder from dividing 2 ints using while loops.


#include <stdio.h>


void main()
{
    int a;
    int b;

	a = 10;
	b = 3;

	while (a > b)
	{
		a = a - b;
	}

	printf("%d\n", a);
}
