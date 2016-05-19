#include <iostream>

void counting_sort(int a[], int c[], int num, int range)
{
    int count[range+1];
    for (int i = 0; i < range + 1; i++)
        count[i] = 0;
    
    for (int i = 0; i < num; i++)
        count[a[i]] += 1;
    for (int i = 1; i < range + 1; i++)
        count[i] += count[i - 1];

    for (int j = num - 1; j >= 0; j--)
    {
        c[count[a[j]]-1] = a[j];
        count[a[j]]--;
    }
}

int main()
{
    int a[] = { 3, 3, 1, 2, 3, 5, 4, 5, 1};
    int c[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    counting_sort(a, c, 9, 5);
    for (int i = 0; i < 9; i++)
        std::cout << c[i] << " ";
    std::cout << std::endl;
}
