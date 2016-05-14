#include <vector>
using std::vector;
#include <iostream>

template <typename T>
void merge(vector<T> &array, typename vector<T>::size_type left, typename vector<T>::size_type mid, typename vector<T>::size_type right ) {

    vector<T> L , R;
    for(auto i = left; i <= mid; i++)
        L.push_back(array[i]);
    for(auto i = mid+1; i <= right; i++)
        R.push_back(array[i]);
    
    int i = 0, j = 0;
    for(auto k = left; k <= right; ) {
        if(L[i] < R[j]) {
            array[k++] = L[i++];
            if(i == L.size()) {
                while(j < R.size())
                    array[k++] = R[j++];
            }
        } else {
            array[k++] = R[j++];
            if(j == R.size()) {
                while(i < L.size())
                    array[k++] = L[i++];
            }
        }
    }
}

template <typename T>
void mergeSort(vector<T> &array, typename vector<T>::size_type left, typename vector<T>::size_type right) {

    if(left < right) {
        auto mid = (left + right) / 2;
        mergeSort(array, 0, mid);
        mergeSort(array, mid+1, right);
        merge(array, left, mid, right);
    }
}


int main () {

    vector<int> vec {5,3,2,6,7,5,1};
    mergeSort(vec, 0, vec.size()-1);
    for(auto &a : vec) 
        std::cout << a << " ";
    std::cout << std::endl;
}
