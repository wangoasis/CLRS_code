#include <iostream>
#include <vector>
#include <climits>
using std::vector;

#define abs(x) ((x) >= 0 ? (x) : -(x))

int median(int [], int);
int kth_select(int [], int, int, int);
int partition(int [], int, int, int);

vector<int> k_close_median(int a[], int n, int k)
{
    int med = median(a, n);
    // copy array a to c, to save original array
    int c[n];
    for (int i = 0; i < n; i++)
        c[i] = a[i];

    int b[n];
    for (int i = 0; i < n; i++)
        b[i] = abs(a[i] - med);
    
    // since a number in the array minus the med must equal 0, we don't need this number
    int thres = kth_select(b, 0, n - 1, k + 1); 

    vector<int> res;

    for (int i = 0; i < n; i++)
    {
        int diff = abs(c[i] - med);
        if (diff != 0  && diff <= thres)
            res.push_back(c[i]); 
    }

    return res;
}

int median_index(int n)
{
    if (n % 2)
        return n / 2;
    else
        return (n - 1) / 2;
}

int partition(int a[], int start, int end, int pivot)
{
    int i;
    for (i = start; i <= end; i++)
        if (a[i] == pivot)
            break;

    std::swap(a[i], a[end]);

    i = start - 1;
    for (int j = start; j < end; j++)
        if (a[j] <= pivot)
            std::swap(a[++i], a[j]);
    std::swap(a[++i], a[end]);
    return i; 
}

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

// used to find the median of 5 number
int find_median(int a[], int n)
{
    insertion_sort(a, n);
    return a[n / 2];
}

int kth_select(int a[], int start, int end, int k)
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
                         : kth_select(median, 0, i - 1, i / 2);
        
        int pos = partition(a, start, end, med_of_med);
        
        if (pos - start + 1 == k)
            return a[pos];
        if (pos - start + 1 > k)
            return kth_select(a, start, pos - 1, k);
        return kth_select(a, pos + 1, end, k - (pos - start + 1));
    }

    return INT_MAX;
}

int median(int a[], int n)
{
    return kth_select(a, 0, n - 1, median_index(n) + 1); 
}

int main()
{
    int length = 15;
    int a[length] = { 34, 2, 1, 15, 42, 5, 23, 16, 9, 27, 32, 44, 20, 25, 38};
    
    for (int i = 0; i < length; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    vector<int> res = k_close_median(a, length, 5);
    for (int i = 0; i < res.size(); i++)
        std::cout << res[i] << " ";
    std::cout << std::endl;

    insertion_sort(a, length);
    for (int i = 0; i < length; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    std::cout << "median: " << a[7] << std::endl;
}
