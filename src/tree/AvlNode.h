#include "BiNode.h"

#ifndef AVLNODE_H
#define AVLNODE_H

template <class T>
class AvlNode : public BiNode<T> {
    public:

        /* ~AvlNode() { */
        /*     if (this->left != NULL && !this->left->isNull()) */
        /*         delete this->left; */
        /*     if (this->right != NULL && !this->right->isNull()) */
        /*         delete this->left; */
        /* } */

        AvlNode()
            : BiNode<T>()
            , parent(NULL)
            , left(NULL)
            , right(NULL)
        {};

        AvlNode(int key,
                T value,
                int height,
                AvlNode<T>* parent,
                AvlNode<T>* left,
                AvlNode<T>* right,
                bool isNull)
            : BiNode<T>(key, value, height, isNull)
            , parent(parent)
            , left(left)
            , right(right)
        {};

        AvlNode(int key,
                T value)
            : BiNode<T>(key, value, 1, false)
            , parent(&NULLNODE)
            , left(&NULLNODE)
            , right(&NULLNODE)
        {};

        AvlNode* insert(int k, T value);
        AvlNode* remove(int k);
        AvlNode<T>* find(int k);   // k: key of the node
        AvlNode<T>* next();
        AvlNode<T>* min();
        AvlNode<T>* clear();
        void show();

        static AvlNode<std::string> STR_NULLNODE;
        static AvlNode<T> NULLNODE;

    private:
        void preOrder(AvlNode* x);
        AvlNode* balance();
        AvlNode* leftRotate();
        AvlNode* rightRotate();

        AvlNode* parent;
        AvlNode* left;
        AvlNode* right;

};

#include "AvlNode_impl.h"
#endif
