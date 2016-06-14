#include "BTree.h"
#include <iostream>

int main()
{
    BTree<int> tree;
    for (int i = 1; i < 100; i++)
    {
        tree.insert(i);
    }
    std::cout << tree.exists(5) << std::endl;
//    tree.print_tree();
    std::cout << tree.predecessor(90) << std::endl;
}
