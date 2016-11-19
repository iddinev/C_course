// Write a program that finds the middle element in a stack and
// removes it. Print the modified stack afterwards.


#include <stdio.h>
#include <stdlib.h>

#include "stack.c"

int main()
{
    struct list_node *stack = NULL;
    struct list_node *tmp_node = NULL;
    struct list_node *middle_node = NULL;
    int stack_depth = 0;

    constructStack((struct list_node**)&stack);
    tmp_node = stack;

    printf("Original stack:\n");
    printStack((struct list_node*)stack);

    while (stack)
    {
        stack_depth++;
        stack = stack->next_node;
    }

    if (stack_depth = 1)
    {
        printf("Stack has depth of 1 - cannot remove middle.\n");
        return 0;
    }

    stack = tmp_node;
    for (int i=0; i<stack_depth/2 - 1; i++)
    {
        stack = stack->next_node;
    }

    middle_node = stack->next_node;
    stack->next_node = middle_node->next_node;
    free(middle_node);
    stack = tmp_node;

    printf("Original stack with middle element removed:\n");
    printStack((struct list_node*)stack);
    freeStack((struct list_node**)&stack);

    return 0;
}
