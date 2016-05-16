#include "young_matrix.h"
#include <iostream>

int main()
{
    young_matrix young;
    std::cout << young.min_element() << std::endl;
    std::cout << young.extract_min_element() << std::endl;
    young.print_matrix();
    young.insert(1);
    young.print_matrix();
    std::cout << young.min_element() << std::endl;
    std::cout << young.exist_element(14) << std::endl;
}
