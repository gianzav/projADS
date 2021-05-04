#include "RBNode.h"
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>

Node Node::NULLNODE {INT16_MIN, "", 0, 0, BLACK, NULL, NULL, NULL, true};

Node::Node(int key, std::string value, colors color)
    : key(key)
    , value(value)
    , color(color)
    , height(1)
    , blackHeight(1)
    , parent(&NULLNODE)
    , left(&NULLNODE)
    , right(&NULLNODE)
    , aIsNull(false) 
{}

Node::Node(int key, std::string value, colors color, Node* left, Node* right)
    : key(key)
    , value(value)
    , color(color)
    , height(1)
    , blackHeight(1) // NULL leafs are black by definition
    , parent(NULL)
    , left(left)
    , right(right)
    , aIsNull(false)
{}


Node::Node(int key, std::string value, int height, int blackHeight, colors color, Node* parent, Node* left, Node* right, bool isNull)
    : key(key)
    , value(value)
    , color(color)
    , height(height)
    , blackHeight(blackHeight) // NULL leafs are black by definition
    , parent(parent)
    , left(left)
    , right(right)
    , aIsNull(isNull)
{}

/**
 * Destroy the entire tree recursively
 */
Node::~Node() {
    if (left != NULL && !left->isNull())
        delete left;
    if (right != NULL && !right->isNull())
        delete right;
}

int Node::getKey() {
    return this->key;
}

int Node::getColor() {
    return this->color;
}

int Node::getHeight() {
    return this->height;
}

std::string Node::getValue() {
    return this->value;
}

int Node::getBlackHeight() {
    return this->blackHeight;
}

void Node::changeColor(colors c) {
    this->color = c;
}

void Node::toggleColor() {
    (this->color == RED) ? this->color = BLACK : this->color = RED;
}

bool Node::isNull() {
    return this->aIsNull;
}

/**
 * Left rotate 'this' 
 * @return New root of subtree (previously 'this')
 */
Node* Node::leftRotate() {
    Node* x = this;
    Node* y = x->right; 
    Node* z = x->parent;
    
    x->right = y->left;
    y->left->parent = x;
    y->parent = z;

    (x->key < z->key) ? z->left = y : z->right = y;
   
    y->left = x;
    x->parent = y;

    x->height = std::max(x->left->height, x->right->height) + 1;
    y->height = std::max(y->left->height, y->right->height) + 1;

    while (!z->isNull()) {
        z->height = std::max(z->left->height, z->right->height) + 1;
        z = z->parent;
    }


    /* what about black height? */
    return y;
}

/**
 * Right rotate 'this' 
 * @return New root of subtree (previously 'this')
 */
Node* Node::rightRotate() {
    Node* x = this;
    Node* y = x->left; 
    Node* z = x->parent;
    
    x->left = y->right;
    y->right->parent = x;
    y->parent = z;

    (x->key < z->key) ? z->left = y : z->right = y;
    
    y->right = x;
    x->parent = y;

    x->height = std::max(x->left->height, x->right->height) + 1;
    y->height = std::max(y->left->height, y->right->height) + 1;

    while (!z->isNull()) {
        z->height = std::max(z->left->height, z->right->height) + 1;
        z = z->parent;
    }

    /* what about black height? */
    return y;
}

void Node::show() {
    preOrder(this);
}

void Node::preOrder(Node *x) {
    if (x != NULL && !x->isNull()) {
        std::string color;
        (x->color == RED) ? color = "red" : color = "black";
        std::cout << x->key << ":" << x->value << ":" << color << " ";

        preOrder(x->left);
        preOrder(x->right);
    } else {
        std::cout << "NULL ";
    }
}

Node* Node::find(int k) {
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


/**
 * @param[in] x Node to insert in the tree where this Node is the root
 * @return Root of the modified tree
 */
Node* Node::insert(Node* x) { // x: new node

    x->changeColor(RED);

    Node* y = this->parent;
    Node* z = this;
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
    
    if (y->color == RED) {
        x->insertBalance();
    }

    y = this;
    z = y->parent;
    while (!z->isNull()) {
        y = z;
        z = y->parent;
    }
    
    return y;
} 


/**
 * @pre this node is RED
 */
void Node::insertBalance() {

    Node* x = this;  // new node
    Node* y = x->parent;
    Node* w = x->parent->parent; // grandparent of x
    Node* z; // uncle of x

    if (y->isNull()) { // x is the root
        x->changeColor(BLACK);
        return;
    } else if (w->isNull()){ // y is the root
        y->changeColor(BLACK);
        return;
    }

    (y->key < w->key) ? z = w->right : z = w->left;

    if (z->color == BLACK) { // "lucky" or "almost lucky" case

        if (x == y->left && z == w->right) { // opposite nodes. x:left, z:right
            w->rightRotate();
            y->changeColor(BLACK);
            w->changeColor(RED);
        } else if (x == y->right && z == w->left) { // opposite nodes. x:right, z:left
            w->leftRotate();
            y->changeColor(BLACK);
            w->changeColor(RED);
        } else if (x == y->left && z == w->left) { // "same edge" nodes. x:left, z:left
            y->rightRotate();     
            // now it's the "lucky" case, but with y
            y->insertBalance();
        } else { // x:right, z:right
            y->leftRotate();     
            // now it's the "lucky" case, but with y
            y->insertBalance();
        }
    } else { // "unlucky" case, z is RED
        y->changeColor(BLACK);
        z->changeColor(BLACK);
        w->changeColor(RED);
        // now could be w to cause a RED-RED problem
        if (!w->parent->isNull() && w->parent->color == RED) {
            w->insertBalance();
        } else if (w->parent->isNull()){
            w->changeColor(BLACK);
        }
    }
}
