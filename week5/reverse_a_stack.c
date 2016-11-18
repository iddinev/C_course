// Write a program that reverses a stack.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.c"


int main()
{
    struct list_node *forward_stack = NULL;
    struct list_node *forward_stack_top = NULL;
    struct list_node *backward_stack = NULL;
    struct list_node *tmp_node = NULL;
    int i;

    constructStack((struct list_node**)&forward_stack);
    forward_stack_top = forward_stack;

    printf("Forward stack:\n");
    printStack((struct list_node*)forward_stack);

    while (forward_stack)
    {
        tmp_node = backward_stack;
        createEmptyListNode((struct list_node**)&backward_stack);
        memcpy(backward_stack, forward_stack, sizeof(struct list_node));
        backward_stack->next_node = tmp_node;
        forward_stack = forward_stack->next_node;
    }

    printf("Reversed stack:\n");
    printStack((struct list_node*)backward_stack);

    freeStack((struct list_node**)&forward_stack_top);
    freeStack((struct list_node**)&backward_stack);

    return 0;
}
