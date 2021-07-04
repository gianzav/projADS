#include "RbNode.h"
#include "BstNode.h"
#include "AvlNode.h"
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int main() {
    
    srand(time(0));
    int key;
    int count;

    /* RbNode<string>* t = new RbNode<string>; */
    BstNode<string>* t = new BstNode<string>;

    for (int j=0; j<1; j++) {
        count = 0;

        for (int i=0; i<1000000; i++) {
            key = rand();

            if (t->find(key)->isNull()) {
                t = t->insert(key, "");
                count++;
            }
        }

        cout << j << ": " << count << " keys inserted" << endl;
        t = t->clear();
    }
    return 0;
}
