#include "Huffman.h"
#include <iostream>

int main()
{
    map<string, double> chars;
    chars["A"] = 0.2;
    chars["B"] = 0.25;
    chars["C"] = 0.1;
    chars["D"] = 0.15;
    chars["E"] = 0.3;

    Huffman* h = new Huffman(chars);
    h->print_code_table();
    std::cout << h->encode("ACABDEBC") << std::endl;
    std::cout << h->decode("0010000011011101100") << std::endl;
}
