#include <iostream>
int partition(int [], int, int);

void quicksort(int a[], int start, int end)
{
    if (start < end)
    {
        int p = partition(a, start, end);
        quicksort(a, start, p - 1);
        quicksort(a, p + 1, end);
    }
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
    quicksort(a, 0, 8);
    for (int i = 0; i < 9; i++)
        std::cout << i << " ";
    std::cout << std::endl;
}
