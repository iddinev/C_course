// Write a program that reverses a stack.


#include <stdio.h>
#include <stdlib.h>

#include "stack.c"


int main()
{
    struct stack_node *head_node = NULL;
    struct stack_node *reverse_head_node = NULL;
    struct stack_node *stack_start;
    struck stack_node tmp_node;

    constructStack((struct stack_node**)&head_node);

    printf("Original stack:\n");
    printStack((struct stack_node*)head_node);

    stack_start = head_node;

    while (head_node)
    {

    }


    return 0;
}
