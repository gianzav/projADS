#include <iostream>

using namespace std;

void func(int x) {
    x = 10;
}

int main() {
    int a = 34; 
    func(a);
    cout << a << endl;
    return 0;
}
