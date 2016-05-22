/*
    exercise 9.1-1:
    show that the second smallest of n elements can be found with 
    n + ceil(lgn) - 2 comparisons in the worst case
*/

#include <queue>
#include <climits>
#include <iostream>
using std::queue;
#include <time.h>
#include <stdlib.h>
#define random(x) (rand()%x)

struct Node
{
    int value;
    bool child; // 0 means left child is smaller 
    struct Node* left;
    struct Node* right;

    Node(int v, bool c)
    : value(v), child(c), left(nullptr), right(nullptr)
    {
    }
};

int second_smallest(int a[], int length)
{
    queue<Node*> q;
    for (int i = 0; i < length; i++)
    {
        Node* node = new Node(a[i], 0);
        q.push(node);
    }

    Node* root;
    while (!q.empty())
    {
        if (q.size() == 1)
        {
            root = q.front();
            break;
        }
        for (int i = 0; i < q.size(); i += 2) 
        {
            if (i == q.size() - 1)
            {
                Node* node = q.front();
                q.pop();
                q.push(node);
                break;
            }
            else
            {
                Node* node1 = q.front();
                q.pop();
                Node* node2 = q.front();
                q.pop();

                Node* new_node;
                if (node1->value <= node2->value)
                    new_node = new Node(node1->value, false);
                else
                    new_node = new Node(node2->value, true);

                new_node->left = node1;
                new_node->right = node2;
                q.push(new_node);
            }
        }
    }

    int second_smallest_num(root->child ? root->left->value : root->right->value);
    root = root->child ? root->right : root->left;
    while (root)
    {
        if (root->left && root->right)
        {
            if (root->child)
            {
                second_smallest_num = root->left->value < second_smallest_num ? root->left->value : second_smallest_num;
                root = root->right;
            }
            else
            {
                second_smallest_num = root->right->value < second_smallest_num ? root->right->value : second_smallest_num;
                root = root->left;
            }
        }
        else
            break;
    }

    return second_smallest_num;
}

int partition(int a[], int start, int end)
{
    int pivot = a[end];
    int i = start - 1;

    for (int j = start; j < end; j++)
        if (a[j] <= pivot)
            std::swap(a[j], a[++i]);
    std::swap(a[++i], a[end]);
    return i;
}

void quicksort(int a[], int start, int end)
{
    if (start < end)
    {
        int p = partition(a, start, end);
        quicksort(a, start, p - 1);
        quicksort(a, p + 1, end);
    }
}

int main()
{
    int length = 20;
    int a[length];

    srand((int)time(0));
    for (int i = 0; i < length; i++)
        a[i] = random(50);
    for (int i = 0; i < length; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    std::cout << "second smallest: " << second_smallest(a, length) << std::endl;    

    quicksort(a, 0, length - 1);
    for (int i = 0; i < length; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}
