#include <iostream>
#include <vector>

std::pair<int, int> partition_equal_element(int [], int, int);

void quicksort_equal_element(int a[], int start, int end)
{
    if (start < end)
    {
        std::pair<int, int> res = partition_equal_element(a, start, end);
        int p = res.first;
        int num = res.second;
        quicksort_equal_element(a, start, p - num - 1);
        quicksort_equal_element(a, p + 1, end);
    }
}

std::pair<int, int> partition_equal_element(int a[], int start, int end)
{
    int pivot = a[end];
    int i = start - 1;
    std::vector<int> index;

    for (int j = start; j < end; j++)
    {
        if (a[j] <= pivot)
        {
            std::swap(a[++i], a[j]);
            if (a[i] == pivot)
                index.push_back(i);
        }
    }
    std::swap(a[++i], a[end]);
    std::pair<int, int> res = std::make_pair(i, index.size());

    for (int j = 0; j < index.size(); j++)
        std::swap(a[index[j]], a[--i]);

    return res;
}

int main()
{
    int a[] = { 5, 11, 5, 2, 1, 3, 7, 9, 11, 7, 5, 5, 10, 4, 10};
    quicksort_equal_element(a, 0, 14);
    for (int i = 0; i < 15; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}
