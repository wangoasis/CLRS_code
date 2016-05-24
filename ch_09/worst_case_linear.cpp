#include <iostream>
#include <climits>

int partition(int [], int, int, int);

void insertion_sort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int find_median(int a[], int n)
{
    insertion_sort(a, n);  
    return a[n / 2];   
}

int kth_smallest(int a[], int start, int end, int k)
{
    if (k > 0 && k <= end - start + 1)
    {
        int n = end - start + 1; 
        
        int i, median[(n + 4) / 5];  
        for (i = 0; i < n / 5; i++)
            median[i] = find_median(a + start + i * 5, 5);
        if (i * 5 < n) 
        {
            median[i] = find_median(a + start + i * 5, n % 5);
            i++;
        }
        
        int med_of_med = (i == 1)? median[i - 1]
                         : kth_smallest(median, 0, i - 1, i / 2);
        
        int pos = partition(a, start, end, med_of_med);
        
        if (pos - start + 1 == k)
            return a[pos];
        if (pos - start + 1 > k)
            return kth_smallest(a, start, pos - 1, k);
        return kth_smallest(a, pos + 1, end, k - (pos - start + 1));
    }

    return INT_MAX;
}


int partition(int a[], int start, int end, int x)
{
    int i;
    for (i = start; i <= end; i++)
        if (a[i] == x)
            break;
    std::swap(a[i], a[end]);
    
    i = start - 1;
    for (int j = start; j < end; j++)
        if (a[j] <= x)
            std::swap(a[++i], a[j]);
    std::swap(a[++i], a[end]);
    return i;
}

int main()
{
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    for (int i = 0; i < 7; i++)
        std::cout << arr[i] << " ";

    int n = 7, k = 5;
    std::cout << "5th smallest element is "
    << kth_smallest(arr, 0, n - 1, k) << std::endl;

    insertion_sort(arr, 7);
    for (int i = 0; i < 7; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return 0;
}
