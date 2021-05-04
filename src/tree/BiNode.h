#include <iostream>
#include <string>

#ifndef BINODE_H
#define BINODE_H

class BiNode {
    private:
        int key;
        std::string value;
        int height;
        /* int blackHeight; */
        /* colors color; */
        BiNode* parent;
        BiNode* left;
        BiNode* right;
        bool aIsNull;

        virtual void preOrder(BiNode* x);

    public:
        ~BiNode();
        BiNode();
        BiNode(int key, std::string value, int height, BiNode* parent, BiNode* left, BiNode* right, bool isNull);

        /* BiNode(int key, std::string value, colors color); */
        /* BiNode(int key, std::string value, colors color, BiNode* left, BiNode* right); */
        /* BiNode(int key, std::string value, int height, int blackHeight, colors color, BiNode* parent, BiNode* left, BiNode* right, bool isNull); */


        virtual BiNode* insert(BiNode* x); // x: new node, y: parent
        virtual BiNode* remove(int k);
        virtual BiNode* find(int k);
        virtual BiNode* next();
        virtual BiNode* min();

        /* BiNode* leftRotate(); */
        /* BiNode* rightRotate(); */
        /* void insertBalance(); */
        void show();

        virtual bool isNull();
        int getKey();
        std::string getValue();
        /* int getColor(); */
        int getHeight();
        /* int getBlackHeight(); */
        /* void changeColor(colors c); */
        /* void toggleColor(); */
        static BiNode NULLNODE; 
};
#endif
