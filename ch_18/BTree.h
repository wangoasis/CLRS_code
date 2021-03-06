#ifndef _BTREE_H
#define _BTREE_H

#include <iostream>
#include <utility>
using std::pair;
#include <stack>
using std::stack;

// #define _DISK_MODE

template <typename T>
class BTree
{
private:
    static const int t = 3;

    struct Node
    {
        bool is_leaf;
        int n; // number of keys
        T key_values[2 * t]; // meaningful key_value: index 1 to 2t - 1
        struct Node* children[2 * t + 1]; // meaningful children: index 1 to 2t

        Node(bool b = true, int n1 = 0)
        : is_leaf(b), n(n1)
        { }
    };
    
    Node* root; // root of B-tree

public:

    BTree()
    {
        root = allocate_node();
#ifdef _DISK_MODE
        disk_write(root);
#endif
    }

    ~BTree()
    {
        destroy(root);
    }

    void print_tree() const 
    {
        print_tree(root, 0);
    }

    const T & find_min() const
    {
        return find_min(root);
    }

    const T & find_max() const
    {
        return find_max(root);
    }

    void insert(const T & value)
    {
        if (root->n < 2 * t - 1)
            insert_nonfull(root, value);
        else // root is full
        {
            Node* s = allocate_node();
            s->is_leaf = false;
            s->n = 0;
            s->children[1] = root;
            root = s;
            split_child(s, 1);
            insert_nonfull(root, value);
        }
    }

    void remove(const T & value)
    {
        remove(root, value);
    }

    bool exists(const T & value) const
    {
        return exists(value, root);
    }

    const T & predecessor(const T & value) 
    {
        pair<Node*, int> p = search(root, value);
        if (p.first == NULL)
        {
            std::cout << "value does not exist in tree, no predecessor" << std::endl;
            return -1;
        }
        return predecessor(p.first, p.second);
    }

private:
    Node* allocate_node()
    {
        Node* node = new Node();
#ifdef _DISK_MODE
        std::cout << "allocate a node" << std::endl;
#endif
        return node;
    }

    void disk_write(Node* node) const
    {
        std::cout << "write to disk" << std::endl;
    }

    void disk_read(Node* node) const
    {
        std::cout << "read from disk" << std::endl;
    }

    const T & find_min(Node* node) const
    {
        if (node == NULL)
            return -1;
        else if (node->is_leaf)
            return node->key_values[1];
        else
        {
#ifdef _DISK_MODE
            disk_read(node->children[1]);
#endif
            return find_min(node->children[1]);
        }
    }

    const T & find_max(Node* node) const
    {
        if (node == NULL)
            return -1;
        else if (node->is_leaf)
            return node->key_values[node->n];
        else
        {
#ifdef _DISK_MODE
            disk_read(node->children[node->n + 1]);
#endif
            return find_max(node->children[node->n + 1]);
        }
    }

    bool exists(const T & value, Node* node) const
    {
        if (node != NULL)
        {
            int i = 1;
            while (i <= node->n && value > node->key_values[i])
                i++;
            if (i <= node->n && value == node->key_values[i])
                // value is in node
                return true; 
            else if (node->is_leaf)
                return false;
            else
            {
#ifdef _DISK_MODE
                disk_read(node->children[i]);
#endif
                return exists(value, node->children[i]);
            }
        }
        else
            return false;
    }

    void destroy(Node* node)
    {
        if (node != NULL)
        {
            if (!node->is_leaf)
            {
                for (int i = 1; i <= node->n + 1; i++)
                    destroy(node->children[i]);
            }
            delete node;
        }
    }

    void print_tree(Node* node, int height) const
    {
        if (node != NULL)
        {
            std::cout << "height: " << height << std::endl;
            for (int i = 1; i <= node->n; i++)
                std::cout << node->key_values[i] << " ";
            std::cout << std::endl;
            if (!node->is_leaf)
            {
                for (int i = 1; i <= node->n + 1; i++)
                    print_tree(node->children[i], height + 1);
            }
        }
    }

