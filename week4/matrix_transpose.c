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


int **malloc2d(int rows, int cols)
{
    int i;
    static int **array;

    array = (int**)malloc(rows * sizeof(int*));

    for (i=0; i<rows; i++)
    {
        array[i] = (int*)malloc(cols * sizeof(int));
    }

    return array;
}


void free2d(void **ptr, int rows, int cols)
{
    int i;
    int **array;

    array = (int**)ptr;

    for (i=0; i<rows; i++)
    {
        free(array[i]);
    }

    free(array);
}


int **transpose2d(int **in_array, int in_rows, int in_columns)
{
    int i, j;
    static int **array;

    array = (int**)malloc2d(in_columns, in_rows);

    for (i=0; i<in_columns; i++)
    {
        for (j=0; j<in_rows; j++)
        {
            array[i][j] = in_array[j][i];
        }
    }

    free2d((void**)in_array, in_rows, in_columns);

    return array;
}


int main()
{
    int **array2;
    int i, j, k;
    int cols, rows;
    k = 0;
    rows = 3;
    cols = 2;

    array2 = (int**)malloc2d(rows, cols);

    for (i=0; i<rows; i++)
    {
        for (j=0; j<cols; j++)
        {
            array2[i][j] = k++;
        }
    }

    printArray(array2, rows, cols);

    array2 = transpose2d(array2, rows, cols);

    printArray(array2, cols, rows);

    free2d((void**)array2, cols, rows);

    return 0;
}
