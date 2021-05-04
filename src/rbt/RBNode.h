#include <iostream>
#include <string>

#ifndef RBNODE_H
#define RBNODE_H

enum colors {RED, BLACK}; // 0: RED, 1: BLACK

class Node {
    private:
        int key;
        std::string value;
        int height;
        int blackHeight;
        colors color;
        Node* parent;
        Node* left;
        Node* right;
        bool aIsNull;

        void preOrder(Node* x);

    public:
        ~Node();
        Node(int key, std::string value, colors color);
        Node(int key, std::string value, colors color, Node* left, Node* right);
        Node(int key, std::string value, int height, int blackHeight, colors color, Node* parent, Node* left, Node* right, bool isNull);


        Node* insert(Node* x); // x: new node, y: parent
        Node* remove(int k);
        Node* find(int k);
        Node* leftRotate();
        Node* rightRotate();
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
        static Node NULLNODE; 
};
#endif
