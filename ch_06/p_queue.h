#ifndef _P_QUEUE_H
#define _P_QUEUE_H

#include <iostream>

class p_queue {

public:
    p_queue(int array[], int length);
    void insert(int x);
    int heap_max(void);
    int heap_extract_max(void);

private:
    int a[10000];
    int heapsize;
    
    int parent(int i);
    int left_child(int i);
    int right_child(int i);
    void max_heapify(int array[], int length, int i);
    void build_maxheap(int array[], int length);
    void heapsort(int array[], int length);
       
};

#endif
