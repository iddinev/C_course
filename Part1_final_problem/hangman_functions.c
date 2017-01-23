#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#define DEFAULT_WORD_LEN 4
/* #define RANDOM_SCALE 35000 */
#define RANDOM_SCALE 1
#define GALLOWS_SIZE 63
#define NUMBER_OF_TRIES 63


// Constants and structs.

// Data is stored in ascii.
const char *dict_file = "./dictionary.dat";
const char *used_words_file = "./guessedwords.dat";
const char *gallows_file = "./gallows.dat";

struct list_node
{
    char node_val;
    struct list_node *next_node;
};

// *END* Constants and structs.



// Function prototypes:

void push(struct list_node **top_node, char letter);

char pop(struct list_node **top_node);

void freeStack(struct list_node **top_node);

// Return an int from a uniform [0;mod-1] distribution.
int randomScaled(int mod);

// Function to portably and properly flush stdin.
// It requries that the last char in the buffer is newline or EOF.
// There should be atleast 1 char in the buffer when called.
void flushSTDIN();

// Function is void as to leave the mem alocation and freeing
// to the caller.
void invertString(char *msg);

// Get malloced memory and copy the inverted gallow in it.
// Can return the current gallow or go and return the next until EOF.
// if there are no more gallows - free the mem and return NULL.
void getGallows(char *gallows, int next);

// Pick a random word (not belonging to the used_words file) newline stripped.
// If no word is picked, a safe option is returned - the first word
// that was read from the dictionary with ok len and not already used.
// If there is no safe option - returns NULL.
// Function looks a bit messy but - code now, refactor later.
char* pickRandomWord(int minLen);

//'guessed' should have the same length (not counting the '\0') as '*word'.
void printWord(struct list_node *word, char guessed[]);

struct list_node *WordToList(char *word);

int mainMenu();

// *END* Function prototypes.



// Function definitions:

void push(struct list_node **top_node, char letter)
{
    struct list_node *new_node;
    new_node = (struct list_node*)malloc(sizeof(struct list_node));

    if (!*top_node)
    {
        new_node->node_val = letter;
        new_node->next_node = NULL;
    }
    else
    {
        new_node->node_val = letter;
        new_node->next_node = *top_node;
    }

    *top_node = new_node;
}


char pop(struct list_node **top_node)
{
    char letter;
    if (*top_node)
    {
        letter = (*top_node)->node_val;
        struct list_node *tmp_node = *top_node;
        *top_node = (*top_node)->next_node;
        free(tmp_node);
    }
    else
    {
        letter = '\0';
    }

    return letter;
}


void freeStack(struct list_node **top_node)
{
    struct list_node *tmp_node;

    while (*top_node)
    {
        tmp_node = *top_node;
        *top_node = tmp_node->next_node;
        free(tmp_node);
    }

    *top_node = NULL;
}


int randomScaled(int mod)
{
    int ran;
    ran = rand() % mod;
    return ran;
}


void flushSTDIN()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


void invertString(char *msg)
{
    if (!msg) {return;}

    int len = strlen(msg);
    char *invert = (char*)malloc(len * sizeof(char));
    int i;

    for (i=0; i<len; i++)
    {
        invert[len-i-1] = msg[i];
    }

    invert[len] = '\0';

    strcpy(msg, invert);

    free(invert);
}


void getGallows(char *gallows, int next)
{
    FILE *gallows_flp;
    static int file_cur_pos = 0;
    static int file_prev_pos = 0;
    int n_bytes = 0;
    char swap;
    char *tmp = (char*)malloc(sizeof(char));
    gallows = (char*)realloc(gallows, GALLOWS_SIZE * sizeof(char));
    gallows[0] = '\0';

    gallows_flp = fopen(gallows_file, "r");

    if (next)
    {
        fseek(gallows_flp, file_cur_pos, SEEK_SET);
    }
    else
    {
        fseek(gallows_flp, file_prev_pos, SEEK_SET);
    }

    file_prev_pos = ftell(gallows_flp);

    for (int i=0; i<=6; i++)
    {
        getline((char**)&tmp, (size_t*)&n_bytes, gallows_flp);
        if (strlen(tmp) < 7)
        {
            free(gallows);
            gallows = NULL;
            break;
        }
        tmp[strcspn(tmp, "\r\n")] = '\0';
        // Legs and hands shouldn't be inverted.
        if (i == 3 || i == 4)
        {
            swap = tmp[1];
            tmp[1] = tmp[3];
            tmp[3] = swap;
        }
        invertString(tmp);
        strcat(gallows, tmp);
        strcat(gallows, "\n");
    }

    file_cur_pos = (int)ftell(gallows_flp);
    free(tmp);
}


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
    // Create the file if not already existing.
    used_flp = fopen(used_words_file, "a+");

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

// Check the word for letters and set the appropriate flags in 'guessed'.
// RETURN is number of positions of the letter if found, otherwise 0.
// 'guessed' should have the same length as 'word' not counting the '\0'.
int checkForLetter(struct list_node *word, char letter, char *guessed)
{
    int found_letter = 0;
    int i = 0;
    char lower_letter;

    while (word)
    {
        lower_letter = word->node_val;
        lowerCase((char *)&lower_letter);
        if (lower_letter == letter)
        {
            guessed[i] = 1;
            found_letter++;
        }
        i++;
        word = word->next_node;
    }
    return found_letter;
}
void printWord(struct list_node *word, char guessed[])
{
    int remaining = 0;
    int i = 0;

    while (word)
    {
        if (guessed[i])
        {
            printf("%c ", word->node_val);
        }
        else
        {
            printf("_ ");
            remaining++;
        }
        i++;
        word = word->next_node;
    }
    printf(", letters remaining: %d\n", remaining);
}


struct list_node *WordToList(char *word)
{
    struct list_node *word_list = NULL;
    int len = strlen(word);

    for (int i=0; i<len; i++)
    {
        push((struct list_node **)&word_list, word[len-1-i]);
    }

    return word_list;
}


// Wrapper function of tolower(int c).
void lowerCase(char *letter)
{
    int tmp;

    tmp = tolower((int) *letter);

    *letter = (char)tmp;
}


void playHangman(int word_len)
{
    struct list_node *word_list = NULL;
    /* struct list_node *tmp_word_list = NULL; */
    struct list_node *picked_letters = NULL;
    struct list_node *tmp = NULL;
    char *gallows = (char*)malloc(GALLOWS_SIZE * sizeof(char));
    char *word = NULL;
    char *guessed = NULL;
    char letter;
    char rem_tries = NUMBER_OF_TRIES;
    int positions;

    word = (char *)pickRandomWord(word_len);
    if (!word)
    {
        printf("No suitable word found.\n");
        return
    }
    guessed = (char *)malloc(strlen(word) * sizeof(char));
    for (int i=0; i<strlen(word); i++) {guessed[i] = 0;}
    word_list = WordToList(word);
    /* tmp_word_list = word_list; */

    while (rem_tries)
    {
        printf("Pick a letter: ");
        scanf("%c", &letter);
        flushSTDIN();
        lowerCase((char *)&letter);

        positions = checkForLetter(word_list, letter, guessed);

        if (!positions)
        {




    }
}


int mainMenu()
{
    int entry, word_len;
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
    flushSTDIN();


    switch(entry)
    {
        case 1:
            playHangman(DEFAULT_WORD_LEN);
            return 0;
            break;
        case 2:
            printf("New word length: ");
            scanf("%d", &word_len);
            playHangman(word_len);
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

// *END* Function definitions.
