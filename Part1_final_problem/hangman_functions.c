#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DEFAULT_WORD_LEN 4
#define RANDOM_SCALE 1



// Data is stored in ascii.
const char *dict_file = "./dictionary.dat";
const char *used_words_file = "./guessedwords.dat";
const char *gallows_file = "./gallows.dat";



int randomScaled(int mod)
{
    int ran;
    ran = rand() % mod;
    return ran;
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


void printGallows()
{
    FILE *gallows_flp;
    static int file_pos;
    int n_bytes = DEFAULT_WORD_LEN;
    char *gallows = NULL;

    gallows_flp = fopen(gallows_file, "r");
    for (int i=0; i<=6; i++)
    {
        getline((char**)&gallows, (size_t*)&n_bytes, gallows_flp);
    file_pos = SEEK_CUR;




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
        current[strcspn(current, "\r\n")] = '\0';
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
                tmp[strcspn(tmp, "\r\n")] = '\0';
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
                tmp[strcspn(tmp, "\r\n")] = '\0';
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
        return safe;
    }
    else
    {
        free(safe);
        return chosen;
    }

    fclose(dict_flp);
    fclose(used_flp);

    free(tmp);
    free(current);
}


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
    flushSTDIN();

    used_flp = fopen(used_words_file, "a+");
    fclose(used_flp);

    switch(entry)
    {
        case 1:
            /* changeWordLen(); */
            word = (char *)pickRandomWord(4);
            printf("Chosen word is '%s'\n", word);
            free(word);
            return 0;
            break;
        case 2:
            drawGallows();
            return 0;
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
            break;

        default:
            return 1;
    }
}
