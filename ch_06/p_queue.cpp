#include "p_queue.h"

p_queue::p_queue(int array[], int length) {

    for (int i = 0; i < length; i++) {
        
        a[i] = array[i];
    }
    heapsize = length;
    build_maxheap(a, heapsize);
}

void p_queue::build_maxheap(int array[], int length) {
    
    for (int i = length / 2 - 1; i >= 0; i--)
        // the last non-leaf node is length/2-1 
        max_heapify(array, length, i);
}

void p_queue::max_heapify(int array[], int length, int i) {
    
    int left = left_child(i);
    int right = right_child(i);
    int largest = i;

    if (left < length && array[i] < array[left])
        largest = left;
    if (right < length && array[largest] < array[right])
        largest = right;

    if (largest != i) {
        
        std::swap(array[i], array[largest]);
        max_heapify(array, length, largest);
    }
}

int p_queue::left_child(int i) {
    
    return 2 * i + 1;
}

int p_queue::right_child(int i) {
    
    return 2 * i + 2;
}

int p_queue::parent(int i) {
    
    return (i - 1) / 2;
}

void p_queue::heapsort(int array[], int length) {
    
    build_maxheap(array, length);
    for (int i = length - 1; i >= 1; i--) {
        
        std::swap(array[0], array[i]);
        max_heapify(array, --length, 0);
    }
}

int p_queue::heap_max() {
    
    return a[0];
}

int p_queue::heap_extract_max() {
    
    if (heapsize <= 0) {
        
        std::cerr << "heapsize <= 0" << std::endl;
        return -1;
    }

    int max = a[0];
    std::swap(a[0], a[heapsize - 1]);
    max_heapify(a, heapsize - 1, 0);

    return max;
}

void p_queue::insert(int x) {

    heapsize++;
    a[heapsize-1] = x;
    
    int i = heapsize - 1;
    while (i > 0 && a[parent(i)] < a[i]) {
        
        std::swap(a[parent(i)], a[i]);
        i = parent(i);   
    }
}

