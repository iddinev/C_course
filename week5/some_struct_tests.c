// Write a program that implements a singly linked list.
// Create a couple of nodes in a loop, then for verification
// go over them backwards and print their values - use a simple
// struct to implement the list.


#include <stdio.h>


typedef struct
{
    int x, y;
}   simple;


// Seems like a good practice to explicitly list what
// kind of structs or whatever the function is expecting in
// the function declarations - Although C works just fine with
// only the name of the custom type.
/* void printStruct(struct simple *strc) */
void printStruct(simple *strc)
{
    printf("x is %d\n", strc->x);
    printf("y is %d\n", strc->y);
}


void read_input(simple *strc)
{
    printf("x is ? ");
    scanf("%d", &strc->x);
    printf("y is ? ");
    scanf("%d", &strc->y);
}


int main()
{
    simple st;
    simple *st_pt;

    st_pt = &st;

    st.x = 5;
    st.y = 16;
    printf("%d\n", &st_pt->x);

    read_input((simple*)&st);

    printStruct((simple*)&st);

    return 0;
}
