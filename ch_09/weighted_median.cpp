/*
    problem 9.2
*/

#include <iostream>
#include <climits>
#include <map>
using std::map;
using std::pair;

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

int median(int a[], int n)
{
    return kth_smallest(a, 0, n - 1, (n - 1) / 2 + 1);
}

int weighted_median(int a[], double w[], int start, int end)
{
    int med = median(a, end - start + 1);
    map<int, double> value_weight;
    for (int i = 0; i < end - start + 1; i++)
        value_weight.insert(std::make_pair(a[start+i], w[start+i]));

    int med_index = partition(a, start, end, med);
    double left_sum(0.0), right_sum(0.0);
    for (int i = start; i < med_index; i++)
        left_sum += value_weight.find(a[i])->second;
    for (int i = med_index + 1; i <= end; i++)
        right_sum += value_weight.find(a[i])->second;
    
    if (left_sum < 0.5 && right_sum <= 0.5)
        return med;
    else if (left_sum >= 0.5)
    {
        value_weight.find(med)->second += right_sum;
        return weighted_median(a, w, start, med_index);
    }
    else 
    {
        value_weight.find(med)->second += left_sum;
        return weighted_median(a, w, med_index, end);
    }
}

int main()
{
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    double weight[] = { 0.14, 0.15, 0.04, 0.2, 0.15, 0.20, 0.12}; 
    std::cout << weighted_median(arr, weight, 0, 6) << std::endl;

    return 0;
}
