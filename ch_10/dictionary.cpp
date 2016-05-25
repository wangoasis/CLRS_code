/*
    Implement the dictionary operations INSERT, DELETE and 
    SEARCH using singly linked, circular lists. 
*/

#include <iostream>

class Dict
{
private:
    struct Node
    {
        int value;
        struct Node* next;
    };
    Node* null_node; // sentinal node
    Node* head;

    void destroy_list()
    {
        Node* node = head->next;
        Node* next;
        while (node != null_node)
        {
            next = node->next;
            free(node);
            node = next;
        }
    }

public:
    Dict()
    {
        null_node = (Node*)malloc(sizeof(struct Node));
        head = (Node*)malloc(sizeof(struct Node));
        null_node->value = 0;
        null_node->next = null_node;
        head->value = 0;
        head->next = null_node;
    }

    ~Dict()
    {
        destroy_list();
    }

    void insert(int x)
    {
        Node* new_node = (Node*)malloc(sizeof(struct Node));
        new_node->value = x;
        new_node->next = head->next;
        head->next = new_node;
    }

    bool exists(int x)
    {
        Node* node = head->next;
        while (node != null_node && node->value != x)
            node = node->next;
        if (node != null_node)
            return true;
        else
            return false;
    }

    void del(int x)
    {
        Node* node = head->next;
        while (node->next != null_node)
        {
            if (node->next->value == x)
            {
                Node* node2 = node->next;
                node->next = node2->next;
                free(node2);
            }
            else
                node = node->next;
        }
    }

    void show()
    {
        Node* node = head->next;
        while (node != null_node)
        {
            std::cout << node->value << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }

};

int main()
{
    Dict dict;
    for (int i = 0; i < 10; i++)
        dict.insert(i);
    dict.show();
    std::cout << dict.exists(5) << std::endl; 
    std::cout << dict.exists(11) << std::endl; 
    dict.del(5);
    std::cout << dict.exists(5) << std::endl; 
    dict.show();
}
