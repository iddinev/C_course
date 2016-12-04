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
// 1. Refactor the code - there is a lot of code duplication.
// 2. The deleteEntry() deletes all matching entries - needs
//    to distinguish and ask when there are multiple matches.
// 3. All options should print success/fail messages.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Data is stored in a binary format.
const char *PhoneBook = "./PhoneBook.dat";
const char *tmp_PhoneBook = "./.tmp_PhoneBook.dat";


// Constant field lengths will make searcing quicker.
struct PhoneEntry
{
    char FirstName[51];
    char SecondName[51];
    char PhoneNumber[11];
};


void printEntry(struct PhoneEntry *Entry)
{
    printf("First name: %s\n", Entry->FirstName);
    printf("Second name: %s\n", (*Entry).SecondName);
    printf("Phone number: %s\n", Entry->PhoneNumber);
}


void addEntry()
{
    FILE *filep;
    struct PhoneEntry NewEntry;

    printf("Enter first name:\n");
    scanf("%s", NewEntry.FirstName);
    printf("Enter second name:\n");
    scanf("%s", NewEntry.SecondName);
    printf("Enter phone number:\n");
    scanf("%s", NewEntry.PhoneNumber);

    filep = fopen(PhoneBook, "a");

    fwrite(&NewEntry, sizeof(struct PhoneEntry), 1, filep);

    fclose(filep);
}


void searchByName()
{
    struct PhoneEntry SearchEntry, InputEntry;
    FILE *filep;
    int opt;

    printf("Search by first or second name [0|1]?:\n");
    scanf("%d", &opt);

    switch(opt)
    {
        case 0:
            printf("Enter first name:\n");
            scanf("%s", SearchEntry.FirstName);
            break;
        case 1:
            printf("Enter second name:\n");
            scanf("%s", SearchEntry.SecondName);
            break;

        default:
            printf("Invalid selection...\n");
    }

    filep = fopen(PhoneBook, "r");

    while(!feof(filep))
    {
        fread(&InputEntry, sizeof(struct PhoneEntry), 1, filep);
        if (!strcmp(SearchEntry.FirstName, InputEntry.FirstName) ||
            !strcmp(SearchEntry.SecondName, InputEntry.SecondName))
        {
            printEntry((struct PhoneEntry*)&InputEntry);
            break;
        }

    }

    fclose(filep);
}


// Space is cheap so we're going to use a tmp file for swapping.
void deleteEntry()
{
    struct PhoneEntry SearchEntry, InputEntry;
    FILE *tmp_filep, *filep;
    int opt;


    printf("Search by first or second name [0|1]?:\n");
    scanf("%d", &opt);

    switch(opt)
    {
        case 0:
            printf("Enter first name:\n");
            scanf("%s", SearchEntry.FirstName);
            break;
        case 1:
            printf("Enter second name:\n");
            scanf("%s", SearchEntry.SecondName);
            break;

        default:
            printf("Invalid selection...\n");
    }

    filep = fopen(PhoneBook, "r");
    tmp_filep = fopen(tmp_PhoneBook, "w");

    while(fread(&InputEntry, sizeof(struct PhoneEntry), 1, filep))
    {
        if (strcmp(SearchEntry.FirstName, InputEntry.FirstName) &&
            strcmp(SearchEntry.SecondName, InputEntry.SecondName))
        {
            fwrite(&InputEntry, sizeof(struct PhoneEntry), 1, tmp_filep);
        }
    }

    fclose(tmp_filep);
    fclose(filep);
    rename(tmp_PhoneBook, PhoneBook);
}


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
            searchByName();
            break;
        case 3:
            deleteEntry();
            break;
        case 4:
            printf("Exiting...\n");
            break;

        default:
            return 1;
    }

    return 0;
}
