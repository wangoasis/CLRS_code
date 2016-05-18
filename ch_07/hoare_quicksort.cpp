#include <iostream>

int hoare_partition(int [], int, int);

void hoare_quicksort(int a[], int start, int end)
{
    if (start < end)
    {
        int p = hoare_partition(a, start, end);
        hoare_quicksort(a, start, p);
        hoare_quicksort(a, p + 1, end);
    }
}

int hoare_partition(int a[], int start, int end)
{   
    int pivot = a[start];
    int i = start;
    int j = end;

    while (true)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i < j)
            std::swap(a[i], a[j]);
        else 
            return j;
    }
}

int main()
{
    int a[] = { 9, 7, 5, 3, 1, 4, 6, 8, 12, 10};
    hoare_quicksort(a, 0, 9);
    for (int i = 0; i < 10; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}
