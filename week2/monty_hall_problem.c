// Write a progam that runs 'n' simulations of the Monty Hall problem
// and aggregates wheter it is better to switch doors or not.
// Works in the case of 'N' doors with 'p' being opened by the host.
// Check wiki for more info on the Monty Hall problem.


#include <stdio.h>
#include <stdlib.h>


int single_game(int door, int choosen, int keep, int n_doors, int n_opened)
{
    if (keep)
    {
        if (choosen == door) {return 1;}
        else {return 0;}
    }
    else
    {
        if (choosen == door) {return 0;}
        else if (!(rand() % (n_doors - n_opened - 1))) {return 1;}
        else {return 0;}
    }
}


// Generalized function for the case of n_doors doors, and the host opening
// n_opened loosing doors.
void iters_of_monty(int n_sims, int n_doors, int n_opened)
{
    float win, lose;
    int i;
    int k_succ = 0;
    int nok_succ = 0;
    int n_keep = 0;
    int door = 0;
    int choosen = 0;
    int keep = 0;

    srand(time(NULL));

    for (i=0; i<n_sims; i++)
    {
        door = rand() % n_doors;
        choosen = rand() % n_doors;
        keep = rand() % 2;

        if (keep)
        {
            k_succ += single_game(door, choosen, keep, 0, 0);
            n_keep++;
        }
        else
        {
            nok_succ += single_game(door, choosen, keep, n_doors, n_opened);
        }
    }

    printf("running %d sims with %d doors and %d doors being opened\n", n_sims, n_doors, n_opened);
    win = (k_succ * 100.) / n_keep;
    lose = ((n_keep - k_succ) * 100.) / n_keep;
    printf("when keeping the door - win: %3.3f%%, lose: %3.3f%%\n", win, lose);
    win = (nok_succ * 100.) / (n_sims - n_keep);
    lose = ((n_sims - n_keep - nok_succ) * 100.) / (n_sims - n_keep);
    printf("when switching the door - win: %3.3f%%, lose: %3.3f%%\n", win, lose);
}


int main()
{
    int sims = 1e5;
    int doors = 10;
    int opened = 4;

    iters_of_monty(sims, doors, opened);

    return 0;
}
