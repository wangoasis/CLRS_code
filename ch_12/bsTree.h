/*
    c++ implementation of binary search tree
    &&
    exercise 12.1-3
    give a nonrecursive algorithm that performs an inorder tree walk
    solution: function printTreeNonRecur
*/
#ifndef bsTree_H
#define bsTree_H
#include <stdio.h>
#include <iostream>
#include <stack>
#include <iomanip>
using std::stack;
using std::ostream;

template <typename Comparable>
class bsTree 
{
public:
    bsTree () 
    : root(NULL)
    { }

    ~bsTree () {
        makeEmpty();
    }

    const Comparable & findMax () const 
    {
        binaryNode* node = findMax(root);
        return node->data;
    }

    const Comparable & findMin () const 
    {
        binaryNode* node = findMin(root);
        return node->data;
    }

    bool contains(const Comparable & x) const 
    {
        return contains(x, root);
    }

    bool isEmpty() const 
    {
        return root == NULL;
    }

    void printTree (ostream & out = std::cout) const 
    {
        if(isEmpty())
            out << "empty tree!" << std::endl;
        else 
//            printTree(root, out);
            printTreeNonRecur(root, out);
    }

    void makeEmpty() 
    {
        makeEmpty(root);
    }

    void insert(const Comparable & x) 
    {
        insert(x, root);
    }

    void remove(const Comparable & x)
    {
        remove(x, root);
    }

    void draw(ostream & out = std::cout) const
    {
        draw(out, 0, root);
    }

private:
    struct binaryNode
    {
        Comparable data;
        binaryNode* left;
        binaryNode* right;

        binaryNode(const Comparable & x, binaryNode* l, binaryNode* r)
        : data(x), left(l), right(r) 
        {}
    };

    binaryNode* root;

    void insert(const Comparable & x, binaryNode * & node)
    {
        if(node == NULL)
            node = new binaryNode(x, NULL, NULL);
        else if(x < node->data)
            insert(x, node->left);
        else if(x > node->data)
            insert(x, node->right);
        else ;
    }

    void remove(const Comparable & x, binaryNode * & node) 
    {
        if(node == NULL)
        {
            std::cerr << "do not exists in the tree" << std::endl;
            return;
        }
        if(x < node->data)
            remove(x, node->left);
        else if(x > node->data)
            remove(x, node->right);
        else if(node->left != NULL && node->right != NULL) 
        {
            node->data = findMin(node->right)->data;
            remove(node->data, node->right);
        }
        else 
        { 
            binaryNode* old = node;
            node = node->left != NULL ? node->left : node->right;
            delete old;
        }
    }

    binaryNode* findMin(binaryNode* node) const 
    {
        if(node == NULL)
            return NULL;
        if(node->left == NULL)
            return node;
        return findMin(node->left);
    }

    binaryNode* findMax(binaryNode* node) const 
    {
        if(node == NULL)
            return NULL;
        if(node->right == NULL)
            return node;
        return findMax(node->right);
    }

    bool contains(const Comparable & x, binaryNode* node) const 
    {
        if(node == NULL)
            return false;
        if(x < node->data)
            return contains(x, node->left);
        else if(x > node->data)
            return contains(x, node->right);
        else
            return true;
    }

    void makeEmpty(binaryNode* & node) 
    {
        if(node != NULL) 
        {
            makeEmpty(node->left);
            makeEmpty(node->right);
            delete node;
        }
        node = NULL;
    }

    void printTree(binaryNode* node, ostream & out) const 
    {
        if(node != NULL) 
        {
            printTree(node->left, out);
            out << node->data << " ";
            printTree(node->right, out);
        }
    }

    // nonrecursive algorithm for inOrder tree walking
    void printTreeNonRecur(binaryNode* node, ostream & out) const
    {
        stack<binaryNode*> s;
        binaryNode *p = node;
        while (p != NULL || !s.empty())
        {
            while (p)
            {
                s.push(p);
                p = p->left;
            }
            p = s.top();
            s.pop(); 
            out << p->data << " ";
            p = p->right;
        }
    }

    void draw(ostream & out, int indent, binaryNode* node) const
    {
        if (node != NULL)
        {
            draw(out, indent + 4, node->right);
            out << std::setw(indent) << " " << node->data << std::endl;
            draw(out, indent + 4, node->left);
        }
    }
};
#endif
