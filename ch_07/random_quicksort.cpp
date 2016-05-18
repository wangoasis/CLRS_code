#include <stdlib.h>
#define random(x) ( rand() % x)

#include <iostream>
int partition(int [], int, int);
int random_partition(int[], int, int);

void random_quicksort(int a[], int start, int end)
{
    if (start < end)
    {
        int p = random_partition(a, start, end);
        random_quicksort(a, start, p - 1);
        random_quicksort(a, p + 1, end);
    }
}

int random_partition(int a[], int start, int end)
{
    int p = random(end - start + 1) + start;
    std::swap(a[p], a[end]);
    return partition(a, start, end);
}

int partition(int a[], int start, int end)
{   
    int pivot = a[end];
    int i = start - 1;

    for (int j = start; j < end; j++)
        if (a[j] <= pivot)
            std::swap(a[++i], a[j]);
    std::swap(a[++i], a[end]);

    return i;
}

int main()
{
    int a[] = { 1, 3, 5, 2, 4, 6, 9, 8, 0};
    random_quicksort(a, 0, 8);
    for (int i = 0; i < 9; i++)
        std::cout << i << " ";
    std::cout << std::endl;
}
