#include "./BiNode.h"
#include <cstddef>
#include <iostream>
#include <string>

#ifndef RBNODE_H
#define RBNODE_H

enum colors {RED, BLACK}; // 0: RED, 1: BLACK

template <class T>
class RbNode : public BiNode<T> {
    public:

        /* ~RbNode(); */

        RbNode()
            : BiNode<T>()
            , color(BLACK)
            , parent(NULL)
            , left(NULL)
            , right(NULL)
        {};

        RbNode(int key, 
               T value, 
               colors color)
            : BiNode<T>(key, value, 1, false)
            , color(color)
            , parent(&NULLNODE)
            , left(&NULLNODE)
            , right(&NULLNODE)
            {};

        RbNode(int key, 
               T value, 
               int height, 
               colors color, 
               RbNode* parent, 
               RbNode* left, 
               RbNode* right, 
               bool isNull)
            : BiNode<T>(key, value, height, isNull)
            , color(color)
            , parent(parent)
            , left(left)
            , right(right)
            {};

        RbNode<T>* insert(int k, T value); // x: new node, y: parent
        RbNode<T>* remove(int k);
        RbNode<T>* find(int k);
        RbNode<T>* next();
        RbNode<T>* min();
        RbNode<T>* clear();

        colors getColor();
        void setColor(colors c);
        void toggleColor();
        void show();

        static RbNode<std::string> STR_NULLNODE; 
        static RbNode<T> NULLNODE;

    protected:
        void preOrder(RbNode* x);

    private:
        void insertBalance();
        RbNode* leftRotate();
        RbNode* rightRotate();

        colors color;
        RbNode* parent;
        RbNode* left;
        RbNode* right;
};

#include "RbNode_impl.h"
#endif
