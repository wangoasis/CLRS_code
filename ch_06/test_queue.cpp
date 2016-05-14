#include "p_queue.h"

int main() {

    int a[6] = { 3, 4, 2, 1, 5, 7};
    p_queue q(a, 6);
    std::cout << " heap max: " << q.heap_max() << std::endl;
    q.insert(9);
    std::cout << " heap max: " << q.heap_extract_max() << std::endl;
    std::cout << " heap max: " << q.heap_max() << std::endl;
}
