#include <iostream>
#include <string>

/* Getters */
template <class ValT>
int BiNode<ValT>::getKey() {
    return this->key;
}

template <class ValT>
ValT BiNode<ValT>::getValue() {
    return this->value;
}

template <class ValT>
int BiNode<ValT>::getHeight() {
    return this->height;
}

/* template <class ValT> */
/* NodeT* BiNode<ValT, NodeT>::getParent() { */
/*     return this->parent; */
/* } */

/* template <class ValT> */
/* NodeT* BiNode<ValT, NodeT>::getLeft() { */
/*     return this->left; */
/* } */

/* template <class ValT> */
/* NodeT* BiNode<ValT, NodeT>::getRight() { */
/*     return this->right; */
/* } */

/* Setters */

template <class ValT>
void BiNode<ValT>::setKey(int key) {
    this->key = key;
}

template <class ValT>
void BiNode<ValT>::setValue(ValT value) {
    this->value = value;
}

template <class ValT>
void BiNode<ValT>::setHeight(int height) {
    this->height = height;
}

/* template <class ValT> */
/* void BiNode<ValT, NodeT>::setParent(NodeT* parent) { */
/*     this->parent = parent; */
/* } */

/* template <class ValT> */
/* void BiNode<ValT, NodeT>::setLeft(NodeT* left) { */
/*     this->left = left; */
/* } */

/* template <class ValT> */
/* void BiNode<ValT, NodeT>::setRight(NodeT* right) { */
/*     this->right = right; */
/* } */

/* template <class ValT> */
/* void BiNode<ValT, NodeT>::show() { */
/*     preOrder(this); */
/* } */

template <class T>
bool BiNode<T>::isNull() {
    return this->aIsNull;
}
