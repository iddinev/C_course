// Write a function that represents an integer as all the
// combinations of sum of 2 primes.


#include <stdio.h>


int check_sum(int a, int b, int sum)
{
    if ((a + b) != sum)
    {
        printf("%d + %d != %d\n", a, b, sum);
    }
    else 
    {
        printf("%d + %d == %d\n", a, b, sum);
    }

}


int isprime(int a)
{
    if (a == 1) {return 1;}
    int i;
    for(i=2; i<a; i++)
    {
        if ((a % i) == 0) {return 0;}
    }
    return 1;
}


void sum_of_primes(int sum)
{
    int i,k;
    k = 0;
    int median, rem;

    median = (sum / 2) + 1;

    for(i=1; i<=median; i=2*k+1)
    {
        rem = sum - i;
        if (isprime(rem) && isprime(sum - rem))
        {
            check_sum(rem, sum-rem, sum);
        }
        k++;
    }
}


int main()
{

    int sum = 41;

    sum_of_primes(sum);
    
    return 0;
}
