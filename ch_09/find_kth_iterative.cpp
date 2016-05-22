/*
    exercise 9.2-3:
    write an iterative version of randomized-select
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>

#define random(a) (rand() % a)
#define random_2(a, b) (rand() % (b - a + 1) + a)

int random_partition(int a[], int start, int end)
{
    int ran = random_2(start, end);
    std::swap(a[ran], a[end]);

    int pivot = a[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
        if (a[j] <= pivot)
            std::swap(a[j], a[++i]);
    std::swap(a[++i], a[end]);
    return i;
}

int find_kth_element(int a[], int start, int end, int k)
{
    while (start <= end && k <= end - start + 1)
    {   
        int p = random_partition(a, start, end);
        int i = p - start + 1;
        if (i == k)
            return a[p];
        else if (i > k)
            end = p - 1;  
        else
        {
            k = k - i;
            start = p + 1;
        }
    }
}

void quicksort(int a[], int start, int end)
{
    if (start < end)
    {
        int p = random_partition(a, start, end);
        quicksort(a, start, p - 1);
        quicksort(a, p + 1, end);
    }
}

int main()
{
    int length = 20;
    int a[length];

    srand((int)time(0));
    for (int i = 0; i < length; i++)
        a[i] = random(50);
    for (int i = 0; i < length; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    std::cout << "5th smallest: " << find_kth_element(a, 0, length - 1, 5) << std::endl;    

    quicksort(a, 0, length - 1);
    for (int i = 0; i < length; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    std::cout << "5th smallest from quicksort: " << a[4] << std::endl;    
}
