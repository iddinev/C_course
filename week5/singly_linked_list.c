// Write a program that implements a singly linked list.
// Create a couple of nodes in a loop, then for verification
// go over them backwards and print their values - use a simple
// struct to implement the list.


#include <stdio.h>
#include <stdlib.h>


struct node
{
    int node_val;
    struct node *next_node;
};


void printNode(struct node *node_ptr)
{
    printf("node[%d] ", node_ptr->node_val);
}


void readNode(struct node *node_ptr)
{
    printf("new node value: ");
    scanf("%d", &node_ptr->node_val);
}


int main()
{
    struct node *root_node, *head_node, *work_node;
    int cont = 1;

    root_node = (struct node*)malloc(sizeof(struct node));
    head_node = root_node;

    root_node->next_node = NULL;
    printf("Initialize the root node\n");
    readNode(root_node);

    // Construct list.
    while (cont)
    {
        work_node = (struct node*)malloc(sizeof(struct node));
        readNode(work_node);
        head_node->next_node = (struct node*)work_node;
        head_node = work_node;
        head_node->next_node = NULL;
        printf("Continue ? [0=no] ");
        scanf("%d", &cont);
    }

    // Print list forwards (and free memory in the procces).
    head_node = root_node;
    while (head_node)
    {
        printf("-> ");
        printNode((struct node*)head_node);
        free(head_node);
        head_node = head_node->next_node;
    }

    printf("\n");

    return 0;
}

