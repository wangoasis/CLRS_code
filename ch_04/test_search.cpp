#include "searchMaxSub.h"
#include <iostream>

int main() 
{
    
    vector<int> a {20, -1, -5, -9, 16, -100};
    searchMaxSub s; 
    std::cout << s.findMaxSub1(a) << std::endl;
    std::cout << s.findMaxSub2(a) << std::endl;
    std::cout << s.findMaxSub3(a) << std::endl;
    std::cout << s.findMaxSub4(a) << std::endl;
}
