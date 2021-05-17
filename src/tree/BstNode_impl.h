#include <cstddef>

template <class T>
BstNode<std::string> BstNode<T>::STR_NULLNODE = {INT16_MIN, "", 0, NULL, NULL, NULL, true};

template <class T>
BstNode<T> BstNode<T>::NULLNODE;

/**
 * Destroy the entire tree recursively
 */
/* template <class T> */
/* BstNode<T>::~BstNode() { */
/*     if (this->left != NULL && !this->left->isNull()) */
/*         delete this->left; */
/*     if (this->right != NULL && !this->right->isNull()) */
/*         delete this->left; */
/* } */

template <class T>
BstNode<T>* BstNode<T>::insert(int k, T value) {

    BstNode<T>* x = new BstNode<T>(k, value);
    BstNode<T>* y = this->parent;
    BstNode<T>* z = this;

    if (z->isNull()) {
        return x;
    }

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
   
    y = this;
    z = y->parent;
    while (!z->isNull()) {
        y = z;
        z = y->parent;
    }
   
    return y;
}

template <class T>
BstNode<T>* BstNode<T>::remove(int k) {

    BstNode<T>* t;
    BstNode<T>* z = this->find(k);
    BstNode<T>* x;

    /* search a replacement for z */

    if (z->left->isNull() || z->right->isNull()) { /* if z has only one child */
        x = z;
    } else {
        x = z->next(); /* otherwise find the successor */
    }

    /* x is a leaf or has only one child, it's the node that will be deleted */

    BstNode<T>* v;
    if (!x->left) {
        v = x->left;
    } else {
        v = x->right;
    }

    BstNode<T> *y = x->parent;
    if (y->isNull()) { /* if x is the root */
        t = v;
    } else {
        if (x == y->left) { /* if it's a left child */
            y->left = v;
        } else { /* else it's a right child */
            y->right = v;
        }
    }

    if (!v->isNull()) { /* if v is the root of a subtree of x */
        v->parent = y;
    }

    while (y != NULL) {
        y->height = std::max(y->left->getHeight(), y->right->getHeight()) + 1;
        y = y->parent;
    }

    if (z != x) {
        z->key = x->key;
        z->value = x->value;
    }

    x = &NULLNODE;
    return t;
}

template <class T>
BstNode<T>* BstNode<T>::find(int k) {
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

template <class T>
void BstNode<T>::preOrder(BstNode<T>* x) {
    if (x != NULL && !x->isNull()) {
        std::cout << x->getKey() << ":" << x->getValue() << " ";

        preOrder(x->left);
        preOrder(x->right);
    } else {
        std::cout << "NULL ";
    }
}

template <class T>
BstNode<T>* BstNode<T>::min() {
    if (this->left->isNull()) {
        return this;
    } else {
        return this->left->min();
    }
}

/* Finds the successor of this node */
template <class T>
BstNode<T>* BstNode<T>::next() {
    if (!this->right->isNull()) {
        return this->right->min();
    } else {
        BstNode* t = this;

        while (!t->parent->isNull()
                && t->parent->getKey() < t->getKey()) {
            t = t->parent;
        }
        return t->parent;
    }
}


template <class T>
void BstNode<T>::show() {
    preOrder(this);
}


template <class T>
BstNode<T>* BstNode<T>::clear() {
    if (!this->isNull()) {
        this->left->clear();
        this->right->clear();
        delete this;
    }
    return &NULLNODE;
   
}
