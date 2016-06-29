template <typename T>
class BinomialNode
{
public:
    T key;
    int degree;
    BinomialNode<T> *first_child;
    BinomialNode<T> *parent;
    BinomialNode<T> *next_sibling;

    BinomialNode(T value)
    : key(value), degree(0), 
      first_child(nullptr), 
      parent(nullptr),
      next_sibling(nullptr)
      { }
};
