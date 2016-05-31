/* 
    problem 14.2
*/

#include <iostream>

struct Node
{
    int value;
    struct Node* next;

    Node(int i)
    : value(i) 
    { }
};

int main()
{
    int m, n;
    std::cout << "enter m: ";
    std::cin >> m; // num of people
    std::cout << "enter n: ";
    std::cin >> n;

    Node* first = new Node(1);
    Node* q = first;
    for (int i = 2; i <= m; i++)
    {
        Node* node = new Node(i);
        q->next = node;
        q = node; 
    }
    q->next = first;

    Node* p = first;
    for (int i = 0; i < m; i++)
    {
        for (int j = 1; j < n; j++, q = q->next, p = p->next);
        std::cout << p->value << " ";
        q->next = p->next;
        Node* old = p;
        p = p->next;
        delete old;
    }
    std::cout << std::endl;
}
