#include <cstdint>
#include <cstdio>

template <class T>
RbNode<std::string> RbNode<T>::STR_NULLNODE = {0, "", 0, BLACK, NULL, NULL, NULL, true};

template <class T>
RbNode<T> RbNode<T>::NULLNODE;


/**
 * Destroy the entire tree recursively
 */
/* template <class T> */
/* RbNode<T>::~RbNode<T>() { */
/*     if (this->left != NULL && !this->left->isNull()) */
/*         delete this->left; */
/*     if (this->right != NULL && !this->right->isNull()) */
/*         delete this->left; */
/* } */

template <class T>
colors RbNode<T>::getColor() {
    return this->color;
}

/* template <class T> */
/* int RbNode<T>::getBlackHeight() { */
/*     return this->blackHeight; */
/* } */

template <class T>
void RbNode<T>::setColor(colors c) {
    this->color = c;
}

template <class T>
void RbNode<T>::toggleColor() {
    (this->color == RED) ? this->color = BLACK : this->color = RED;
}

/**
 * Left rotate 'this' 
 * @return New root of subtree (previously 'this')
 */
template <class T>
RbNode<T>* RbNode<T>::leftRotate() {
    RbNode<T>* x = this;
    RbNode<T>* y = x->right; 
    RbNode<T>* z = x->parent;
    
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
template <class T>
RbNode<T>* RbNode<T>::rightRotate() {
    RbNode<T>* x = this;
    RbNode<T>* y = x->left; 
    RbNode<T>* z = x->parent;
    
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

template <class T>
void RbNode<T>::preOrder(RbNode<T> *x) {
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

template <class T>
RbNode<T>* RbNode<T>::find(int k) {
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
 * @param[in] x RbNode<T> to insert in the tree where this RbNode<T> is the root
 * @return Root of the modified tree
 */
template <class T>
RbNode<T>* RbNode<T>::insert(int k, T value) { // x: new node

    RbNode<T>* x = new RbNode<T>{k, value, RED};

    RbNode<T>* y = this->parent;
    RbNode<T>* z = this;

    if (this->isNull()) {
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
template <class T>
void RbNode<T>::insertBalance() {

    RbNode<T>* x = this;  // new node
    RbNode<T>* y = x->parent;
    RbNode<T>* w = x->parent->parent; // grandparent of x
    RbNode<T>* z; // uncle of x

    if (y->isNull()) { // x is the root
        x->color = BLACK;
        return;
    } else if (w->isNull()){ // y is the root
        y->color = BLACK;
        return;
    }

    (y->key < w->key) ? z = w->right : z = w->left;

    if (z->color == BLACK) { // "lucky" or "almost lucky" case

        if (x == y->left && z == w->right) { // opposite nodes. x:left, z:right
            w->rightRotate();
            y->color = BLACK;
            w->color = RED;
        } else if (x == y->right && z == w->left) { // opposite nodes. x:right, z:left
            w->leftRotate();
            y->color = BLACK;
            w->color = RED;
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
        y->color = BLACK;
        z->color = BLACK;
        w->color = RED;
        // now could be w to cause a RED-RED problem
        if (!w->parent->isNull() && w->parent->color == RED) {
            w->insertBalance();
        } else if (w->parent->isNull()){
            w->color = BLACK;
        }
    }
}

/* Finds the successor of this node */
template <class T>
RbNode<T>* RbNode<T>::next() {
    if (!this->right->isNull()) {
        return this->right->min();
    } else {
        RbNode* t = this;

        while (!t->parent->isNull()
                && t->parent->getKey() < t->getKey()) {
            t = t->parent;
        }
        return t->parent;
    }
}

template <class T>
RbNode<T>* RbNode<T>::min() {
    if (this->left->isNull()) {
        return this;
    } else {
        return this->left->min();
    }
}

template <class T>
void RbNode<T>::show() {
    preOrder(this);
}

template <class T>
RbNode<T>* RbNode<T>::remove(int k) { return NULL; }

template <class T>
RbNode<T>* RbNode<T>::clear() {
    if (this->left != NULL && !this->left->isNull())
        delete this->left;
    if (this->right != NULL && !this->left->isNull())
        delete this->right;
    return &NULLNODE;
}
