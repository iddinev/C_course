// Compute the greatest common denominator of 2 ints using
// Euclid's algorithm.


#include <stdio.h>


void main()
{
    int a;
    int b;
    int t;

	a = 24;
	b = 16;

	while (b != 0)
	{
		t = b;
        b = a % b;
        a = t;
	}

	printf("%d\n", a);
}
