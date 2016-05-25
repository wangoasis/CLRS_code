/*
    show how to implement a queue using two stacks
*/

#include <iostream>
#include <stack>
using std::stack;

class Queue 
{
public:
    void enqueue(int x)
    {
        s1.push(x);
    }

    int dequeue()
    {
        if (s1.size() == 0)
        {
            std::cerr << "empty queue" << std::endl;
            return -1;
        }

        while (s1.size() != 1)
        {
            s2.push(s1.top());
            s1.pop();
        }

        int x = s1.top();
        s1.pop();

        while (!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }

        return x;
    }

    void print_queue()
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        while (!s2.empty())
        {
            std::cout << s2.top() << " ";
            s1.push(s2.top());
            s2.pop();
        }
    }

private:
    stack<int> s1;
    stack<int> s2;
};

int main()
{
    Queue q;
    for (int i = 0; i < 10; i++)
        q.enqueue(i);
    q.print_queue();
    std::cout << std::endl;
    q.dequeue();
    q.print_queue();
    std::cout << std::endl;
    q.enqueue(19);
    q.print_queue();
    std::cout << std::endl;
}
