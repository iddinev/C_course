#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFF_SIZE 11
#define DEFAULT_WORD_LEN 4
#define RANDOM_SCALE 4



// Data is stored in a binary format.
const char *dict_file = "./dictionary.dat";
const char *used_words_file = "./used_words.dat";



int randomScaled(int mod)
{
    int ran;
    ran = rand() % mod;
    return ran;
}


// Pick a random word (not belonging to the used_words file) newline stripped.
// If no word is picked, a safe option is returned - the first word
// that was read from the dictionary with ok len and not already used.
// If there is no safe option - returns NULL.
// Function looks a bit messy but - code now, refactor later.
char* pickRandomWord(int minLen)
{
    char *chosen = (char*)malloc(minLen*sizeof(char));
    char *safe = (char*)malloc(minLen*sizeof(char));
    char *current = NULL;
    char *tmp = NULL;
    char match = 0;
    char safeOK = 0;
    char chosenOK = 0;
    size_t n_bytes = BUFF_SIZE;
    FILE *dict_flp, *used_flp;

    dict_flp = fopen(dict_file, "r");
    used_flp = fopen(used_words_file, "a+");

    while (getline((char**)&current, (size_t*)&n_bytes, dict_flp) != -1)
    {
        if (chosenOK)
        {
            break;
        }

        if (strlen(current) < minLen)
        {
            continue;
        }

        if (!safeOK)
        {
            match = 0;
            fseek(used_flp, 0, SEEK_SET);
            while (getline((char**)&tmp, (size_t*)&n_bytes, used_flp) != -1)
            {
                if (!strcmp(current, tmp))
                {
                    match = 1;
                    break;
                }
            }
            if (!match)
            {
                strcpy(safe, current);
                safeOK = 1;
            }
        }

        if (randomScaled(RANDOM_SCALE) == 1)
        {
            match = 0;
            fseek(used_flp, 0, SEEK_SET);
            while (getline((char**)&tmp, (size_t*)&n_bytes, used_flp) != -1)
            {
                if (!strcmp(current, tmp))
                {
                    match = 1;
                    break;
                }
            }
            if (!match)
            {
                strcpy(chosen, current);
                chosenOK = 1;
            }
        }
    }

    if (!chosenOK)
    {
        free(chosen);
        safe[strlen(safe)-1] = '\0';
        return safe;
    }
    else
    {
        free(safe);
        chosen[strlen(chosen)-1] = '\0';
        return chosen;
    }

    free(tmp);
    free(current);
}


void nullifyPointer(char *ptr, int size)
{
    for (int i=0; i<size; i++)
    {
        ptr[i] = 0;
    }
}


// Function to portably and properly flush stdin.
// It requries that the last char in the buffer is newline or EOF.
// There should be atleast 1 char in the buffer when called.
void flushSTDIN()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


// Space is cheap so we're going to use a tmp file for swapping.
int mainMenu()
{
    int entry;
    char *word;
    char *menu = "================\n"
                 "Hangman menu\n"
                 "-----------------\n"
                 "1. Change min word length (now at 4).\n"
                 "2. Exit.\n"
                 "----------------\n"
                 "Enter your choice:\n";

    printf("%s", menu);
    // Quick hack to properly distinguish a single digit from anything else.
    entry = getchar() - 48;
    flushSTDIN();

    switch(entry)
    {
        case 1:
            /* changeWordLen(); */
            srand(time(NULL));
            word = (char *)pickRandomWord(4);
            printf("Chosen word is '%s'", word);
            free(word);
            return 0;
            break;
        case 2:
            printf("Exiting...\n");
            return 0;
            break;

        default:
            // Play the game.
            return 0;
    }
}
