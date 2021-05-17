#include "./BiNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

template <class T>
class BstNode : public BiNode<T> {
    public:

        /* ~BstNode() { */
        /*     if (this->left != NULL && !this->left->isNull()) */
        /*         delete this->left; */
        /*     if (this->right != NULL && !this->right->isNull()) */
        /*         delete this->left; */
        /* } */

        BstNode()
            : BiNode<T>()
            , parent(NULL)
            , left(NULL)
            , right(NULL)
        {};

        BstNode(int key,
                T value,
                int height,
                BstNode<T>* parent,
                BstNode<T>* left,
                BstNode<T>* right,
                bool isNull)
            : BiNode<T>(key, value, height, isNull)
            , parent(parent)
            , left(left)
            , right(right)
        {};

        BstNode(int key,
                T value)
            : BiNode<T>(key, value, 1, false)
            , parent(&NULLNODE)
            , left(&NULLNODE)
            , right(&NULLNODE)
        {};


        BstNode<T>* insert(int k, T value);
        BstNode<T>* remove(int k);
        BstNode<T>* find(int k);   // k: key of the node
        BstNode<T>* next();
        BstNode<T>* min();
        BstNode<T>* clear();
        void show();

        static BstNode<std::string> STR_NULLNODE;
        static BstNode<T> NULLNODE;

    private:
        void preOrder(BstNode* x);

        BstNode* parent;
        BstNode* left;
        BstNode* right;
};

#include "BstNode_impl.h"
#endif