    // split the ith child of node, the number of key_values of ith child
    // is 2*t-1
    void split_child(Node* & x, int i)
    {
        Node* y = x->children[i];
        Node* z = allocate_node(); // new node
        z->is_leaf = y->is_leaf;
        z->n = t - 1;

        // copy key value
        for (int j = t + 1; j <= 2 * t - 1; j++)
            z->key_values[j - t] = y->key_values[j];
        // copy children
        if (!y->is_leaf)
        {
            for (int j = t + 1; j <= 2 * t; j++)
                z->children[j - t] = y->children[j];
        }
        y->n = t - 1;

        // insert a key value to node x
        for ( int j = x->n + 1; j >= i; j--)
            x->key_values[j + 1] = x->key_values[j];
        x->key_values[i] = y->key_values[t];
        // insert a child to node x
        for (int j = x->n + 1; j >= i + 1; j--)
            x->children[j + 1] = x->children[j];
        x->children[i + 1] = z;
        x->n++;

#ifdef _DISK_MODE
        disk_write(y);
        disk_write(z);
        disk_write(x);
#endif
    }

    // insert a value to a nonfull node
    void insert_nonfull(Node* & x, const T & value)
    {
        if (x->is_leaf)
        {
            int i = x->n;
            while (i >= 1 && value < x->key_values[i])
            {
                x->key_values[i + 1] = x->key_values[i];
                i--;
            }
            if (x->key_values[i] == value)
            {
                std::cout << value << " already exists in B tree" << std::endl;
                return;
            }
            x->key_values[i + 1] = value;
            x->n++;
#ifdef _DISK_MODE
            disk_write(x);
#endif
        }
        else // x is an internal node
        {
            int i = 1;
            while (i <= x->n && value > x->key_values[i])
                i++;
            if (value == x->key_values[i])
            {
                std::cout << value << " already exists in B tree" << std::endl;
                return;
            }
#ifdef _DISK_MODE
            disk_read(x->children[i]);
#endif
            if (x->children[i]->n == 2 * t - 1)
            {
                split_child(x, i);
                if (value > x->key_values[i])
                    i++;
            }
            insert_nonfull(x->children[i], value);
        }
    }

    // find the predecessor of the ith key value of node x
    const T & predecessor(Node* x, int i)
    {
        if (!x->is_leaf)
        {
#ifdef _DISK_MODE
            disk_read(x->children[i]);
#endif
            return find_max(x->children[i]);
        }
        else if(i > 1)
            return x->key_values[i - 1];
        else // x is a leaf, and i == 1
        {
            stack<Node*> s;
            T value = x->key_values[1];
            path(root, value, s);

            while (true)
            {
                if (s.empty())
                {
                    std::cout << "no predecessor" << std::endl;
                    return -1;
                }

                Node* y = s.top();
                s.pop();
                int i = 1;
#ifdef _DISK_MODE
                disk_read(y->children[1]);
#endif
                while (y->children[i] != x)
                {
                    i++;
#ifdef _DISK_MODE
                    disk_read(y->children[i]);
#endif
                }
                if (i != 1)
                    return y->key_values[i - 1];
                else
                    x = y;
            }
        }
    }

    void path(Node* x, const T & value, stack<Node*> & s)
    {
        int i = 1; 
        while (i <= x->n && value > x->key_values[i])
            i++;
        if (i <= x->n && value == x->key_values[i])
            // value is in node x
            return;
        if (x->is_leaf)
            return;
        else
        {
#ifdef _DISK_MODE
            disk_read(x->children[i]);
#endif
            s.push(x);
            path(x->children[i], value, s);
        }
    }

    // return: Node* x, int i
    // value is the ith key value of Node
    pair<Node*, int> search(Node* node, const T & value) const
    {
        if (node == NULL)
            return std::make_pair(nullptr, -1);
        int i = 1;
        while (i <= node->n && value > node->key_values[i])
            i++;
        if (i <= node->n && value == node->key_values[i])
            return std::make_pair(node, i);
        else if (node->is_leaf)
            return std::make_pair(nullptr, -1);
        else 
            return search(node->children[i], value);  
    }

