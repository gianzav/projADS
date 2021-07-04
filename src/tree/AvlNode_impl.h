#include <stdexcept>
template <class T>
AvlNode<std::string> AvlNode<T>::STR_NULLNODE = {INT16_MIN, "", 0, NULL, NULL, NULL, true};

template <class T>
AvlNode<T> AvlNode<T>::NULLNODE;


template <class T>
AvlNode<T>* AvlNode<T>::leftRotate() {

    AvlNode<T>* y = this->parent;
    AvlNode<T>* r = this->right;
    
    /* rotating */
    r->parent = y;
    this->right = r->left; 

    if (!r->left->isNull())
        r->left->parent = this;

    r->left = this;
    this->parent = r;
    
    if (!y->isNull()) {
        if (this == y->left)
            y->left = r;
        else
            y->right = r;
    }

    /* updating the heights */
    this->height = std::max(this->left->height, this->right->height) + 1;
    r->height = std::max(r->left->height, r->right->height) + 1;

    while (!y->isNull()) {
        y->height = std::max(y->left->height, y->right->height) + 1;
        y = y->parent;
    }
    return r;
}

template <class T>
AvlNode<T>* AvlNode<T>::rightRotate() {
    AvlNode<T>* y = this->parent;
    AvlNode<T>* l = this->left; /* will be the new root */

    /* rotating */
    l->parent = y;
    this->left = l->right;

    if (!l->right->isNull())
        l->right->parent = this;

    l->right = this;
    this->parent = l;

    if (!y->isNull()) {
        if (this == y->left)
            y->left = l;
        else
            y->right = l;
    }

    /* updating the heights */
    this->height = std::max(this->left->height, this->right->height) + 1;
    l->height = std::max(l->left->height, l->right->height) + 1;

    while (!y->isNull()) {
        y->height = std::max(y->left->height, y->right->height) + 1;
        y = y->parent;
    }

    return l;
}

/* inserts a new AvlNode<T> in the tree
 * O(n) with n = # of nodes
 *
 * Worst case scenario: height(T) = n, completely unbalanced tree
 * 
 * Output: pointer to the new AvlNode<T>
 */
template <class T>
AvlNode<T>* AvlNode<T>::insert(int k, T value) {

    AvlNode<T>* x = new AvlNode<T>(k, value);
    AvlNode<T>* y = this->parent;
    AvlNode<T>* z = this;
    AvlNode<T>* t;

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

    t = y;
    /* Updating heights */
    while (y != NULL && !y->isNull()) {
        y->height = std::max(y->left->height, y->right->height) + 1;
        t = y;
        y = y->parent;
    }
    
    /* Balancing */
    x = x->parent->parent;

    while (x != NULL && !x->isNull()) {
        if (std::abs(x->left->height - x->right->height) == 2) {
            t = x->balance();
        }  else {
            t = x;
        }
        x = x->parent;
    }

    /* Now t is the root of the new tree */

    /* y = this; */
    /* z = y->parent; */
    /* while (!z->isNull()) { */
    /*     y = z; */
    /*     z = y->parent; */
    /* } */
    
    return t;
}

template <class T>
void AvlNode<T>::show() {
    preOrder(this);
}

template <class T>
void AvlNode<T>::preOrder(AvlNode<T> *x) {
    if (x != NULL && !x->isNull()) {
        std::cout << x->key << ":" << x->value << ":" << x->height << " ";

        preOrder(x->left);
        preOrder(x->right);
    } else {
        std::cout << "NULL ";
    }
}

/* finds the AvlNode<T> whose key is k
 */
template <class T>
AvlNode<T>* AvlNode<T>::find(int k) {
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
AvlNode<T>* AvlNode<T>::next() {
    if (!this->right->isNull()) {
        return this->right->min();
    } else {
        AvlNode* t = this;

        while (!t->parent->isNull()
                && t->parent->getKey() < t->getKey()) {
            t = t->parent;
        }
        return t->parent;
    }
}

template <class T>
AvlNode<T>* AvlNode<T>::min() {
    if (this->left->isNull()) {
        return this;
    } else {
        return this->left->min();
    }
}

/* Output: pointer to the effectively removed AvlNode<T>
 */
template <class T>
AvlNode<T>* AvlNode<T>::remove(int k) {

    AvlNode<T>* t = this;
    AvlNode<T>* z = this->find(k);
    AvlNode<T>* x;

    /* search a replacement for z */

    if (z->left->isNull() || z->right->isNull()) { /* if z has only one child */
        x = z;
    } else {
        x = z->next(); /* otherwise find the successor */
    }

    /* x is a leaf or has only one child, it's the node that will be deleted */

    AvlNode<T>* v;
    if (!x->left->isNull()) {
        v = x->left;
    } else {
        v = x->right;
    }

    AvlNode<T>* y = x->parent;
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

    while (y != NULL && !y->isNull()) {
        y->height = std::max(y->left->height, y->right->height) + 1;
        y = y->parent;
    }

    if (z != x) {
        z->key = x->key;
        z->value = x->value;
    }

    while (x != NULL && !x->isNull()) {
        if (std::abs(x->left->height - x->right->height) == 2) {
            if (x == t) {
                t = x->balance();
                x = t;
            } else {
                x = x->balance();
            }
        }
        x = x->parent;
    }

    return t;
}


/* Pre: |height(x->left) - height(x->right)| = 2
 *      x->left and x->right are balanced
 */
template <class T>
AvlNode<T>* AvlNode<T>::balance() {

    AvlNode<T>* x = this;
    AvlNode<T>* y = x->left;
    AvlNode<T>* z = x->right;

    int h = y->height;
    int k = z->height;

    if (h > k) { /* left subtree is bigger */
        if (y->left->height < y->right->height)
            y->leftRotate();

        x = x->rightRotate();
    } else {
        if (z->left->height > z->right->height)
            z->rightRotate();

        x = x->leftRotate();
    }

    return x;
}


template <class T>
AvlNode<T>* AvlNode<T>::clear() {
    if (this->left != NULL && !this->left->isNull())
        delete this->left;
    if (this->right != NULL && !this->left->isNull())
        delete this->right;
    return &NULLNODE;
}
