#include <stdio.h>

int main()
{
    const float acc = 1e-6;
    int n = 1;
    float sum = 0;
    float summand = 1;
    float sign = 1;

	while (sign * summand >= acc)
	{
        sign = -1 * sign;
        sum += summand;
        summand = sign / (2 * n + 1);
        n++;

	}

	printf("pi is = %f, n = %d\n", 4 * sum, n);

return 0;
}