    void remove(Node* & x, const T & value)
    {
        int i = 1;
        while (i <= x->n && value > x->key_values[i])
            i++;
        if (i <= x->n && value == x->key_values[i]) // value is in node x
        {
            if (x->is_leaf) // x is a leaf node
            {
                for (int j = i + 1; j <= x->n; j++)
                    x->key_values[j - 1] = x->key_values[j];
                x->n--;
                return;
            }
            else // x is a internal node
            {
                Node* prev_child = x->children[i];
                Node* next_child = x->children[i + 1];

                if (prev_child->n >= t)
                {
                    // get the predecessor of key_value: value
                    T prev_key = pre_key_value(prev_child);
                    remove(prev_child, prev_key);
                    x->key_values[i] = prev_key;
                    return;
                }
                else if(next_child->n >= t)
                {
                    // get the successor of key_value: value
                    T next_key = suc_key_value(next_child);
                    remove(next_child, next_key);
                    x->key_values[i] = next_key;
                    return;
                }
                else 
                {
                    merge_child(x, i);
                    remove(prev_child, value);
                }
            }
        }
        else // value is not in node x
        {
            // value is in sub-tree of root x->children[i]
            Node* root2 = x->children[i];
            if (root2->n == t - 1)
            {   
                Node* root2_left = i > 1 ? x->children[i - 1] : nullptr;
                Node* root2_right = i <= x->n ? x->children[i + 1] : nullptr;
                if (root2_left && root2_left->n >= t)
                {
                    // move down x->key_values[i-1]
                    for (int j = root2->n; j >= 1; j--)
                        root2->key_values[j + 1] = root2->key_values[j];
                    root2->key_values[1] = x->key_values[i - 1];

                    // move children
                    if (!root2->is_leaf)
                    {   
                        for (int j = root2->n + 1; j >= 1; j--)
                            root2->children[j + 1] = root2->children[j];
                        root2->children[1] = root2_left->children[root2_left->n + 1];
                    }

                    root2->n++;
                    x->key_values[i - 1] = root2_left->key_values[root2_left->n];
                    root2_left->n--;
                }
                else if (root2_right && root2_right->n >= t)
                {
                    // move down x->key_values[i]
                    root2->key_values[root2->n + 1] = x->key_values[i];
                    root2->n++;
                    x->key_values[i] = root2_right->key_values[1];
                    root2_right->n--;

                    // move key_values
                    for (int j = 1; j <= root2_right->n; j++)
                        root2_right->key_values[j] = root2_right->key_values[j + 1];

                    // move children
                    if (!root2->is_leaf)
                    {   
                        root2->children[root2->n + 1] = root2_right->children[1];
                        for (int j = 1; j <= root2_right->n + 1; j++)
                            root2_right->children[j] = root2_right->children[j + 1];
                    }
                }
                // root2_left and root2_right both have t-1 key_values
                else if (root2_left)
                {
                    merge_child(x, i - 1);
                    root2 = root2_left;
                }
                else if (root2_right)
                    merge_child(x, i);
            }
            remove(root2, value);
        }
    }

    // x->children[i] and x->children[i+1] both have t - 1 key-values
    // this method merge this two children, and move x->key_values[i]
    // to the merged children. Therefore, the merged chlldren has
    // 2*t-1 key-values
    void merge_child(Node* & x, int i)
    {
        Node* prev_child = x->children[i];
        Node* next_child = x->children[i + 1];

        prev_child->n = 2 * t - 1;
        // move down x->key_values[i]
        prev_child->key_values[t] = x->key_values[i];

        // copy key_values
        for (int j = t + 1; j <= 2 * t - 1; j++)
            prev_child->key_values[j] = next_child->key_values[j - t];
        // copy children
        if (!prev_child->is_leaf)
        {
            for (int j = t + 1; j <= 2 * t; j++)
                prev_child->children[j] = next_child->children[j - t];
        }

        // delete key_value and child in node x
        for (int j = i + 1; j <= x->n; j++)
        {
            x->key_values[j - 1] = x->key_values[j];
            x->children[j] = x->children[j + 1];
        }
        x->n--;

        delete next_child;
        if (x->n == 0)
            delete x;
    }

    // Node x is the node before a key value
    // this method finds the predecessor
    T pre_key_value(Node* x)
    {
        while (!x->is_leaf)
            x = x->children[x->n + 1];
        return x->key_values[x->n];
    }

    // Node x is the node after a key value
    // this method finds the successor
    T suc_key_value(Node* x)
    {
        while (!x->is_leaf)
            x = x->children[1];
        return x->key_values[1];
    }
};

#endif
