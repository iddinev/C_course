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

    printStack((struct list_node*)stack);

    while (stack)
    {
        stack_depth++;
        stack = stack->next_node;
    }

    stack = tmp_node;
    for (int i=0; i<stack_depth/2 - 2; i++)
    {
        stack = stack->next_node;
    }

    middle_node = stack->;
    stack = middle_node->next_node;
    free(middle_node);
    stack = tmp_node;

    /* printf("Stack depth is %d\n", stack_depth); */
    printStack((struct list_node*)stack);
    freeStack((struct list_node**)&stack);

    return 0;
}
