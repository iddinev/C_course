// Implement a standard bubble sort.


#define INT_LEN 4


#include <stdio.h>


void bubble_sort_ints(int *a, int len)
{
    int i, j, temp;

    for (i=0; i<len; i++)
    {
        for (j=i+1; j<len; j++)
        {
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void printArray(int *array, int len)
{
    int i;

    printf("{ ");

    for (i=0; i<len; i++)
    {
        printf("%d, ", array[i]);
    }

    printf("}\n");
}

int main()
{
    int array[] = {6, 2, 1, 10, 7, 5};

    printf("initial array is: ");
    printArray(array, sizeof(array)/INT_LEN);

    bubble_sort_ints(array, sizeof(array)/INT_LEN);
    printf("sorted array is: ");
    printArray(array, sizeof(array)/INT_LEN);

    return 0;
}

