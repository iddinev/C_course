// Write a program that can store simple phonebook entries in a file.
// The entries consist of 2 names and a phonenumber. The program
// should be able to: 1. add 2. search by name 3. delete 4. exit.
//
// The program menu should be:
// Phonebook menu
// -----------------
// 1. Add entry
// 2. Search by name
// 3. Delete entry
// 4. Exit
// ----------------
// Enter your choice:


// TODO:
// 1. Make the main menu work in a loop.
// 2. All options should print success/fail messages.


#include <stdio.h>

#include "phonebook_functions.c"


int main()
{
    int entry;
    char *menu = "Phonebook menu\n"
                 "-----------------\n"
                 "1. Add entry\n"
                 "2. Search by name\n"
                 "3. Delete entry\n"
                 "4. Exit\n"
                 "----------------\n"
                 "Enter your choice:\n";

    printf("%s", menu);
    scanf("%d", &entry);

    switch(entry)
    {
        case 1:
            addEntry();
            break;
        case 2:
            searchORdelete(0);
            break;
        case 3:
            searchORdelete(1);
            break;
        case 4:
            printf("Exiting...\n");
            break;

        default:
            return 1;
    }

    return 0;
}
