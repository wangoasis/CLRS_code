#include <iostream>

void fastest_way(int a1[], int a2[], int t1[], int t2[], int e[], int x[], int n, int l1[], int l2[], int* f_last, int* l_last) {
    // total time
    int f1[n], f2[n];
    
    f1[0] = e[0] + a1[0];
    f2[0] = e[1] + a2[0];

    for (int j = 1; j < n; j++)
    {
        if (f1[j - 1] <= f2[j - 1] + t2[j - 1])
        {
            f1[j] = f1[j - 1] + a1[j];
            l1[j] = 1;
        }
        else
        {
            f1[j] = f2[j - 1] + t2[j - 1] + a1[j];
            l1[j] = 2;
        }
        if (f2[j - 1] <= f1[j - 1] + t1[j - 1])
        {
            f2[j] = f2[j - 1] + a2[j];
            l2[j] = 2;
        }
        else
        {
            f2[j] = f1[j - 1] + t1[j - 1] + a2[j];
            l2[j] = 1;
        }
    }

    if (f1[n - 1] + x[0] <= f2[n - 1] + x[1])
    {
        *f_last = f1[n - 1] + x[0];
        *l_last = 1;
    }
    else
    {
        *f_last = f2[n - 1] + x[1];
        *l_last = 2;
    }
}

void print_station(int l1[], int l2[], int l_last, int n)
{
    int i = l_last;
    std::cout << "station " << n << " line " << i << std::endl;
    for (int j = n - 1; j > 0; j--)
    {
        if (i == 1)
        {
            std::cout << "station " << j << " line " << l1[j] << std::endl;
            i = l1[j];
        }
        else
        {
            std::cout << "station " << j << " line " << l2[j] << std::endl;
            i = l2[j];
        }
    }
}

void print_station_reverse(int l1[], int l2[], int l_last, int n)
{
    int new_way;
    if (l_last == 1)
        new_way = l1[n - 1];
    else
        new_way = l2[n - 1];
    if (n >= 2)
        print_station_reverse(l1, l2, new_way, n - 1);
    std::cout << "station " << n << " line " << l_last << std::endl;

}

int main()
{
    int n = 6;

    // time spent in station
    int a1[6] = {7, 9, 3, 4, 8, 4};
    int a2[6] = {8, 5, 6, 4, 5, 7};
    // time getting on line
    int e[2] = {2, 4};
    // time spent on changing line
    int t1[5] = {2, 3, 1, 3, 4};
    int t2[5] = {2, 1, 2, 2, 1};
    // time leaving line
    int x[2] = {3, 2};

    int l1[6], l2[6];
    int f_last, l_last;

    fastest_way(a1, a2, t1, t2, e, x, n, l1, l2, &f_last, &l_last);
    print_station(l1, l2, l_last, n);
    std::cout << std::endl;
    print_station_reverse(l1, l2, l_last, n);
}
