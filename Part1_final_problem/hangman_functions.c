#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DEFAULT_WORD_LEN 4
#define RANDOM_SCALE 2



// Data is stored in a binary format.
const char *dict_file = "./dictionary.dat";
const char *used_words_file = "./guessedwords.dat";



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
    size_t n_bytes = minLen;
    FILE *dict_flp, *used_flp;

    srand(time(NULL));

    dict_flp = fopen(dict_file, "r");
    used_flp = fopen(used_words_file, "r");

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

    fclose(dict_flp);
    fclose(used_flp);

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
    FILE *used_flp;
    char *word;
    char *menu = "================\n"
                 "Hangman menu:\n"
                 "-----------------\n"
                 "1. Play a game.\n"
                 "2. Change minimal word length (now at 4).\n"
                 "3. Exit.\n"
                 "----------------\n"
                 "Enter your choice:\n";

    printf("%s", menu);
    // Quick hack to properly distinguish a single digit from anything else.
    entry = getchar() - 48;
    ungetc(10, stdin);
    /* printf("'%d'", entry); */
    flushSTDIN();

    used_flp = fopen(used_words_file, "a+");
    fclose(used_flp);

    switch(entry)
    {
        case 1:
            /* changeWordLen(); */
            word = (char *)pickRandomWord(4);
            printf("Chosen word is '%s'", word);
            free(word);
            return 0;
            break;
        case 2:
            return 0;
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
            break;

        default:
            return 1;
    }
    /* return 0; */
}
