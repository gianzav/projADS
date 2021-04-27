#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sys/stat.h>

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

    string fileName = "./generated/rand";
    string fileExt = ".txt";
    int suffix = 1; 

    fstream f;

    /* If the file already exists close it */
    /* while (f) { */
    /*     f.close(); */
    /*     f.open(fileName + to_string(suffix++) + fileExt, std::ios_base::out); */
    /* } */

    /* for (int i = 0; i < 10; i++) { */

    /* } */

    struct stat buf;

    while (stat( (fileName + to_string(suffix) + fileExt).c_str(), &buf) != -1) {
        suffix++;
    }

    f.open(fileName + to_string(suffix) + fileExt, ios_base::out);

    for (int i = 0; i<10; i++) {
        s = generazioneStringa(10);
        f << s << endl;
    }

    f.close();
    return 0;
}
