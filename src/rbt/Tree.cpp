#include "Tree.h"
#include <cstdio>
#include <iostream>


Node* insert(Node* x, Node* y);
Node* remove(Node* x, int k);
Node* find(int* k);
Node* leftRotate(Node* x);
Node* rightRotate(Node* x);

void RBTree::show() {
    preOrder(root);
}

void RBTree::preOrder(Node x) {
}
