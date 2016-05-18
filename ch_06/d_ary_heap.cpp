#include <iostream>

class d_ary_heap
{
public:
    d_ary_heap(int d_children)
    : d(d_children) 
    {
        heapsize = 0;
    }

    int max_element()
    {
        if (heapsize != 0)
            return a[0];
        return -1;
    }

    int extract_max_element()
    {
        if (!heapsize)
        {
            std::cerr << "empth heap" << std::endl;
            return -1;
        }
        int max = a[0];
        a[0] = a[heapsize--];
        down_heapify(a, 0);

        return max;
    }

    void insert(int x)
    {
        if (heapsize == 10000)
        {
            std::cerr << "full heap" << std::endl;
            return;
        }
        a[heapsize++] = x;
        up_heapify(a, heapsize - 1);
    }

private:
    int a[10000];
    int d; // number of children
    int heapsize;
    
    int parent(int i)
    {
        return (i - 1) / d;
    }

    int first_child(int i)
    {
        return d * i + 1;
    }

    void down_heapify(int array[], int i)
    {
        int first = first_child(i);
        int last = first + d - 1;
        int largest = i;

        for (int j = first; j <= last && j < heapsize; j++)
            if (a[j] > a[largest])
                largest = j;

        if (largest != i)
        {
            std::swap(a[i], a[largest]);
            down_heapify(a, largest);
        }
    }

    void up_heapify(int array[], int i)
    {
        while (a[i] > a[parent(i)])
        {
            std::swap(a[i], a[parent(i)]);
            i = parent(i);
        }
    }
};

int main() 
{
    d_ary_heap heap(4);
    for (int i = 0; i < 16; i++)
        heap.insert(i);

    for (int i = 30; i > 16; i--)
        heap.insert(i);

    for (int i = 0; i < 10; i++)
    {
        std::cout << heap.extract_max_element() << std::endl;
    }
}
