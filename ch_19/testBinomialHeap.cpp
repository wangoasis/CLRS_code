#include "BinomialHeap.h"
#include <iostream>

int main()
{
    BinomialHeap<int>* heap = new BinomialHeap<int>();
    for (int i = 5; i < 20; i++)
        heap->insert(i);
//    heap->print();
    std::cout << heap->find_min() << std::endl;
    heap->extract_min();
    std::cout << heap->find_min() << std::endl;
}
