#include "BiNode.h"
#include <iostream>
#include <string>

BiNode BiNode::NULLNODE {INT16_MIN, "", 0, NULL, NULL, NULL, true};

/* Default contructor */
BiNode::BiNode()
    : key(0)
    , value("")
    , height(1)
    , parent(&NULLNODE)
    , left(&NULLNODE)
    , right(&NULLNODE)
    , aIsNull(false)
{}

BiNode::BiNode(int key, std::string value, int height, BiNode* parent, BiNode* left, BiNode* right, bool isNull)
    : key(key)
    , value(value)
    , height(height)
    , parent(parent)
    , left(left)
    , right(right)
    , aIsNull(isNull)
{}


int BiNode::getKey() {
    return this->key;
}

std::string BiNode::getValue() {
    return this->value;
}

int BiNode::getHeight() {
    return this->height;
}


/* inserts a new node in the tree
 * O(n) with n = # of nodes
 *
 * Worst case scenario: height(T) = n, completely unbalanced tree
 */
BiNode* BiNode::insert(BiNode* x) {
 // x: new node

    BiNode* y = this->parent;
    BiNode* z = this;
    while (!z->isNull()) {
            y = z;
        if (x->key < z->key) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    /* now z is a NULLNODE */
    (x->key < y->key) ? y->left = x : y->right = x;
    x->parent = y;

    return this;
}

BiNode* BiNode::remove(int k) {
    BiNode *z = find(k);
    BiNode *x; 

    /* search a replacement for z */

    if (z->left == NULL || z->right == NULL) { /* if z has only one child */
        x = z;
    } else {
        x = next(z); /* otherwise find the successor */
    }

    /* x is a leaf or has only one child, it's the BiNode that will be deleted */

    BiNode *v;
    if (x->left != NULL) {
        v = x->left;
    } else {
        v = x->right;
    }

    BiNode *y = x->parent;
    if (y == NULL) { /* if x is the root */
        t = v;
    } else {
        if (x == y->left) { /* if it's a left child */
            y->left = v;
        } else { /* else it's a right child */
            y->right = v; 
        }
    }

    if (v != NULL) { /* if v is the root of a subtree of x */
        v->parent = y;
    }

    while (y != NULL) {
        y->height = fmax(height(y->left), height(y->right)) + 1;
        y = y->parent;
    }

    if (z != x) {
        z->key = x->key;
        strcpy(z->value, x->value);
    }

    x = NULL;
    return t;
}

BiNode* BiNode::find(int k) {
    if (!this->isNull()) {
        if (this->key == k) {
            return this;
        } else if (k < this->key){
            return this->left->find(k);
        } else {
            return this->right->find(k);
        }
    } else {
        return &NULLNODE;
    }
}

void BiNode::preOrder(BiNode *x) {
    if (x != NULL && !x->isNull()) {
        std::cout << x->key << ":" << x->value << " ";

        preOrder(x->left);
        preOrder(x->right);
    } else {
        std::cout << "NULL ";
    }
}

BiNode* BiNode::min() {
    if (left->isNull()) {
        return this;
    } else {
        return this->left->min();
    }
}

/* Finds the successor of this node */
BiNode* BiNode::next() {
    if (!this->right->isNull()) {
        return this->right->min();
    } else {
        BiNode* t = this;

        while (!t->parent->isNull() && t->parent->key < t->key) {
            t = t->parent;
        }
        return t->parent;
    }
}
void BiNode::show() {
    preOrder(this);
}

bool BiNode::isNull() {
    return this->aIsNull;
}
