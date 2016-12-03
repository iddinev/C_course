// A simple singly linked list implementation.
// Also stack push/pop functions.


#ifndef __STACK_H__
#define __STACK_H__


struct list_node
{
    int node_val;
    struct list_node *next_node;
};


// It seems it is not a good idea to free(<some_NULL_pointer>) if you intend
// to use the pointer for something after freeing it.
void createEmptyListNode(struct list_node **node);

void printNode(struct list_node *node);

void readNode(struct list_node *node);

void push(struct list_node **top_node);

void pop(struct list_node **top_node);

// It is a good practice to use double pointers when freeing,
// so that you can set the last/original pointer to NULL when
// everything is freed. It is a good general practice for pointers to
// be used as: 1. initialize to NULL, 2. set to some memeory and use,
// 3. free after done and seto to NULL again.
void freeStack(struct list_node **top_node);

void constructStack(struct list_node **top_node);

void printStack(struct list_node *top_node);


#endif
