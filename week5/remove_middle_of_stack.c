// Write a program that finds the middle element in a stack and
// removes it. Print the modified stack afterwards.
// Remove the middle by looping through the stack only once.


#include <stdio.h>
#include <stdlib.h>

#include "stack.c"

int main()
{
    struct list_node *stack = NULL;
    struct list_node *tmp_node = NULL;
    struct list_node *middle_node = NULL;
    struct list_node *two_step_node = NULL;

    constructStack((struct list_node**)&stack);
    middle_node = stack;
    two_step_node = stack;

    printf("Original stack:\n");
    printStack((struct list_node*)stack);

    while (two_step_node && two_step_node->next_node)
    {
        tmp_node = middle_node;
        middle_node = middle_node->next_node;
        two_step_node = two_step_node->next_node->next_node;
    }

    if (middle_node->next_node)
    {
        tmp_node->next_node = middle_node->next_node;
        free(middle_node);

        printf("Original stack with middle element removed:\n");
        printStack((struct list_node*)stack);
    }
    else
    {
        printf("Stack has only 1 element.");
    }

    freeStack((struct list_node**)&stack);

    return 0;
}
