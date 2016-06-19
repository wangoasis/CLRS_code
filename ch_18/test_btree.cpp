#include "BTree.h"
#include <iostream>

int main()
{
    BTree<int> tree;
    for (int i = 1; i < 100; i++)
    {
        tree.insert(i);
    }
    std::cout << "exists 95? " << tree.exists(95) << std::endl;
//    std::cout << "print tree" << std::endl;
//    tree.print_tree();
    std::cout << "max: " << tree.find_max() << std::endl;
    std::cout << "min: " << tree.find_min() << std::endl;

    std::cout << "remove 33..." << std::endl;
    tree.remove(33);

//    std::cout << "print tree" << std::endl;
//    tree.print_tree();

    std::cout << "exists 33? " << tree.exists(33) << std::endl;
    std::cout << "exists 34? " << tree.exists(34) << std::endl;
    std::cout << "predecessor of 34: " << tree.predecessor(34) << std::endl;
}

