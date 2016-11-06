// Print all the numbers up to 30, that are not divisible by 3 and 5.


#include <stdio.h>


void main()
{
	for (int i=0; i<=30; ++i)
	{
		if ((i % 3) != 0 && (i % 5) != 0)
		{
			printf("%d\n", i);
		}
	}
}
