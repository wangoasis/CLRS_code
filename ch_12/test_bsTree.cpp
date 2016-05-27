#include "bsTree.h"
#include <time.h>

int main()
{
    bsTree<int> tree;
    srand((int)time(0));
    for (int i = 14; i > 0; i--)
        tree.insert(rand()%14);

    tree.printTree();
    std::cout << std::endl;
    tree.draw();
    std::cout << "max element: " << tree.findMax() << std::endl;
    std::cout << "min element: " << tree.findMin() << std::endl;
    tree.remove(5);
    tree.printTree();
    std::cout << std::endl;
}
