// Use switch/case to print the word assosiated with each grade digit -
// in Bulgaria's grading system. Print an appropriate message if the
// digit is an invalid grade.


#include <stdio.h>


int main()
{
    char grade = 5;

    switch (grade)
    {
        case 2:
            printf("Bad.\n");
            break;
        case 3:
            printf("Poor.\n");
            break;
        case 4:
            printf("Good.\n");
            break;
        case 5:
            printf("Very good.\n");
            break;
        case 6:
            printf("Excellent.\n");
            break;
        default:
            printf("Invalid grade digit.\n");
    }

    return 0;
}
