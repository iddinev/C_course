#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME_SIZE 61
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
    printf("++++++++++++\n");
    printf("Full name: %s\n", Entry->fullName);
    printf("Phone number: %s\n", Entry->PhoneNumber);
    printf("++++++++++++\n");
}


void nullifyPointer(char **ptr, int size)
{
    for (int i=0; i<size; i++)
    {
        (*ptr)[i] = 0;
    }
}

// Function to portably and properly flush stdin.
// It requries that the last char in the buffer is newline or EOF.
// There should be atleast 1 char in the buffer when called.
void flushSTDIN()
{
    int c;
    /* c = 1; */
    /* while (c != '\n' && c != EOF) */
    /* while ((c = getchar()) != '\n' && c != EOF) */
    while ((c = getchar()) != '\n' && c != EOF) { }
    /* { */
        /* c = getchar(); */
        /* if ((c = '\n') || (c = EOF)) */
        /* {printf("!");} */
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
    // *str should have enough memory to store max(name_len, phone_len).
    char *str = (char*)malloc(NAME_SIZE * sizeof(char));
    struct PhoneEntry NewEntry;

    printf("Enter full name:\n");
    fgets(str, NAME_SIZE, stdin);
    if (strlen(str) < (NAME_SIZE - 1)) {ungetc(10, stdin);}
    flushSTDIN();
    sanitizeString((char **)&str);
    strcpy(NewEntry.fullName, str);

    /* nullifyPointer((char **)&str, sizeof(str)); */
    printf("Enter phone number:\n");
    fgets(str, NUMBER_SIZE, stdin);
    if (strlen(str) < (NUMBER_SIZE - 1)) {ungetc(10, stdin);}
    flushSTDIN();
    sanitizeString((char **)&str);
    strcpy(NewEntry.PhoneNumber, str);

    filep = fopen(PhoneBook, "a");

    fwrite(&NewEntry, sizeof(struct PhoneEntry), 1, filep);

    fclose(filep);

    /* nullifyPointer((char **)&str, sizeof(str)); */
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
    printf("unsanitized !%s!", str);
    if (strlen(str) < (NAME_SIZE - 1)) {ungetc(10, stdin);}
    flushSTDIN();
    sanitizeString((char **)&str);
    strcpy(SearchEntry.fullName, str);
    printf("sanitized !%s!", SearchEntry.fullName);

    filep = fopen(PhoneBook, "r");

    if (deleteEntry) {tmp_filep = fopen(tmp_PhoneBook, "w");}

    while(fread(&InputEntry, sizeof(struct PhoneEntry), 1, filep))
    {
        if (!strcmp(SearchEntry.fullName, InputEntry.fullName))
        {
            if (!deleteEntry)
            {
                printf("\nFound an account:\n");
            }
            else
            {
                printf("\nDeleted an account:\n");
            }
            printEntry((struct PhoneEntry*)&InputEntry);
        }
        else if (deleteEntry)
        {
            fwrite(&InputEntry, sizeof(struct PhoneEntry), 1, tmp_filep);
        }
    }

    if (deleteEntry)
    {
        fclose(tmp_filep);
        rename(tmp_PhoneBook, PhoneBook);
    }

    fclose(filep);

    /* nullifyPointer((char **)&str, sizeof(str)); */
    free(str);
}

int mainMenu()
{
    int entry;
    char *menu = "================\n"
                 "Phonebook menu\n"
                 "-----------------\n"
                 "1. Add entry\n"
                 "2. Search by name\n"
                 "3. Delete entry\n"
                 "4. Exit\n"
                 "----------------\n"
                 "Enter your choice:\n";

    printf("%s", menu);
    scanf("%d", &entry);
    flushSTDIN();

    switch(entry)
    {
        case 1:
            addEntry();
            return 0;
            break;
        case 2:
            searchORdelete(0);
            return 0;
            break;
        case 3:
            searchORdelete(1);
            return 0;
            break;
        case 4:
            printf("Exiting...\n");
            return 0;
            break;

        default:
            printf("Invalid option. Exiting...\n");
            return 1;
    }
}
