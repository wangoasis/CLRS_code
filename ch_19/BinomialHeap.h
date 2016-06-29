#include "BinomialNode.h"
#include <iostream>

template <typename T>
class BinomialHeap
{
private:
    BinomialNode<T> *root;

public:
    BinomialHeap()
    : root(nullptr)
    { }

    BinomialHeap(BinomialNode<T>* & node)
    : root(node)
    { }

    void insert(T value)
    {
        BinomialNode<T>* node = new BinomialNode<T>(value);
        if (node == nullptr)
            return;
        root = combine(root, node);  
    }

    void extract_min()
    {
        BinomialNode<int>* min_node = root;
        BinomialNode<int>* prev_min_node = nullptr;
        T element = root->key;
        BinomialNode<int>* node = root->next_sibling;
        BinomialNode<int>* node2 = root;

        // find the minimum node
        while (node != nullptr)
        {
            if (node->key < element)
            {
                min_node = node;
                prev_min_node = node2;
            }
            node = node->next_sibling;
            node2 = node2->next_sibling;
        }
        prev_min_node->next_sibling = min_node->next_sibling;

        // reverse the children list of the minimum node
        node = min_node->first_child;
        BinomialNode<int>* prev = nullptr;
        BinomialNode<int>* temp = nullptr;
        while (node != nullptr)
        {
            node->parent = nullptr;
            temp = node->next_sibling;
            node->next_sibling = prev;
            prev = node;
            node = temp;
        }
        root = combine(root, prev);
    }

    T find_min() const
    {
        BinomialNode<T>* node = root;
        if (node != nullptr)
        {
            T element = node->key;
            node = node->next_sibling;
            while (node != nullptr)
            {
                if (node->key < element)
                    element = node->key;
                node = node->next_sibling;
            }

            return element;
        }
        else
        {
            return -1;
        }
    }


private:
    BinomialNode<T>* combine(BinomialNode<T>* & h1, BinomialNode<T>* & h2)
    {
        // merge two list of roots
        BinomialNode<T>* new_root = merge_root(h1, h2);
        if (new_root == nullptr)
            return nullptr;

        BinomialNode<T>* x = new_root;
        BinomialNode<T>* prev_x = nullptr;
        BinomialNode<T>* next_x = x->next_sibling;

        while (next_x != nullptr)
        {
            if (x->degree != next_x->degree 
                || 
                ( next_x->next_sibling != nullptr 
                  && 
                  x->degree == next_x->next_sibling->degree) )
            {
                prev_x = x;
                x = next_x;
                next_x = x->next_sibling;
            }
            else if (x->key <= next_x->key)
            {
                x->next_sibling = next_x->next_sibling;
                combine_equal_tree(x, next_x);
                next_x = x->next_sibling;
            }
            else
            {
                if (prev_x == nullptr)
                    new_root = next_x;
                else
                    prev_x->next_sibling = next_x;
                combine_equal_tree(next_x, x);
                x = next_x;
                next_x = x->next_sibling;
            }
        }
        return new_root;
    }

    // node1->key <= node2->key
    void combine_equal_tree(BinomialNode<T>* & node1, BinomialNode<T>* & node2)
    {
        node2->parent = node1;
        node2->next_sibling = node1->first_child;
        node1->first_child = node2;
        node1->degree++;
    }

    // merge and sort roots of h1 and h2
    BinomialNode<T>* merge_root(BinomialNode<T>* & h1, BinomialNode<T>* & h2)
    {
        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;

        BinomialNode<T>* new_root;
        BinomialNode<T>* node;
        BinomialNode<T>* root1 = h1;
        BinomialNode<T>* root2 = h2;
        if (h1->degree <= h2->degree)
        {
            new_root = h1;
            root1 = root1->next_sibling;
        }
        else
        {
            new_root = h2;
            root2 = root2->next_sibling;
        }
        node = new_root;
        while (root1 && root2)
        {
            if (root1->degree <= root2->degree)
            {
                node->next_sibling = root1;
                root1 = root1->next_sibling;
            }
            else
            {
                node->next_sibling = root2;
                root2 = root2->next_sibling;
            }
            node = node->next_sibling;
        }
        if (root1)
            node->next_sibling = root1;
        else
            node->next_sibling = root2;
        return new_root;
    }
};
