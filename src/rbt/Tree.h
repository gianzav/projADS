#include "Node.h"

#ifndef RBTREE_H
#define RBTREE_H

class RBTree {
    private:
        Node* root; // pointer to the root of the tree
        int size;  // # nodes

        void preOrder(Node x);

    public:
        RBTree();
        RBTree(Node* root, int size);
        
        Node* insert(Node* x, Node* y);
        Node* remove(Node* x, int k);
        Node* find(int* k);
        Node* leftRotate(Node* x);
        Node* rightRotate(Node* x);
        void show();
};
#endif
