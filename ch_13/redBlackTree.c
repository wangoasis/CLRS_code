#include "redBlackTree.h"
#include "fatal.h"
#include <stdlib.h>
#include <stdio.h>

#define infinity (30000)
#define negInfinity (-30000)

typedef enum colorType { red, black } colorType;

struct rbTreeNode {
    
    elementType element;
    struct rbTreeNode *parent;
    rbTree left;
    rbTree right;
    colorType color;
};

// sentinal node, take place of original NULL pointer 
static position nullNode = NULL; 

// initialization: nullNode, tree
// in this file, tree->right points to the real root of a tree
rbTree init(void) {
    
    if(nullNode == NULL) {
    
        nullNode = malloc(sizeof(struct rbTreeNode));
        if(nullNode == NULL)
            Error("out of space");
        nullNode->parent = nullNode;
        nullNode->left = nullNode->right = nullNode;
        nullNode->color = black; // most important quality of nullNode
        nullNode->element = infinity;
    }

    return nullNode;
}

void printTree(rbTree tree) {
    
    if(tree != nullNode) {
        
        printTree(tree->left);
        printf("%d, ", tree->element);
        printTree(tree->right);
    }
}

rbTree makeEmpty(rbTree tree) {
    
    if(tree != nullNode) {
        
        makeEmpty(tree->left);
        makeEmpty(tree->right);
        free(tree);
    }
    return nullNode;
}

position find(elementType value, rbTree tree) {

    if(tree == nullNode)
        return nullNode;
    if(value < tree->element)
        return find(value, tree->left);
    else if(value > tree->element)
        return find(value, tree->right);
    else 
        return tree;
}

position findMax(rbTree tree) {
    
    if(tree != nullNode) {
    
        while(tree->right != nullNode) 
            tree = tree->right;

        return tree;
    }

    return nullNode;
}

position findMin(rbTree tree) {
    
    if(tree != nullNode) {
    
        while(tree->left != nullNode) 
            tree = tree->left;

        return tree;
    }

    return nullNode;
}

elementType retrieve(position p) {
    
    return p->element;
}

static position singleRotateWithRight(position k1, rbTree *root) {
    
    position k2;
    k2 = k1->right;

    k1->right = k2->left;
    if(k2->left != nullNode)
        k2->left->parent = k1;

    k2->parent = k1->parent;
    if(k1->parent == nullNode)
        *root = k2;
    else if(k1 == k1->parent->left)
        k1->parent->left = k2;
    else 
        k1->parent->right = k2;
    k2->left = k1;

    k1->parent = k2;

    return k2;
}

static position singleRotateWithLeft(position k1, rbTree *root) {
    
    position k2;
    k2 = k1->left;

    k1->left = k2->right;
    if(k2->right != nullNode)
        k2->right->parent = k1;

    k2->parent = k1->parent;
    if(k1->parent == nullNode)
        *root = k2;
    else if(k1 == k1->parent->right)
        k1->parent->right = k2;
    else 
        k1->parent->left = k2;
    k2->right = k1;

    k1->parent = k2;

    return k2;
}

static rbTree rbInsertFixup(position node, rbTree tree) {

    while(node->parent->color == red) {
        
        if(node->parent == node->parent->parent->left) {
            
            position node2 = node->parent->parent->right; // uncle
            if(node2->color == red) {
                
                node->parent->color = black;                     // case 1
                node2->color = black;                            // case 1
                node->parent->parent->color = red;              // case 1
                node = node->parent->parent;                     // case 1
            } else { // node2->color == black

                if(node == node->parent->right) {                // case 2
                    node = node->parent;                         // case 2
                    node = singleRotateWithRight(node, &tree)->left;    // case 2
                }                                                // case 2
                node->parent->color = black;                     // case 3
                node->parent->parent->color = red;               // case 3
                node = singleRotateWithLeft(node->parent->parent, &tree)->left;         // case 3
            }
        }
        else {
            
            position node2 = node->parent->parent->left; // uncle
            if(node2->color == red) {
                
                node->parent->color = black;                     // case 1
                node2->color = black;                            // case 1
                node->parent->parent->color = red;              // case 1
                node = node->parent->parent;                     // case 1
            } else { // node2->color == black

                if(node == node->parent->left) {                 // case 2
                    node = node->parent;                         // case 2
                    node = singleRotateWithLeft(node, &tree)->right;    // case 2
                }                                                // case 2
                node->parent->color = black;                     // case 3
                node->parent->parent->color = red;               // case 3
                node = singleRotateWithRight(node->parent->parent, &tree)->right;       // case 3
            }
        }
    }

    tree->color = black;

    return tree;
}

