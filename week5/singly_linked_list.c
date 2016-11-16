// Write a program that implements a singly linked list.
// Create a couple of nodes in a loop, then for verification
// go over them backwards and print their values - use a simple
// struct to implement the list.


#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int node_val;
    void *next_node;
}   node;

void printNode(node *node_ptr)
{
    printf("node[%d] ", node_ptr->node_val);
}


void readNode(node *node_ptr)
{
    printf("new node value: ");
    scanf("%d", &node_ptr->node_val);
}


int main()
{
    node root_node, head_node;
    node *work_node;
    int cont = 1;

    /* work_node = &root_node; */
    head_node = root_node;

    // Construct list.
    while (cont)
    {
        work_node = (node*)malloc(sizeof(node));
        readNode(work_node);
        head_node.next_node = (void*)work_node;
        head_node = *work_node;
        head_node.next_node = NULL;
        printNode((node*)&head_node);
        printf("\n");
        printf("Continue ? [0=no] ");
        scanf("%d", &cont);
    }

    // Print list forwards (and free memory in the procces).
    while (head_node.next_node)
    {
        printf("-> ");
        printNode((node*)&head_node);





    return 0;
}

