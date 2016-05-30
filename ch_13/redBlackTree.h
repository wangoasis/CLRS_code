typedef int elementType;

#ifndef _REDBLACKTREE_H
#define _REDBLACKTREE_H

struct rbTreeNode;
typedef struct rbTreeNode *rbTree;
typedef struct rbTreeNode *position;

rbTree init(void);
rbTree makeEmpty(rbTree);
position find(elementType, rbTree);
position findMin(rbTree);
position findMax(rbTree);
rbTree insert(elementType, rbTree);
rbTree delete(elementType, rbTree);
elementType retrieve(position);
void printTree(rbTree);
int height(rbTree);

#endif
