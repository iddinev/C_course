// Write a program that transposes a given n*m matrix.
// The matrix should be a dynamically allocated array.


#include <stdio.h>
#include <stdlib.h>


void printArray(int ** const array, int n, int m)
{
    int i, j;

    for (i=0; i<n; i++)
    {
        printf("{ ");

        for (j=0; j<m; j++)
        {
            printf("%d, ", array[i][j]);
        }

        printf("}\n");
    }
}


void malloc2d(void ***ptr, int rows, int cols)
{
    int i;

    *ptr = (void**)malloc(rows * sizeof(**ptr));

    for (i=0; i<rows; i++)
    {
        (*ptr)[i] = (void*)malloc(cols * sizeof(***ptr));
    }

}


// By the definition of a pointer - the free2d function
// does not need a 'pointer to pointer' in order to free stuff.
// I.e. no need for a free2d(void ***ptr) declaration followed
// by a free2d((void ***)&some_ptr); in order to work.
void free2d(void **ptr, int rows)
{
    int i;

    for (i=0; i<rows; i++)
    {
        free(ptr[i]);
    }

    free(ptr);
}


void transpose2d(int ***in_array, int in_rows, int in_columns)
{
    int i, j;
    int **array;

    malloc2d((void***)&array, in_columns, in_rows);
    array = (int**)array;

    for (i=0; i<in_columns; i++)
    {
        for (j=0; j<in_rows; j++)
        {
            array[i][j] = (*in_array)[j][i];
        }
    }

    free2d((void**)*in_array, in_rows);
    *in_array = array;

}


int main()
{
    int **array2;
    int i, j, k;
    int cols, rows;
    k = 0;
    rows = 3;
    cols = 2;

    malloc2d((void***)&array2, rows, cols);

    for (i=0; i<rows; i++)
    {
        for (j=0; j<cols; j++)
        {
            array2[i][j] = k++ + 1;
        }
    }

    printf("\n");
    printArray(array2, rows, cols);

    transpose2d((int***)&array2, rows, cols);

    printf("-------\n");
    printArray(array2, cols, rows);

    free2d((void**)array2, rows);

    return 0;
}
