// Write a progam that runs 'n' simulations of the Monty Hall problem
// and aggregates wheter it is better to switch doors or not.
// Check wiki for more info on the Monty Hall problem.


#include <stdio.h>
#include <stdlib.h>


int single_game(char door, char choosen, char keep)
{
    if (keep)
    {
        if (choosen == door) {return 1;}
        else {return 0;}
    }
    else
    {
        if (choosen == door) {return 0;}
        else {return 1;}
    }
}


void iters_of_monty(int n_sims)
{
    float win, lose;
    int i;
    int k_succ = 0;
    int nok_succ = 0;
    int n_keep = 0;
    char door = 0;
    char choosen = 0;
    char keep = 0;

    srand(time(NULL));

    for (i=0; i<n_sims; i++)
    {
        door = rand() % 3;
        choosen = rand() % 3;
        keep = rand() % 2;

        if (keep)
        {
            k_succ += single_game(door, choosen, keep);
            n_keep++;
        }
        else
        {
            nok_succ += single_game(door, choosen, keep);
        }
    }

    win = (k_succ * 100.) / n_keep;
    lose = (n_keep - k_succ * 100.) / n_keep;
    printf("when keeping the door - win: %3.3f%c, lose: %3.3f%c\n", win, 37, lose, 37);
    win = (nok_succ * 100.) / (n_sims - n_keep);
    lose = ((n_sims - n_keep - nok_succ) * 100.) / (n_sims - n_keep);
    printf("when switching the door - win: %3.3f%c, lose: %3.3f%c\n", win, 37, lose, 37);
}


int main()
{
    int sims = 1e5;

    iters_of_monty(sims);

    return 0;
}