rbTree insert(elementType value, rbTree tree) {

    if(tree == nullNode) { 
        tree = malloc(sizeof(struct rbTreeNode));
        if(tree == NULL)
            Error("out of space");
        tree->element = value;
        tree->parent = nullNode;
        tree->left = tree->right = nullNode;
        tree->color = black;

        return tree;

    } else {
        
        position root = tree;
        position newNode; // node to be inserted
        position last; // parent of the node to be inserted

        while(tree != nullNode) {
            
            last = tree;
            if(value < tree->element)
                tree = tree->left;
            else if(value > tree->element)
                tree = tree->right;
            else  // value exists in the tree
                return root;
        }

        newNode = malloc(sizeof(struct rbTreeNode));
        if(newNode == NULL)
            Error("out of space");

        newNode->element = value;
        newNode->parent = last;
        newNode->color = red;
        newNode->left = newNode->right = nullNode;

        if(value < last->element) 
            last->left = newNode;
        else
            last->right = newNode;

        return rbInsertFixup(newNode, root);
    }
}

static int max(int a, int b) {
    
    return a > b ? a : b;
}

int height(position p) {
    
    if(p == nullNode)
        return 0;
    if(p->left == nullNode && p->right == nullNode)
        return 1;
    return max(height(p->left), height(p->right)) + 1;
}

// let v take u's place 
static void transplant(rbTree *root, rbTree u, rbTree v) {

    if(u->parent == nullNode)
        *root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

static rbTree rbDeleteFixup(position node, rbTree *tree) {

    position sibling;
    
    while(node != *tree && node->color == black) {
        
        if(node == node->parent->left) {
            sibling = node->parent->right;
            if(sibling->color == red) {
                // case 1
                printf("case 1\n");
                sibling->color = black;                                     
                node->parent->color = red;
                node = singleRotateWithRight(node->parent, tree)->left->left;
                sibling = node->parent->right;
            }
            if(sibling->left->color == black && sibling->right->color == black) {
                // case 2
                printf("case 2\n");
                sibling->color = red;
                node = node->parent;
            }
            else {
                if(sibling->right->color == black) {
                    // case 3
                    printf("case 3\n");
                    sibling->left->color = black;
                    sibling->color = red;
                    sibling = singleRotateWithLeft(sibling, tree);
                }
                // case 4
                printf("case 4\n");
                sibling->color = node->parent->color;
                node->parent->color = black;
                sibling->right->color = black;
                singleRotateWithRight(node->parent, tree);
                node = *tree;
            }
        }
        else {
            sibling = node->parent->left;
            if(sibling->color == red) {
                // case 1
                printf("case 1\n");
                sibling->color = black;                                     
                node->parent->color = red;
                node = singleRotateWithLeft(node->parent, tree)->right->right;
                sibling = node->parent->left; 
            }
            if(sibling->right->color == black && sibling->left->color == black) {
                // case 2
                printf("case 2\n");
                sibling->color = red;
                node = node->parent;
            }
            else {
                if(sibling->left->color == black) {
                    // case 3
                    printf("case 3\n");
                    sibling->right->color = black;
                    sibling->color = red;
                    sibling = singleRotateWithRight(sibling, tree);
                }
                // case 4
                printf("case 4\n");
                sibling->color = node->parent->color;
                node->parent->color = black;
                sibling->left->color = black;
                singleRotateWithLeft(node->parent, tree);
                node = *tree;
            }
        }
    }

    node->color = black;

    return *tree;
}

rbTree delete(elementType value, rbTree tree) {

    position nodeToDelete = find(value, tree);
    position preNode; // node to take nodeToDelete's place
    position prepreNode; // node to take preNode's place

    if(nodeToDelete == nullNode) // value does not exist in the tree
        return tree;

    else { // to delete nodeToDelete
        
        printf("deleting %d\n", nodeToDelete->element);

        preNode = nodeToDelete;
        colorType preNodeColor = preNode->color;

        // nodeToDelete has only one child or no child
        if(nodeToDelete->left == nullNode) {
           
            printf("left child == nullNode\n");
            prepreNode = nodeToDelete->right;
            transplant(&tree, nodeToDelete, nodeToDelete->right);
        }
        else if(nodeToDelete->right == nullNode) {
            
            printf("right child == nullNode\n");
            prepreNode = nodeToDelete->left;
            transplant(&tree, nodeToDelete, nodeToDelete->left);
        }
        else { // nodeToDelete has two child

            printf("two children\n");
            preNode = findMin(nodeToDelete->right); // successor
            preNodeColor = preNode->color;
            prepreNode = preNode->right; // preNode cannot have left child

            if(preNode->parent == nodeToDelete)
                prepreNode->parent = preNode;
            else {
                
                transplant(&tree, preNode, preNode->right);
                preNode->right = nodeToDelete->right;
                preNode->right->parent = preNode;
            }
            transplant(&tree, nodeToDelete, preNode);
            preNode->left = nodeToDelete->left;
            preNode->left->parent = preNode;
            preNode->color = nodeToDelete->color;
        }

        if(preNodeColor == black)
            return rbDeleteFixup(prepreNode, &tree);
        else 
            return tree;

    }
}
