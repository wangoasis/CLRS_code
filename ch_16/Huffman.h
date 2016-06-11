#ifndef _HUFFMAN
#define _HUFFMAN

#include "huffman_tree.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;

class Huffman
{
public:
    Huffman(map<string, double> &);
    
    // encode an input character string to huffman codes
    string encode(const string &);
    // decode an input huffman codes string to character string
    string decode(const string &);
   
    // print char with its huffman code 
    void print_code_table();
    ~Huffman();

private:
    void build_huffman(map<string, double> &);
    void build_encode_table(string, Tree_node *);
    void build_decode_table();
    void print_tree(Tree_node *);
    void destroy(Tree_node *);
    
    // key: char, value: huffman code
    map<string, string> encode_table;
    // key: huffman code, value: char
    map<string, string> decode_table;
    // root of huffman tree
    Tree_node* root;
};

#endif
