#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

std::string generazioneStringa(int n) {
    std::string s = "";
    std::string p;
    for (int i = 0; i < n; i++) {
        p = 'a' + ((int)rand()) % 2;
        s = s + p;
    }
    return s;
}


int main() {

    using namespace std;

    /* Get a new seed based on current time to have a new batch of pseudo-random values */
    srand(time(0));

    string s;

    string fileName = "rand";
    string fileExt = ".txt";
    int suffix = 1; 

    fstream f;
    f.open(fileName + fileExt, std::ios_base::out);

    /* If the file already exists close it */
    while (f) {
        f.close();
        f.open(fileName + to_string(suffix++) + fileExt, std::ios_base::out);
    }

    for (int i = 0; i < 10; i++) {

    }

    f.close();
}
