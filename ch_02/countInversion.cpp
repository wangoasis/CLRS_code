#include <vector>
using std::vector;
#include <iostream>

template <typename T>
int mergeInversion(vector<T> &array, typename vector<T>::size_type left, typename vector<T>::size_type mid, typename vector<T>::size_type right) {
    
    int inversion = 0;
    if(mid < right) {
        vector<T> L, R;
        for(auto i = left; i <= mid; i++)
            L.push_back(array[i]);
        for(auto i = mid+1; i <= right; i++)
            R.push_back(array[i]);
        
        bool counted = false;
        int i = 0, j = 0;
        for(auto k = left; k <= right; ) {
            if((!counted) && (L[i] > R[j])) {
                inversion += L.size() - i;
                counted = true;
            }
            if(L[i] <= R[j]) {
                array[k++] = L[i++];
                if(i == L.size()) 
                    while(j < R.size())
                        array[k++] = R[j++];
            } else {
                array[k++] = R[j++];
                if(j == R.size()) 
                    while(i < L.size())
                        array[k++] = L[i++];
                counted = false;
            }
        }
    }
    return inversion;
}

template <typename T>
int countInversion(vector<T> &array, typename vector<T>::size_type left, typename vector<T>::size_type right) {
    
    int inversion = 0;
    if(left < right) {
        auto mid = (left + right) / 2;
        inversion += countInversion(array, left, mid);
        inversion += countInversion(array, mid+1, right);
        inversion += mergeInversion(array, left, mid, right);
    }
    return inversion;
}


int main() {

    vector<int> vec {8,7,6,5,4,3,2,1,0};
    std::cout << countInversion(vec, 0, vec.size()-1) << std::endl;
    for(auto &a : vec)
        std::cout << a << " ";
    std::cout << std::endl;
}
