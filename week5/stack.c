// A simple singly linked list implementation.
// Also stack push/pop functions.


#include <stdio.h>
#include <stdlib.h>


struct list_node
{
    int node_val;
    struct list_node *next_node;
};


// It seems it is not a good idea to free(<a_NULL_pointer>) if you intend
// to use the pointer for something after freeing it.
void createEmptyListNode(struct list_node **node)
{
    // We don't free the input pointer here.
    *node = (struct list_node*)malloc(sizeof(struct list_node));
}


void printNode(struct list_node *node)
{
    printf("->node[%d]", node->node_val);
}


void readNode(struct list_node *node)
{
    printf("node value: ");
    scanf("%d", &node->node_val);
}


void push(struct list_node **top_node)
{
    struct list_node *new_node;
    new_node = (struct list_node*)malloc(sizeof(struct list_node));

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


void pop(struct list_node **top_node)
{
    if (*top_node)
    {
        printNode(*top_node);
        struct list_node *tmp_node = *top_node;
        *top_node = (*top_node)->next_node;
        free(tmp_node);
    }
    else
    {
        printf("NULL Pointer\n");
    }
}


// It is a good practice to use double pointers when freeing,
// so that you can set the last/original pointer to NULL when
// everything is freed. It is a good general practice for pointers to
// be used as: 1. initialize to NULL, 2. set to some memeory and use,
// 3. free after done and seto to NULL again.
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


void constructStack(struct list_node **top_node)
{
    int cont = 1;

    while (cont)
    {
        push((struct list_node**)top_node);
        printf("Continue ? [0=no] ");
        scanf("%d", &cont);
    }
}


void printStack(struct list_node *top_node)
{
    while (top_node)
    {
        printNode(top_node);
        top_node = top_node->next_node;
    }

    printf("\n");
}
