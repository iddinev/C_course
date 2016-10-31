// Write a progam that runs 'n' simulations of the Monty Hall
// and aggregates wheter it is better to switch doors or not.
// Check wiki for more info on the Monty Hall problem.


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sum0 = 0;
    int sum1 = 0;
    int sum2 = 0;
    /* int sum3 = 0; */
    int ran = 0;
    int i;

    srand(time(NULL));
    for (i=0; i<1e2; i++)
    {
        ran = rand() % 3;
        if (ran == 0) {sum0++;}
        else if (ran == 1) {sum1++;}
        else if (ran == 2) {sum2++;}
        /* else if (ran == 3) {sum3++;} */
    }

    /* printf("0: %d, 1: %d, 2: %d, 3: %d\n", sum0, sum1, sum2, sum3); */
    printf("0: %d, 1: %d, 2: %d\n", sum0, sum1, sum2);

    /* printf("%d\n", RAND_MAX); */
    /* printf("%d\n", rand()); */
    return 0;
}
