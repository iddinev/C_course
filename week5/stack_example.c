// A simple stack example.


#include <stdio.h>
#include <stdlib.h>

#include "stack.c"


int main()
{
    struct stack_node *head_node = NULL;

    constructStack((struct stack_node**)&head_node);

    printStack((struct stack_node*)head_node);

    freeStack((struct stack_node*)head_node);

    return 0;
}
