#include <vector>
using std::vector;
#include <iostream>

// O(N^2)
template <typename T>
void insertSort(vector<T> &array) {

    typedef typename vector<T>::size_type size_type;
    for(size_type i = 1; i != array.size(); i++) {
        auto key = array[i];
        auto j = i - 1;
        while(j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int main () {
    
    vector<int> vec {4,3,1,2,6,9,7};
    insertSort(vec);
    for(auto &a : vec)
        std::cout << a << " ";
    std::cout << std::endl;
}
