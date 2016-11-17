// A simple stack implementation.


#include <stdio.h>
#include <stdlib.h>


struct stack_node
{
    int node_val;
    struct stack_node *next_node;
};


void printNode(struct stack_node *node)
{
    printf("->node[%d]", node->node_val);
}


void readNode(struct stack_node *node)
{
    printf("node value: ");
    scanf("%d", &node->node_val);
}


void push(struct stack_node **top_node)
{
    struct stack_node *new_node;
    new_node = (struct stack_node*)malloc(sizeof(struct stack_node));

    if (!*top_node)
    {
        printf("Initialize the root node\n");
        readNode(new_node);
        new_node->next_node = NULL;
    }
    else
    {
        readNode(new_node);
        new_node->next_node = *top_node;
    }

    *top_node = new_node;
}


void pop(struct stack_node **top_node)
{
    if (*top_node)
    {
        printNode(*top_node);
        struct stack_node *tmp_node = *top_node;
        *top_node = (*top_node)->next_node;
        free(tmp_node);
    }
    else
    {
        printf("NULL Pointer\n");
    }
}

void freeStack(struct stack_node *top_node)
{
    struct stack_node *tmp_node;
    tmp_node = (struct stack_node*)malloc(sizeof(struct stack_node));

    while (top_node)
    {
        tmp_node = top_node;
        top_node = tmp_node->next_node;
        free(tmp_node);
    }

}


void constructStack(struct stack_node **top_node)
{
    int cont = 1;

    while (cont)
    {
        push((struct stack_node**)top_node);
        printf("Continue ? [0=no] ");
        scanf("%d", &cont);
    }
}


void printStack(struct stack_node *top_node)
{
    while (top_node)
    {
        printNode(top_node);
        top_node = top_node->next_node;
    }

    printf("\n");
}
