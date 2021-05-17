#include "RbNode.h"
#include <sstream>
#include <string>
#include <iostream>


int main () {

    std::string input;
    RbNode<std::string>* t = NULL;
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

            if (t == NULL) {
                t = new RbNode<std::string> {k, v, BLACK};
            } else {
                RbNode<std::string>* newNode = new RbNode<std::string> {k, v, RED};
                t = t->insert(newNode);
            }
        } else if (cmd.compare("remove") == 0)  {
            break;
        } else if (cmd.compare("find") == 0) {
            ss >> key;
            k = std::stoi(key);
            RbNode<std::string>* x = t->find(k);

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
