#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFF_SIZE 11
#define DEFAULT_WORD_LEN 4
#define RANDOM_SCALE 100



// Data is stored in a binary format.
const char *dict_file = "./dictionary.dat";
const char *used_words_file = "./used_words.dat";



int randomScaled(int mod)
{
    int rand;
    rand = rand() % mod;
    return rand;
}


char* pickRandomWord(int minLen)
{
    char *current = (char*)malloc(BUFF_SIZE*sizeof(char));
    char *last_safe = (char*)malloc(BUFF_SIZE*sizeof(char));
    size_t n_bytes = BUFF_SIZE;
    FILE *dict_flp, *used_flp;
    
    dict_flp = fopen(dict_file, "r");
    used_flp = fopen(used_words_file, "r");

    
    
    while (getline((char**)&current, (size_t*)&n_bytes, dict_flp) != -1)
    {
        if (len(current) < minLen) 
        {
            continue;
        }
        else if (randomScaled(RANDOM_SCALE) = 1)
        {
            while (getline((char**)&last_safe, (size_t*)&n_bytes, used_flp) != -1)
            {
                if (!strcmp(current, last_safe))
                {



    return current;
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
            word = (char *)pickRandomWord(5);
            printf("Chosen word is '%s'", word);
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
