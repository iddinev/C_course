#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME_SIZE 11
#define NUMBER_SIZE 11


// Data is stored in a binary format.
const char *PhoneBook = "./PhoneBook.dat";
const char *tmp_PhoneBook = "./.tmp_PhoneBook.dat";


// Constant field lengths will make searcing quicker.
struct PhoneEntry
{
    char fullName[NAME_SIZE];
    char PhoneNumber[NUMBER_SIZE];
};


void printEntry(struct PhoneEntry *Entry)
{
    printf("Full name: %s\n", Entry->fullName);
    printf("Phone number: %s\n", Entry->PhoneNumber);
}


// Function to portably and properly flush stdin.
/* void flushSTDIN(flushNewLine) */
void flushSTDIN()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    /* if (flushNewLine) */
    /* { */
        /* while ((c = getchar()) != '\n' && c != EOF) { } */
    /* } */
    /* else */
    /* { */
        /* while ((c = getchar()) != EOF) { } */
    /* } */

}

void sanitizeString(char **input_str)
{
    char *work_str = malloc(NAME_SIZE * sizeof(char));
    char *tmp;
    char delim[] = " \n";
    int len;

    tmp = *input_str;

    while ((*input_str = strtok(*input_str, delim)) != NULL)
    {
        strcat(work_str, *input_str);
        strcat(work_str, " ");
        *input_str = NULL;
    }

    len = strlen(work_str);
    if (!strcmp(&work_str[len-1], " ")) {work_str[len-1] = '\0';}

    *input_str = work_str;

    free(tmp);
}


void addEntry()
{
    FILE *filep;
    char *str = (char*)malloc(NAME_SIZE * sizeof(char));
    struct PhoneEntry NewEntry;

    printf("Enter full name:\n");
    fgets(str, NAME_SIZE, stdin);
    /* flushSTDIN(1); */
    /* printf("%d" */
    if  (strlen(str) == (NAME_SIZE - 1)) {flushSTDIN();}
    /* sanitizeString((char **)&str); */
    /* strcpy(NewEntry.fullName, str); */
    printf("!%s!", str);

    printf("Enter phone number:\n");
    /* printf("Enter phone number:"); */
    fgets(NewEntry.PhoneNumber, NUMBER_SIZE, stdin);
    printf("!%s!", NewEntry.PhoneNumber);
    /* scanf("%s", NewEntry.PhoneNumber); */

    filep = fopen(PhoneBook, "a");

    fwrite(&NewEntry, sizeof(struct PhoneEntry), 1, filep);

    fclose(filep);

    free(str);
}


// Space is cheap so we're going to use a tmp file for swapping.
void searchORdelete(char deleteEntry)
{
    struct PhoneEntry SearchEntry, InputEntry;
    char *str = malloc(NAME_SIZE * sizeof(char));
    FILE *tmp_filep, *filep;

    printf("Enter full name:\n");
    fgets(str, NAME_SIZE, stdin);
    sanitizeString((char **)&str);
    strcpy(SearchEntry.fullName, str);

    filep = fopen(PhoneBook, "r");

    if (deleteEntry) {tmp_filep = fopen(tmp_PhoneBook, "w");}

    while(fread(&InputEntry, sizeof(struct PhoneEntry), 1, filep))
    {
        if (!strcmp(SearchEntry.fullName, InputEntry.fullName))
        {
            if (deleteEntry)
            {
                fwrite(&InputEntry, sizeof(struct PhoneEntry), 1, tmp_filep);
            }
            printEntry((struct PhoneEntry*)&InputEntry);
        }
    }

    if (deleteEntry)
    {
        fclose(tmp_filep);
        rename(tmp_PhoneBook, PhoneBook);
    }

    fclose(filep);

    free(str);
}
