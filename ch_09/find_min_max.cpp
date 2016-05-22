#include <iostream>
#include <utility>
#include <stdlib.h>
#include <time.h>
#define random(x) (rand() % x)
#define maxf(a, b) ( (a) > (b) ? a : b )
#define minf(a, b) ( (a) < (b) ? a : b )

std::pair<int, int> find_min_max(int a[], int length)
{
    int min(0), max(0), i(0); 
    if (length % 2)
    {
        min = a[0];
        max = a[0];
        i = 1;
    }
    else
    {
        min = minf(a[0], a[1]);
        max = maxf(a[0], a[1]);
        i = 2;
    }
    for (; i < length; i += 2)
    {
        int min2(0), max2(0);
        if (a[i] < a[i+1])
        {
            min2 = a[i];
            max2 = a[i+1];
        }
        else
        {
            max2 = a[i];
            min2 = a[i+1];
        }
        min = minf(min, min2);
        max = maxf(max, max2);
    }

    return std::make_pair(min, max);
}

int main() 
{
    int length = 25;
    int a[length];

    srand((int)time(0));
    for (int i = 0; i < length; i++)
        a[i] = random(100); 

    for (int i = 0; i < length; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    std::pair<int, int> res = find_min_max(a, length);
    std::cout << "min: " << res.first << " max: " << res.second << std::endl;
}
