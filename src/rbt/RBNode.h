#include "../tree/BiNode.h"
#include <iostream>
#include <string>

#ifndef RBNODE_H
#define RBNODE_H

enum colors {RED, BLACK}; // 0: RED, 1: BLACK

class RBNode : BiNode {
    private:
        int key;
        std::string value;
        int height;
        int blackHeight;
        colors color;
        RBNode* parent;
        RBNode* left;
        RBNode* right;
        bool aIsNull;

        void preOrder(RBNode* x);

    public:
        ~RBNode();
        RBNode(int key, std::string value, colors color);
        RBNode(int key, std::string value, colors color, RBNode* left, RBNode* right);
        RBNode(int key, std::string value, int height, int blackHeight, colors color, RBNode* parent, RBNode* left, RBNode* right, bool isNull);


        RBNode* insert(RBNode* x); // x: new node, y: parent
        RBNode* remove(int k);
        RBNode* find(int k);
        RBNode* leftRotate();
        RBNode* rightRotate();
        void insertBalance();
        void show();

        bool isNull();
        int getKey();
        std::string getValue();
        int getColor();
        int getHeight();
        int getBlackHeight();
        void changeColor(colors c);
        void toggleColor();
        static RBNode NULLNODE; 
};
#endif
