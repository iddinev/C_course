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
