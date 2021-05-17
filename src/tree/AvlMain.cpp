#include "AvlNode.h"
#include <sstream>
#include <string>
#include <iostream>

#define NIL AvlNode<std::string>::STR_NULLNODE

int main () {

    std::string input;
    AvlNode<std::string>* t = NULL;
    int k;
    std::string key;
    std::string v;
    std::string cmd;

    while (1) {
        std::getline(std::cin, input);
        std::stringstream ss {input};
        ss >> cmd;

        if (cmd.compare("insert") == 0) {
            ss >> key;
            k = std::stoi(key);
            ss >> v;

            if (t == NULL || t->isNull()) {
                t = new AvlNode<std::string> {k, v, 1, &NIL, &NIL, &NIL, false};
            } else {
                /* AvlNode<std::string>* newNode = new AvlNode<std::string> {k, v}; */
                t = t->insert(k, v);
            }
        } else if (cmd.compare("remove") == 0)  {
            ss >> key;
            k = std::stoi(key);
            t = t->remove(k);
        } else if (cmd.compare("find") == 0) {
            ss >> key;
            k = std::stoi(key);
            AvlNode<std::string>* x = t->find(k);

            std::cout << x->getValue() << std::endl;
        } else if (cmd.compare("clear") == 0) {
            delete t;
            t = NULL;
        } else if (cmd.compare("show") == 0) {
            t->show();
            std::cout << std::endl;
        } else if (cmd.compare("height") == 0){
            std::cout << t->getHeight() << std::endl;
        } else {
            break;
        }
    }

    return 0;
}
