#include "Huffman.h"

#include <iostream>
#include <algorithm>

//#define _DEBUG_MODE

Huffman::Huffman(map<string, double> & p)
{
    build_huffman(p);
    build_encode_table("", root);
    build_decode_table();
}

string Huffman::encode(const string & s)
{
    string res = "";
    for (auto i = 0; i != s.size(); i++)
    {
        string tmp = "";
        tmp.insert(tmp.begin(), s[i]);
        res += encode_table[tmp];
    }
    return res;
}

string Huffman::decode(const string & s)
{
    string res = "";
    string tmp = "";
    for (auto i = 0; i != s.size(); i++)
    {
        tmp.insert(tmp.end(), s[i]);
        if (decode_table.find(tmp) != decode_table.end())
        {
            // some continuous number exists in the decode_table 
            // thus it can be seen as the huffman_code
            res += decode_table[tmp];

            // make tmp empty
            tmp = "";
        }
    }
    return res;
}

Huffman::~Huffman()
{
    if (root != NULL)
    {
        destroy(root);
    }
    root = NULL;
}

void Huffman::destroy(Tree_node* node)
{
    if (node->left != NULL)
        destroy(node->left);
    if (node->right != NULL)
        destroy(node->right);
    delete node;
}

void Huffman::print_code_table()
{
    for (auto iter = encode_table.cbegin(); iter != encode_table.cend(); ++iter)
        std::cout << (*iter).first << " " << (*iter).second << std::endl;
    std::cout << std::endl;
}

void Huffman::build_huffman(map<string, double> & p)
{
    vector<Tree_node*> v;
    
    for(auto iter = p.begin(); iter != p.end(); iter++)
        v.push_back(new Tree_node(iter->first, iter->second));

    // sort by probability
    sort(v.begin(), v.end(), comp_by_probability());

    #ifdef _DEBUG_MODE
    std::cout << "after sorting" << std::endl;
    for (auto iter = v.begin(); iter != v.end(); iter++)
        std::cout << (*iter)->chars << " " << (*iter)->probability << std::endl;
    std::cout << std::endl;
    #endif

    while (v.size() != 1)
    {
        // v[0] and v[1] is twos nodes of the least probability
        Tree_node* node2 = new Tree_node(v[0], v[1]);

        auto iter = v.begin();
        iter = v.erase(iter);
        v.erase(iter);

        v.push_back(node2);
        sort(v.begin(), v.end(), comp_by_probability());

        #ifdef _DEBUG_MODE
        for (auto iter = v.begin(); iter != v.end(); iter++)
            std::cout << (*iter)->chars << " " << (*iter)->probability << std::endl;
        std::cout << std::endl;
        #endif
    }

    root = v[0];

    #ifdef _DEBUG_MODE
    print_tree(root);
    std::cout << std::endl;
    #endif
}

void Huffman::print_tree(Tree_node* node)
{
    if (node != NULL)
    {  
        std::cout << node->chars << " "; 
        print_tree(node->left);
        print_tree(node->right);
    }
}

void Huffman::build_encode_table(string s, Tree_node* node)
{
    if (node != NULL)
    {
        if (node->left == NULL && node->right == NULL)
        {
            encode_table.insert(std::make_pair(node->chars, s));
            delete node;
        }
        else
        {
            build_encode_table(s + "0", node->left);
            build_encode_table(s + "1", node->right);
        }
    }
}

void Huffman::build_decode_table()
{
    for (auto iter = encode_table.cbegin(); iter != encode_table.cend(); iter++) 
        decode_table.insert(std::make_pair(iter->second, iter->first));
}
