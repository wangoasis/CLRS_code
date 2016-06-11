#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H

#include <string>
using std::string;
#include <utility>
using std::pair;

struct Tree_node
{
    string chars;
    double probability;
    struct Tree_node * left;
    struct Tree_node * right;

    Tree_node(string s, double p)
    : chars(s), 
      probability(p),
      left(NULL),
      right(NULL)
    { }

    Tree_node(pair<string, double> & p)
    : chars(p.first), 
      probability(p.second),
      left(NULL),
      right(NULL)
    { }

    Tree_node(Tree_node *n1, Tree_node *n2)
    : chars(n1->chars + n2->chars),
      probability(n1->probability + n2->probability),
      left(n1),
      right(n2)
    { }

};

struct comp_by_probability
{
    bool operator() (Tree_node * left, Tree_node * right)
    {
        return left->probability < right->probability;
    }
};

#endif
