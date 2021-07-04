#include <cstddef>
#include <cstdint>

#ifndef BINODE_H
#define BINODE_H

template <class ValT>
class BiNode {
    public:

        int getKey();
        ValT getValue();
        int getHeight();

        void setKey(int key);
        void setValue(ValT value);
        void setHeight(int height);

        virtual BiNode<ValT>* insert(int k, ValT value) = 0;
        virtual BiNode<ValT>* remove(int k) = 0;
        virtual BiNode<ValT>* find(int k) = 0;   // k: key of the node
        virtual BiNode<ValT>* next() = 0;
        virtual BiNode<ValT>* min() = 0;
        virtual BiNode<ValT>* clear() = 0;

        virtual void show() = 0;

        bool isNull();


    protected:

        BiNode() 
            : key(INT16_MIN)
            , height(0)
            , aIsNull(true) 
        {};

        BiNode(int key,
               ValT value,
               int height,
               bool isNull)
            : key(key)
            , value(value)
            , height(height)
            , aIsNull(isNull) 
        {};

        int key;
        ValT value;
        int height;
        bool aIsNull;

};

#include "BiNode_impl.h"
#endif
