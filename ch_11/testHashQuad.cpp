#include "hashQuad.h"
#include <iostream>

#define NumItems (100)

int main( )
{
    int currentSize = 21;
    HashTable<int> H(currentSize);
    int i;

    for(i = 0; i < NumItems; i++)
        H.insert(i);
    for (i = 0; i < NumItems; i++)
        if (!H.contains(i))
            std::cout << "insertion failed" << std::endl;
    H.remove(50);
    std::cout << H.contains(50) << std::endl;
}
